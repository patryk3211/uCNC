/*
	Name: logo.h
	Description: Bitmapped logo used in the startup screen

	Copyright: Copyright (c) Patryk Mierzyński
	Author: Patryk Mierzyński
	Date: 27/07/2024

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
*/

#ifndef TFT_DISPLAY_H
#error "Please do not include this file manually"
#endif

const gfx_pixel_t Logo_Colors[] = {
	GFX_BLACK,
	GFX_COLOR(0x303030),
	GFX_COLOR(0x509c51),
	GFX_COLOR(0xffffff),
};
const uint8_t Logo_40x40[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 65, 65, 65, 65, 64, 0, 0, 0, 0, 1, 65, 65, 65, 65, 64, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 0, 0, 0, 5, 85, 85, 85, 85, 85, 85, 80, 0, 0, 21, 106, 170, 170, 170, 170, 169, 84, 0, 0, 86, 170, 170, 170, 170, 170, 170, 149, 0, 0, 90, 106, 170, 170, 170, 170, 170, 165, 0, 1, 89, 90, 170, 170, 170, 170, 170, 165, 64, 1, 106, 105, 85, 85, 85, 89, 106, 169, 64, 1, 106, 166, 85, 85, 85, 89, 90, 169, 64, 21, 106, 150, 85, 149, 85, 89, 86, 169, 84, 21, 106, 150, 86, 106, 165, 89, 86, 169, 84, 1, 106, 150, 85, 149, 89, 89, 86, 169, 64, 1, 106, 153, 149, 85, 86, 101, 86, 169, 64, 21, 106, 150, 85, 85, 85, 149, 86, 169, 84, 21, 106, 149, 85, 245, 215, 95, 86, 169, 84, 1, 106, 149, 87, 93, 215, 117, 214, 169, 64, 1, 106, 149, 87, 85, 247, 117, 86, 169, 64, 21, 106, 151, 119, 85, 223, 117, 86, 169, 84, 21, 106, 151, 119, 85, 215, 117, 86, 169, 84, 1, 106, 151, 119, 93, 215, 117, 214, 169, 64, 1, 106, 151, 213, 245, 215, 95, 86, 169, 64, 21, 106, 151, 85, 85, 86, 85, 86, 169, 84, 21, 106, 151, 85, 85, 86, 85, 86, 169, 84, 1, 106, 149, 149, 85, 85, 149, 86, 169, 64, 1, 106, 149, 101, 86, 85, 101, 86, 169, 64, 21, 106, 149, 89, 89, 149, 89, 86, 169, 84, 21, 106, 149, 89, 86, 85, 86, 86, 169, 84, 1, 106, 165, 89, 86, 85, 86, 90, 169, 64, 1, 106, 169, 89, 86, 85, 86, 106, 169, 64, 1, 90, 170, 170, 170, 170, 170, 170, 165, 64, 0, 90, 170, 170, 170, 170, 170, 170, 165, 0, 0, 86, 170, 170, 170, 170, 170, 170, 149, 0, 0, 21, 106, 170, 170, 170, 170, 169, 84, 0, 0, 5, 85, 85, 85, 85, 85, 85, 80, 0, 0, 0, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 1, 65, 65, 65, 65, 64, 0, 0, 0, 0, 1, 65, 65, 65, 65, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

