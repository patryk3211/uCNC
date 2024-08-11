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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../../module.h"

#define SYSTEM_MENU_ACTION_INPUT_CHAR(c) (c)
#define SYSTEM_MENU_ACTION_BUTTON(b) ((b) + 128)

DECL_MODULE(keyboard);

#ifdef __cplusplus
}
#endif

#endif

