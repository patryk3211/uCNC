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

#define KEYBOARD_SCAN_PERIOD_MS 20
#define DEBOUNCE_DELAY 50

#define JOG_SWITCH 0
#define FEED_SWITCH 1

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
static uint8_t joystick_positions[2];
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

static FORCEINLINE void kb_btn(uint8_t index, bool release)
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

static FORCEINLINE void jog()
{
	float target[MAX(AXIS_COUNT, 3)];
	memset(target, 0, sizeof(target));

	motion_data_t block_data = { 0 };
	block_data.feed = g_system_menu_jog_feed;

	if(kb_keypad_state(KB_X_POS))
	{
		target[0] = g_system_menu_jog_distance;
	}
	else if(kb_keypad_state(KB_X_NEG))
	{
		target[0] = -g_system_menu_jog_distance;
	}
	else if(kb_keypad_state(KB_Y_POS))
	{
		target[1] = g_system_menu_jog_distance;
	}
	else if(kb_keypad_state(KB_Y_NEG))
	{
		target[1] = -g_system_menu_jog_distance;
	}
	else if(kb_keypad_state(KB_Z_POS))
	{
		target[2] = g_system_menu_jog_distance;
	}
	else if(kb_keypad_state(KB_Z_NEG))
	{
		target[2] = -g_system_menu_jog_distance;
	}
	else
	{
		return;
	}

	mc_incremental_jog(target, &block_data);
}

#define JOYSTICK_DEAD_ZONE 0.05

static FORCEINLINE float joystick_axis_transform_side(float value)
{
	if(value < JOYSTICK_DEAD_ZONE)
	{
		// Joystick dead zone
		return 0;
	}
	else
	{
		// Remap the remaining part to <0; 1> range
		value -= JOYSTICK_DEAD_ZONE;
		value *= 1.0 / (1.0 - JOYSTICK_DEAD_ZONE);
		// This should allow for better control
		return value * value;
	}
}

static FORCEINLINE float joystick_axis_transform(float value)
{
	// Symmetric response
	return value < 0 ? -joystick_axis_transform_side(-value) : joystick_axis_transform_side(value);
}

#ifdef DECL_SERIAL_STREAM
DECL_BUFFER(uint8_t, joystick_steam_buffer, 64);

static uint8_t js_getc()
{
	uint8_t c;
	BUFFER_DEQUEUE(joystick_steam_buffer, &c);
	return c;
}

static uint8_t js_available()
{
	return BUFFER_READ_AVAILABLE(joystick_steam_buffer);
}

static void js_clear()
{
	BUFFER_CLEAR(joystick_steam_buffer);
}

static void js_putc(char c)
{
	BUFFER_ENQUEUE(joystick_steam_buffer, &c);
}

DECL_SERIAL_STREAM(joystick_stream, js_getc, js_available, js_clear, NULL, NULL);
#endif

static bool joystick_jogging = false;
static FORCEINLINE void joystick_jog()
{
	// Any state other than JOG is forbidden, jogging switch must be active
	if(cnc_get_exec_state(EXEC_ALLACTIVE & ~EXEC_JOG) || cnc_has_alarm() || !kb_switch_state(JOG_SWITCH))
		return;

	int16_t x = -CLAMP((int16_t)joystick_positions[1] - 127, -127, 127);
	int16_t y =  CLAMP((int16_t)joystick_positions[0] - 127, -127, 127);

	float tX = joystick_axis_transform((float)x / 127);
	float tY = joystick_axis_transform((float)y / 127);

	float feed = 3000 * MAX(ABS(tX), ABS(tY));
	// s = v * dt, where dt = 50ms
	float distance = feed / 60 * 0.05;

	if(tX == 0 && tY == 0)
	{
		if(cnc_get_exec_state(EXEC_JOG) && joystick_jogging)
		{
			cnc_call_rt_command(CMD_CODE_JOG_CANCEL);
			joystick_jogging = false;
		}
	}
	else
	{
		// More than two jog commands in buffer
		if(PLANNER_BUFFER_SIZE - planner_get_buffer_freeblocks() > 2)
			return;
		if(BUFFER_WRITE_AVAILABLE(joystick_steam_buffer) < 48)
			return;

		// Header
		js_putc('$');
		js_putc('J');
		js_putc('=');
		js_putc('G');
		js_putc('9');
		js_putc('1');

		// Calculate length for normalization
		float invLen = fast_flt_invsqrt(fast_flt_pow2(tX) + fast_flt_pow2(tY));
		float xDist = distance * tX * invLen;
		float yDist = distance * tY * invLen;

		if(xDist != 0)
		{
			js_putc('X');
			print_flt(js_putc, xDist);
		}
		if(yDist != 0)
		{
			js_putc('Y');
			print_flt(js_putc, yDist);
		}

		js_putc('F');
		print_flt(js_putc, feed);
		js_putc('\r');

		joystick_jogging = true;
	}
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
		uint8_t current_command = next_command++;
		softspi_xmit(&keyboard_spi, current_command);
		mcu_delay_us(20);
		switch(current_command)
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

		if(next_command > 4)
		{
			next_command = 1;
			last_scan_time = mcu_millis();
		}

		cnc_dotasks();

		if((button_matrix & (
			(1 << KB_X_POS) | (1 << KB_X_NEG) |
			(1 << KB_Y_POS) | (1 << KB_Y_NEG) |
			(1 << KB_Z_POS) | (1 << KB_Z_NEG)
		)) && current_command == 1) {
			jog();
		}

		if(current_command == 2)
		{
			static bool prev_state = false;
			bool current_state = kb_switch_state(FEED_SWITCH);
			if(prev_state != current_state && timestamp < mcu_millis())
			{
				if(current_state)
				{
					cnc_call_rt_command(CMD_CODE_FEED_HOLD);
				}
				else
				{
					cnc_call_rt_command(CMD_CODE_CYCLE_START);
				}
				prev_state = current_state;
				timestamp = mcu_millis() + DEBOUNCE_DELAY;
			}
		}

		if(current_command == 4)
		{
			joystick_jog();
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

#ifdef DECL_SERIAL_STREAM
	BUFFER_INIT(uint8_t, joystick_stream_buffer, 64);
	serial_stream_register(&joystick_stream);
#endif

#ifdef ENABLE_MAIN_LOOP_MODULES
	ADD_EVENT_LISTENER(cnc_dotasks, keyboard_scan);
#else
#warning "Main loop extensions not enabled. Keyboard module will not function."
#endif
}

