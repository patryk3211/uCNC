#include "src/cnc.h"

#define CNC_STATE EXEC_INTERLOCKING_FAIL //EXEC_IDLE
uint8_t cnc_get_exec_state(uint8_t state) {
	return (CNC_STATE) & state;
}

bool cnc_has_alarm() {
	return (CNC_STATE) & EXEC_ALARM;
}

uint8_t cnc_get_alarm() {
	return 1;
}

void parser_get_modes(uint8_t *modes, uint16_t *feed, uint16_t *spindle) {
	modes[6] = 54;
	modes[2] = 90;
	modes[4] = 21;
	modes[11] = 1;
	*feed = 0;
	*spindle = 0;
}

void itp_get_rt_position(int32_t* steppos) {
	for(int i = 0; i < STEPPER_COUNT; ++i)
		steppos[i] = 0;
}

void kinematics_apply_forward(int32_t *steppos, float *mpos) {
	for(int i = 0; i < STEPPER_COUNT; ++i)
		mpos[i] = steppos[i];
}

void kinematics_apply_reverse_transform(float *mpos) {}
void parser_machine_to_work(float *wpos) { }

