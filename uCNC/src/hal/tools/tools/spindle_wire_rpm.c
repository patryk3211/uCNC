#include "../../../cnc.h"

#include <math.h>
#include "../../../modules/wire_rpm.h"

/**
 * This configures a simple spindle control with a pwm assigned to WIRE_RPM0 and dir invert assigned to DOUT0
 * This spindle also has a coolant pin assigned to DOUT1
 *
 * */

// give names to the pins (easier to identify)
#ifndef SPINDLE_WIRE_RPM
#define SPINDLE_WIRE_RPM PWM0
#endif
#ifndef SPINDLE_WIRE_RPM_DIR
#define SPINDLE_WIRE_RPM_DIR DOUT0
#endif

#ifdef ENABLE_COOLANT
#ifndef SPINDLE_WIRE_RPM_COOLANT_FLOOD
#define SPINDLE_WIRE_RPM_COOLANT_FLOOD DOUT2
#endif
#ifndef SPINDLE_WIRE_RPM_COOLANT_MIST
#define SPINDLE_WIRE_RPM_COOLANT_MIST DOUT3
#endif
#endif

#if defined(ENABLE_TOOL_PID_CONTROLLER) && !defined(DISABLE_SPINDLE_WIRE_RPM_PID)
#ifndef SPINDLE_WIRE_RPM_PID_SAMPLE_RATE_HZ
#define SPINDLE_WIRE_RPM_PID_SAMPLE_RATE_HZ 1
#endif
#define SPINDLE_WIRE_RPM_PID_SETTING_ID 400
#include <stdbool.h>
#include <math.h>
#include "../../../modules/pid.h"
static pid_data_t spindle_wire_rpm_pid;
DECL_EXTENDED_SETTING(SPINDLE_WIRE_RPM_PID_SETTING_ID, spindle_wire_rpm_pid.k, float, 3, protocol_send_gcode_setting_line_flt);
#endif

// #define SPEED_LIMIT 255

static void
startup_code(void)
{
// force pwm mode
#if ASSERT_PIN(SPINDLE_WIRE_RPM)
	io_config_pwm(SPINDLE_WIRE_RPM, 1000);
#endif

#if defined(ENABLE_TOOL_PID_CONTROLLER) && !defined(DISABLE_SPINDLE_WIRE_RPM_PID)
	EXTENDED_SETTING_INIT(SPINDLE_WIRE_RPM_PID_SETTING_ID, spindle_wire_rpm_pid.k);
	settings_load(EXTENDED_SETTING_ADDRESS(SPINDLE_WIRE_RPM_PID_SETTING_ID), (uint8_t *)spindle_wire_rpm_pid.k, sizeof(spindle_wire_rpm_pid.k));
	spindle_wire_rpm_pid.max = g_settings.spindle_max_rpm; // * (SPEED_LIMIT / 255.0f);
	spindle_wire_rpm_pid.min = g_settings.spindle_min_rpm;
#endif
}

static void set_speed(int16_t value)
{
	// easy macro to execute the same code as below
	// SET_SPINDLE(SPINDLE_WIRE_RPM, SPINDLE_WIRE_RPM_DIR, value, invert);
// speed optimized version (in AVR it's 24 instruction cycles)
#if ASSERT_PIN(SPINDLE_WIRE_RPM_DIR)
	if ((value <= 0))
	{
		io_clear_output(SPINDLE_WIRE_RPM_DIR);
	}
	else
	{
		io_set_output(SPINDLE_WIRE_RPM_DIR);
	}
#endif

#if ASSERT_PIN(SPINDLE_WIRE_RPM)
	io_set_pwm(SPINDLE_WIRE_RPM, (uint8_t)ABS(value));
#endif
}

static void set_coolant(uint8_t value)
{
// easy macro
#ifdef ENABLE_COOLANT
	SET_COOLANT(SPINDLE_WIRE_RPM_COOLANT_FLOOD, SPINDLE_WIRE_RPM_COOLANT_MIST, value);
#endif
}

static int16_t range_speed(int16_t value)
{
	value = (int16_t)((255.0f) * (((float)value) / g_settings.spindle_max_rpm));
  // Temporary limit on the max speed
  // if(ABS(value) > 50) value = 50;
  // if(value > SPEED_LIMIT) value = SPEED_LIMIT;
  // else if(value < -SPEED_LIMIT) value = -SPEED_LIMIT;
	return value;
}

static uint16_t get_speed(void)
{
  return wire_rpm_get_speed();
}

#if defined(ENABLE_TOOL_PID_CONTROLLER) && !defined(DISABLE_SPINDLE_WIRE_RPM_PID)
static void pid_update(void)
{
	float output = tool_get_setpoint();

	if (output != 0)
	{
    // Convert IO value back into RPM.
    output = output * g_settings.spindle_max_rpm / 255.0f;
		if (pid_compute(&spindle_wire_rpm_pid, &output, output, get_speed(), HZ_TO_MS(SPINDLE_WIRE_RPM_PID_SAMPLE_RATE_HZ)))
		{
      // spindle_wire_io_value += (uint16_t)output; //range_speed((uint16_t)output);
      // spindle_wire_io_value = CLAMP(0, spindle_wire_io_value, 50);
      print_int(serial_putc, output);
      serial_putc('\n');
			io_set_pwm(SPINDLE_WIRE_RPM, range_speed((int16_t) output));
		}
  }
	else
  {
    // spindle_wire_io_value = 0;
    spindle_wire_rpm_pid.current = 0;
    spindle_wire_rpm_pid.i_accum = 0;
    spindle_wire_rpm_pid.last_input = 0;
  }
}

#endif

const tool_t spindle_wire_rpm = {
	.startup_code = &startup_code,
	.shutdown_code = NULL,
#if defined(ENABLE_TOOL_PID_CONTROLLER) && !defined(DISABLE_SPINDLE_WIRE_RPM_PID)
	.pid_update = &pid_update,
#else
	.pid_update = NULL,
#endif
	.range_speed = &range_speed,
	.get_speed = &get_speed,
	.set_speed = &set_speed,
	.set_coolant = &set_coolant};
