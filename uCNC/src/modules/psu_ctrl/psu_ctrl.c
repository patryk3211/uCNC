/*
	Name: psu_ctrl.c
	Description: Simple module to turn on a power supply when the machine is unlocked

	Copyright: Copyright (c) Patryk Mierzyński
	Author: Patryk Mierzyński
	Date: 16/08/2024

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
*/
#include "psu_ctrl.h"
#include "src/cnc.h"

#ifndef PSU_CTRL_PIN
#define PSU_CTRL_PIN DOUT0
#endif

static bool psu_on = false;

#ifdef ENABLE_MAIN_LOOP_MODULES
static bool psu_reset(void *arg)
{
	io_set_output(PSU_CTRL_PIN);
	psu_on = false;
	return EVENT_CONTINUE;
}

static bool psu_handle(void *arg)
{
	if(!psu_on && !cnc_get_exec_state(EXEC_RESET_LOCKED))
	{
		// Power supply is disabled and CNC just got unlocked
		psu_on = true;
		io_clear_output(PSU_CTRL_PIN);
	}
	return EVENT_CONTINUE;
}

CREATE_EVENT_LISTENER(cnc_reset, psu_reset);
CREATE_EVENT_LISTENER(cnc_dotasks, psu_handle);
#endif

DECL_MODULE(psu_ctrl)
{
	io_set_output(PSU_CTRL_PIN);
	mcu_config_opendrain(PSU_CTRL_PIN);
	psu_on = false;

#ifdef ENABLE_MAIN_LOOP_MODULES
	ADD_EVENT_LISTENER(cnc_reset, psu_reset);
	ADD_EVENT_LISTENER(cnc_dotasks, psu_handle);
#endif
}

