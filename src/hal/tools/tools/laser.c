/*
	Name: lase1.c
	Description: Defines a laser tool using PWM0 for µCNC.
                 Defines a coolant output using DOUT1 (can be used for air assist).

	Copyright: Copyright (c) João Martins
	Author: João Martins
	Date: 17/12/2021

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the	GNU General Public License for more details.
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "cnc.h"
#include "core/io_control.h"
#include "interface/settings.h"
#include "hal/tools/tool_helper.h"

#include <stdbool.h>

    /**
 * This configures a simple spindle control with a pwm assigned to PWM0 and dir invert assigned to DOUT0
 * This spindle also has a coolant pin assigned to DOUT1
 * 
 * */

//give names to the pins (easier to identify)
#define SPINDLE_PWM PWM0
#define COOLANT_FLOOD DOUT1

    static bool previous_lase_mode;

    void laser1_startup_code(void)
    {
        //force laser mode
        previous_lase_mode = g_settings.laser_mode;
        g_settings.laser_mode = 1;
    }

    void laser1_shutdown_code(void)
    {
        //restore laser mode
        g_settings.laser_mode = previous_lase_mode;
    }

    void laser1_set_speed(uint8_t value, bool invert)
    {
//easy macro to execute the same code as below
//SET_LASER(SPINDLE_PWM, value, invert);

//speed optimized version (in AVR it's 24 instruction cycles)
#if SPINDLE_PWM >= 0
        if (SPINDLE_PWM > 0)
        {
            mcu_set_pwm(SPINDLE_PWM, value);
        }
#endif
    }

    void laser1_set_coolant(uint8_t value)
    {
        //easy macro
        SET_COOLANT(COOLANT_FLOOD, -1, value);
    }

    const tool_t __rom__ laser1 = {
        .startup_code = &laser1_startup_code,
        .shutdown_code = &laser1_shutdown_code,
        .set_speed = &laser1_set_speed,
        .set_coolant = NULL,
        .get_spindle = NULL,
        .pid_controller = NULL};

#ifdef __cplusplus
}
#endif
