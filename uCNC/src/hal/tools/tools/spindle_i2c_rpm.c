/*
 *   Custom spindle tool for my custom machine, copied from `spindle_pwm.c`
 *       - patryk3211
 */

#include "../../../cnc.h"

#include <math.h>

#ifndef SPINDLE_PWM
#define SPINDLE_PWM PWM0
#endif

#ifndef MCU_HAS_I2C
#error "An I2C port must be defined for this tool to work"
#endif

#define I2C_RPM_ADDR 0x5A

#define RPM_MULTIPLIER 600

#define I2C_READ  0
#define I2C_WRITE 1

#define I2C_START(addr, rw) mcu_i2c_write(((addr) << 1) | (!rw), true, false)
#define I2C_STOP() mcu_i2c_write(0, false, true)

static uint8_t speed;
static uint32_t currentRPM;
static uint32_t lastMeasurement;

#ifdef ENABLE_MAIN_LOOP_MODULES
static bool spindle_i2c_read(void* args) {
	if(mcu_millis() - lastMeasurement >= 100) {
		uint32_t data;
		if(mcu_i2c_receive(I2C_RPM_ADDR, (uint8_t*)&data, sizeof(uint32_t), 10) == I2C_OK)
			currentRPM = data;

		lastMeasurement = mcu_millis();
	}

	return EVENT_CONTINUE;
}
CREATE_EVENT_LISTENER(cnc_dotasks, spindle_i2c_read);
#endif


static void startup_code(void)
{
    // Configure I2C RPM meter
	mcu_i2c_config(100000);

	{ // Set reset frequency
		uint8_t data[] = { 0x01, 10 };
		mcu_i2c_send(I2C_RPM_ADDR, data, sizeof(data), true);
	}

	// My stupid little reader is too slow and needs some time
	// before it can start another data exchange
	mcu_delay_us(50);

	{ // Set multiplier
		uint8_t data[] = { 0x02, (uint8_t)(RPM_MULTIPLIER), (uint8_t)((RPM_MULTIPLIER) >> 8) };
		mcu_i2c_send(I2C_RPM_ADDR, data, sizeof(data), true);
	}

#ifdef ENABLE_MAIN_LOOP_MODULES
	ADD_EVENT_LISTENER(cnc_dotasks, spindle_i2c_read);

	lastMeasurement = mcu_millis();
#endif

#if ASSERT_PIN(SPINDLE_PWM)
	mcu_config_pwm(SPINDLE_PWM, 1000);
#endif
}

static void set_speed(int16_t value)
{
	speed = (uint8_t)ABS(value);

#if ASSERT_PIN(SPINDLE_PWM)
	mcu_set_pwm(SPINDLE_PWM, (uint8_t)ABS(value));
#else
	io_set_pwm(SPINDLE_PWM, (uint8_t)ABS(value));
#endif
}

static void set_coolant(uint8_t value)
{
// easy macro
#ifdef ENABLE_COOLANT
	SET_COOLANT(SPINDLE_PWM_COOLANT_FLOOD, SPINDLE_PWM_COOLANT_MIST, value);
#endif
}

static int16_t range_speed(int16_t value)
{
	value = (int16_t)((255.0f) * (((float)value) / g_settings.spindle_max_rpm));
	return value;
}

static uint16_t get_speed(void)
{
#ifdef SPINDLE_PWM_HAS_RPM_ENCODER
	return encoder_get_rpm();
#else
#if ASSERT_PIN(SPINDLE_PWM)
	float spindle = (float)speed * g_settings.spindle_max_rpm * UINT8_MAX_INV;
	return (uint16_t)lroundf(spindle);
#else
	return 0;
#endif
#endif
}

#if PID_CONTROLLERS > 0
static void pid_update(int16_t value)
{
	if (speed != 0)
	{
		uint8_t newval = CLAMP(0, mcu_get_pwm(SPINDLE_PWM) + value, 255);
#if ASSERT_PIN(SPINDLE_PWM)
		mcu_set_pwm(SPINDLE_PWM, newval);
#else
		io_set_pwm(SPINDLE_PWM, newval);
#endif
	}
}

static int16_t pid_error(void)
{
    return (speed * g_settings.spindle_max_rpm - currentRPM) / g_settings.spindle_max_rpm;
}
#endif

const tool_t spindle_pwm_i2c = {
	.startup_code = &startup_code,
	.shutdown_code = NULL,
#if PID_CONTROLLERS > 0
	.pid_update = &pid_update,
	.pid_error = &pid_error,
#endif
	.range_speed = &range_speed,
	.get_speed = &get_speed,
	.set_speed = &set_speed,
	.set_coolant = &set_coolant};
