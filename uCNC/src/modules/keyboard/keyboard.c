/*
	Name: keyboard.h
	Description: Module for an SPI front panel

	Copyright: Copyright (c) Patryk Mierzyński
	Author: Patryk Mierzyński
	Date: 31/07/2024

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
*/

#include "keyboard.h"

#include "src/cnc.h"
#include "src/utils.h"
#include "src/modules/softspi.h"
#include "src/modules/lvgl/lvgl_support.h"
#include "src/modules/system_menu.h"

#include "keybinds.h"

#ifndef KEYBOARD_CS
#define KEYBOARD_CS DOUT0
#endif

#ifndef KEYBOARD_SPI_FREQ
#define KEYBOARD_SPI_FREQ 1000000
#endif

static HARDSPI(keyboard_spi, KEYBOARD_SPI_FREQ, 0, mcu_spi_port);

#ifdef ENABLE_MAIN_LOOP_MODULES
static uint8_t next_command = 1;
static uint32_t last_scan_time = 0;

static void slow_receive(void *data, uint8_t length)
{
	// I don't know why this has to be here
	// but without it there is a zero at the
	// beginning of every transmission.
	softspi_xmit(&keyboard_spi, 0);

	uint8_t *ptr = (uint8_t*)data;
	for(uint8_t i = 0; i < length; ++i)
	{
		mcu_delay_us(20);
		ptr[i] = softspi_xmit(&keyboard_spi, 0);
	}
}

static uint32_t button_matrix;
static uint8_t aux_buttons;
static int8_t joystick_positions[2];

static int8_t lvgl_encoder_delta;
// Bit 7 = Make/Break, Bits 6...0 = ASCII code of the key
DECL_BUFFER(char, lvgl_keypad_buffer, 32);
DECL_BUFFER(uint8_t, lvgl_button_buffer, 32);

static FORCEINLINE bool encoder_state()
{
	return !((aux_buttons >> 1) & 1);
}

static void kb_btn(uint8_t index, bool release)
{
	uint8_t btn_id;
	if(index == 19)
		btn_id = 0;
	else if(index == 17)
		btn_id = 1;
	else
		btn_id = 2;
	if(release) btn_id |= 0x80;
	BUFFER_ENQUEUE(lvgl_button_buffer, &btn_id);
}

static void kb_keypad_press(uint8_t index)
{
	if(index < sizeof(LVGL_KEYPAD_KEYS))
	{
		char key = LVGL_KEYPAD_KEYS[index] & 0x7F;
		BUFFER_ENQUEUE(lvgl_keypad_buffer, &key);
	}

	if(index == 19 || index == 17 || index == 16)
		kb_btn(index, false);
}

static void kb_keypad_release(uint8_t index)
{
	if(index < sizeof(LVGL_KEYPAD_KEYS))
	{
		char key = LVGL_KEYPAD_KEYS[index] | 0x80;
		BUFFER_ENQUEUE(lvgl_keypad_buffer, &key);
	}

	if(index == 19 || index == 17 || index == 16)
		kb_btn(index, true);
}

void kb_joystick_press()
{

}

bool kb_switch_state(uint8_t index)
{
	return (aux_buttons >> (index + 2)) & 1;
}

void kb_joystick(uint8_t *axis)
{
	axis[0] = joystick_positions[0];
	axis[1] = joystick_positions[1];
}

static bool keyboard_scan(void *arg)
{
	if(mcu_millis() - last_scan_time >= 8)
	{
		// Start transaction
		softspi_start(&keyboard_spi);
		io_clear_output(KEYBOARD_CS);

		// Send command and wait for keyboard MCU to process
		softspi_xmit(&keyboard_spi, next_command);
		mcu_delay_us(20);
		switch(next_command)
		{
			case 1:
			{
				// Button matrix
				uint32_t new_matrix;
				slow_receive(&new_matrix, 4);

				uint32_t diff = new_matrix ^ button_matrix;
				for(uint8_t i = 0; i < 32; ++i)
				{
					if(!((diff >> i) & 1))
						// No change
						continue;
					((new_matrix >> i) & 1) ? kb_keypad_press(i) : kb_keypad_release(i);
				}
				button_matrix = new_matrix;
				break;
			}
			case 2:
			{
				// Aux buttons
				uint8_t new_aux;
				slow_receive(&new_aux, 1);

#define FALLING_AUX(i) ((((new_aux ^ aux_buttons) >> (i)) & 1) && !((new_aux >> (i)) & 1))

				if(FALLING_AUX(0))
					kb_joystick_press();

				aux_buttons = new_aux;
				break;
			}
			case 3:
			{
				// Encoder delta
				int8_t encoder_delta;
				slow_receive(&encoder_delta, 1);
				if(encoder_delta != 0)
				{
					lvgl_encoder_delta += encoder_delta;
				}
				break;
			}
			case 4:
				// Joystick position
				slow_receive(joystick_positions, 2);
				break;
		}

		// End transaction
		io_set_output(KEYBOARD_CS);
		softspi_stop(&keyboard_spi);

		if(++next_command > 4)
		{
			next_command = 1;
			last_scan_time = mcu_millis();
		}

		cnc_dotasks();
	}

	return EVENT_CONTINUE;
}

CREATE_EVENT_LISTENER_WITHLOCK(cnc_dotasks, keyboard_scan, LISTENER_HWSPI_LOCK);
#endif

static void lvgl_encoder_cb(lv_indev_t *dev, lv_indev_data_t *data)
{
	data->enc_diff = lvgl_encoder_delta;
	data->state = encoder_state() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
	lvgl_encoder_delta = 0;
}

static void lvgl_keypad_cb(lv_indev_t *dev, lv_indev_data_t *data)
{
	if(BUFFER_EMPTY(lvgl_keypad_buffer))
		return;
	char key;
	BUFFER_DEQUEUE(lvgl_keypad_buffer, &key);
	data->key = key & 0x7F;
	data->state = (key & 0x80) ? LV_INDEV_STATE_RELEASED : LV_INDEV_STATE_PRESSED;
}

static void lvgl_buttons_cb(lv_indev_t *dev, lv_indev_data_t *data)
{
	if(BUFFER_EMPTY(lvgl_button_buffer))
	{
		data->btn_id = -1;
		return;
	}
	uint8_t btn;
	BUFFER_DEQUEUE(lvgl_button_buffer, &btn);
	data->btn_id = btn & 0x7F;
	data->state = (btn & 0x80) ? LV_INDEV_STATE_RELEASED : LV_INDEV_STATE_PRESSED;
}

DECL_MODULE(keyboard)
{
	io_set_output(KEYBOARD_CS);

	// spi_config_t conf = { 0 };
	// softspi_config(&keyboard_spi, conf, KEYBOARD_SPI_FREQ);

	BUFFER_INIT(char, lvgl_keypad_buffer, 32);
	BUFFER_INIT(uint8_t, lvgl_button_buffer, 32);

	lv_indev_t *encoder = lv_indev_create();
	lv_indev_set_type(encoder, LV_INDEV_TYPE_ENCODER);
	lv_indev_set_read_cb(encoder, lvgl_encoder_cb);
	LVGL_ADD_INDEV(encoder);

	lv_indev_t *buttons = lv_indev_create();
	lv_indev_set_type(buttons, LV_INDEV_TYPE_BUTTON);
	lv_indev_set_read_cb(buttons, lvgl_buttons_cb);
	static lv_point_t btn_points[] = {
		{ 25, 55 },
		{ 25, 140 },
		{ 25, 225 }
	};
	lv_indev_set_button_points(buttons, btn_points);
	LVGL_ADD_INDEV(buttons);

	lv_indev_t *keypad = lv_indev_create();
	lv_indev_set_type(keypad, LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_read_cb(keypad, lvgl_keypad_cb);
	LVGL_ADD_INDEV(keypad);

#ifdef ENABLE_MAIN_LOOP_MODULES
	ADD_EVENT_LISTENER(cnc_dotasks, keyboard_scan);
#else
#warning "Main loop extensions not enabled. Keyboard module will not function."
#endif
}

