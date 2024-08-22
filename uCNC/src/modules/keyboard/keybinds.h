/*
	Name: keybinds.h
	Description: Defines keybinds to specific system menu actions for the keyboard

	Copyright: Copyright (c) Patryk Mierzyński
	Author: Patryk Mierzyński
	Date: 01/08/2024

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
*/

#ifndef KEYBOARD_H
#error "This file shouldn't be included outside of the keyboard module"
#endif

// #define ACT_CHR(c) SYSTEM_MENU_ACTION_INPUT_CHAR(c)
// #define ACT_NONE SYSTEM_MENU_ACTION_NONE

// const uint8_t KEYPAD_ACTIONS[] = {
// 	ACT_CHR('1'), ACT_CHR('2'), ACT_CHR('3'), ACT_NONE,
// 	ACT_CHR('4'), ACT_CHR('5'), ACT_CHR('6'), ACT_NONE,
// 	ACT_CHR('7'), ACT_CHR('8'), ACT_CHR('9'), ACT_NONE,
// 	ACT_NONE, ACT_CHR('0'), ACT_NONE, ACT_NONE
// };

const char LVGL_KEYPAD_KEYS[] = {
	'1', '2', '3', 'X',
	'4', '5', '6', 'Y',
	'7', '8', '9', 'Z',
	'.', '0', '#', 'D',
	 // 0,   0,   0,   0, // Screen buttons
	 // 0,   0,   0,   0, // XY control
	 // 0,   0,   0,   0, // Z control
};

#define KB_X_POS 20
#define KB_X_NEG 23
#define KB_Y_POS 22
#define KB_Y_NEG 21
#define KB_Z_POS 25
#define KB_Z_NEG 24


