#include "../../../cnc.h"

#ifndef SPINDLE_SERVO
#define SPINDLE_SERVO SERVO0
#endif
#ifndef SPINDLE_SERVO_PIN
#define SPINDLE_SERVO_PIN DOUT9
#endif

#define THROTTLE_DOWN 0
#define THROTTLE_FULL 255
#define THROTTLE_RANGE (THROTTLE_FULL - THROTTLE_DOWN)

static uint8_t spindle_speed;

void spindle_simple_esc_startup() {
#if ((SPINDLE_SERVO) >= 0)
    mcu_set_servo(SPINDLE_SERVO, 0);
	cnc_delay_ms(6000);
#endif
}

void spindle_simple_esc_shutdown() {
#if ((SPINDLE_SERVO_PIN) >= 0)
	mcu_clear_output(SPINDLE_SERVO_PIN);
#endif
}

int16_t spindle_simple_esc_range_speed(int16_t value) {
	if(value == 0) {
		return 0;
	}

	value = (int16_t)((THROTTLE_RANGE) * (((float)value) / g_settings.spindle_max_rpm) + THROTTLE_DOWN);
	return value;
}

void spindle_simple_esc_set_speed(int16_t value) {
#if ((SPINDLE_SERVO) >= 0)
	if(value <= 0) {
		mcu_set_servo(SPINDLE_SERVO, THROTTLE_DOWN);
	} else {
		mcu_set_servo(SPINDLE_SERVO, (uint8_t)value);
	}

	spindle_speed = (value <= 0) ? 0 : value;
#endif
}

void spindle_simple_esc_set_coolant(uint8_t value) { }

uint16_t spindle_simple_esc_get_speed(void) {
	return spindle_speed;
}

const tool_t __rom__ spindle_simple_esc = {
	.startup_code = &spindle_simple_esc_startup,
	.shutdown_code = &spindle_simple_esc_shutdown,
#if PID_CONTROLLERS > 0
	.pid_update = NULL,
	.pid_error = NULL,
#endif
	.range_speed = &spindle_simple_esc_range_speed,
	.get_speed = &spindle_simple_esc_get_speed,
	.set_speed = &spindle_simple_esc_set_speed,
	.set_coolant = &spindle_simple_esc_set_coolant
};
