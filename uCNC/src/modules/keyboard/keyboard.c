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

#include "indev/lv_indev.h"
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

#define KEYBOARD_SCAN_PERIOD_MS 20
#define DEBOUNCE_DELAY 50

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

static uint32_t timestamp;

static uint32_t button_matrix;
// static uint8_t aux_buttons;
static int8_t joystick_positions[2];
static uint8_t switches;
static bool encoder_pressed;

static lv_indev_t *encoder;
static lv_indev_t *buttons;
static lv_indev_t *keypad;

static int8_t lvgl_encoder_delta;
// Bit 7 = Make/Break, Bits 6...0 = ASCII code of the key
DECL_BUFFER(char, lvgl_keypad_buffer, 32);
DECL_BUFFER(uint8_t, lvgl_button_buffer, 32);

static FORCEINLINE bool kb_keypad_state(uint8_t index)
{
	return (button_matrix >> index) & 1;
}

static void kb_btn(uint8_t index, bool release)
{
	uint8_t btn_id;
	if(index == 19)
		btn_id = 0;
	else if(index == 17)
		btn_id = 1;
	else if(index == 16)
		btn_id = 2;
	else
		return;
	if(release) btn_id |= 0x80;
	BUFFER_ENQUEUE(lvgl_button_buffer, &btn_id);
}

static void kb_keypad_press(uint8_t index)
{
	if(index < sizeof(LVGL_KEYPAD_KEYS))
	{
		char key = LVGL_KEYPAD_KEYS[index];
		if(key != 0)
		{
			key &= 0x7F;
			BUFFER_ENQUEUE(lvgl_keypad_buffer, &key);
		}
	}

	if(index == 19 || index == 17 || index == 16)
		kb_btn(index, false);
}

static void kb_keypad_release(uint8_t index)
{
	if(index < sizeof(LVGL_KEYPAD_KEYS))
	{
		char key = LVGL_KEYPAD_KEYS[index];
		if(key != 0)
		{
			key |= 0x80;
			BUFFER_ENQUEUE(lvgl_keypad_buffer, &key);
		}
	}

	if(index == 19 || index == 17 || index == 16)
		kb_btn(index, true);
}

bool kb_switch_state(uint8_t index)
{
	return (switches >> index) & 1;
}

void kb_joystick(uint8_t *axis)
{
	axis[0] = joystick_positions[0];
	axis[1] = joystick_positions[1];
}

static void jog()
{
	if(cnc_get_exec_state(EXEC_JOG))
		return;
	extern uint16_t jog_feed;
	extern float jog_distance;

	char buffer[48];
	char *ptr = buffer;
	*ptr++ = '$';
	*ptr++ = 'J';
	*ptr++ = '=';
	*ptr++ = 'G';
	*ptr++ = '9';
	*ptr++ = '1';

	if(kb_keypad_state(KB_X_POS))
	{
		*ptr++ = 'X';
	}
	else if(kb_keypad_state(KB_X_NEG))
	{
		*ptr++ = 'X';
		*ptr++ = '-';
	}
	else if(kb_keypad_state(KB_Y_POS))
	{
		*ptr++ = 'Y';
	}
	else if(kb_keypad_state(KB_Y_NEG))
	{
		*ptr++ = 'Y';
		*ptr++ = '-';
	}
	else if(kb_keypad_state(KB_Z_POS))
	{
		*ptr++ = 'Z';
	}
	else if(kb_keypad_state(KB_Z_NEG))
	{
		*ptr++ = 'Z';
		*ptr++ = '-';
	}
	else
	{
		return;
	}

	sprintf(ptr, "%d.%03dF%d\r", (uint16_t)jog_distance, (uint16_t)((uint32_t)(jog_distance * 1000) % 1000), jog_feed);

	system_menu_send_cmd(buffer);
}

static FORCEINLINE void kb_rx_button_matrix()
{
	if(timestamp >= mcu_millis())
		return;
	uint32_t new_matrix;
	slow_receive(&new_matrix, 4);

	uint32_t diff = new_matrix ^ button_matrix;
	for(uint8_t i = 0; i < 32; ++i)
	{
		if(!((diff >> i) & 1))
			// No change
			continue;
		((new_matrix >> i) & 1) ? kb_keypad_press(i) : kb_keypad_release(i);
		timestamp = mcu_millis() + DEBOUNCE_DELAY;
	}
	button_matrix = new_matrix;

	if(!BUFFER_EMPTY(lvgl_keypad_buffer))
		lv_indev_read(keypad);
	if(!BUFFER_EMPTY(lvgl_button_buffer))
		lv_indev_read(buttons);
}

static FORCEINLINE void kb_rx_aux_buttons()
{
	uint8_t new_aux;
	slow_receive(&new_aux, 1);

	if(button_matrix)
		return;

	bool new_enc = !((new_aux >> 1) & 1);
	// Double timeout on the encoder actions
	if(new_enc != encoder_pressed && timestamp + DEBOUNCE_DELAY < mcu_millis())
	{
		timestamp = mcu_millis() + DEBOUNCE_DELAY;
		encoder_pressed = new_enc;
	}

	switches = (new_aux >> 2) & 0b11;
}

static FORCEINLINE void kb_rx_encoder_delta()
{
	int8_t encoder_delta;
	slow_receive(&encoder_delta, 1);
	if(button_matrix)
		return;
	if(encoder_delta != 0 && timestamp + DEBOUNCE_DELAY < mcu_millis())
	{
		lvgl_encoder_delta += encoder_delta;
	}
}

static FORCEINLINE void kb_rx_joystick()
{
	slow_receive(joystick_positions, 2);
}

static bool keyboard_scan(void *arg)
{
	if(mcu_millis() - last_scan_time >= KEYBOARD_SCAN_PERIOD_MS)
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
				kb_rx_button_matrix();
				break;
			case 2:
				kb_rx_aux_buttons();
				break;
			case 3:
				kb_rx_encoder_delta();
				break;
			case 4:
				kb_rx_joystick();
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

		if(button_matrix & (
			(1 << KB_X_POS) | (1 << KB_X_NEG) |
			(1 << KB_Y_POS) | (1 << KB_Y_NEG) |
			(1 << KB_Z_POS) | (1 << KB_Z_NEG)
		)) {
			jog();
		}
	}

	return EVENT_CONTINUE;
}

CREATE_EVENT_LISTENER_WITHLOCK(cnc_dotasks, keyboard_scan, LISTENER_HWSPI_LOCK);
#endif

static void lvgl_encoder_cb(lv_indev_t *dev, lv_indev_data_t *data)
{
	data->enc_diff = lvgl_encoder_delta;
	data->state = encoder_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
	lvgl_encoder_delta = 0;
}

static void lvgl_keypad_cb(lv_indev_t *dev, lv_indev_data_t *data)
{
	if(BUFFER_EMPTY(lvgl_keypad_buffer))
	{
		data->key = -1;
		data->state = -1;
		return;
	}
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
		data->state = -1;
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

	spi_config_t conf = { 0 };
	softspi_config(&keyboard_spi, conf, KEYBOARD_SPI_FREQ);

	BUFFER_INIT(char, lvgl_keypad_buffer, 32);
	BUFFER_INIT(uint8_t, lvgl_button_buffer, 32);

	encoder = lv_indev_create();
	lv_indev_set_type(encoder, LV_INDEV_TYPE_ENCODER);
	lv_indev_set_read_cb(encoder, lvgl_encoder_cb);
	lv_indev_set_mode(encoder, LV_INDEV_MODE_TIMER);
	LVGL_ADD_INDEV(encoder);

	buttons = lv_indev_create();
	lv_indev_set_type(buttons, LV_INDEV_TYPE_BUTTON);
	lv_indev_set_read_cb(buttons, lvgl_buttons_cb);
	static lv_point_t btn_points[] = {
		{ 25, 55 },
		{ 25, 140 },
		{ 25, 225 }
	};
	lv_indev_set_button_points(buttons, btn_points);
	lv_indev_set_mode(buttons, LV_INDEV_MODE_EVENT);
	LVGL_ADD_INDEV(buttons);

	keypad = lv_indev_create();
	lv_indev_set_type(keypad, LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_read_cb(keypad, lvgl_keypad_cb);
	lv_indev_set_mode(keypad, LV_INDEV_MODE_EVENT);
	LVGL_ADD_INDEV(keypad);

#ifdef ENABLE_MAIN_LOOP_MODULES
	ADD_EVENT_LISTENER(cnc_dotasks, keyboard_scan);
#else
#warning "Main loop extensions not enabled. Keyboard module will not function."
#endif
}

