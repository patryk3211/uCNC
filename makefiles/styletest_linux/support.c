#include "src/cnc.h"

#define CNC_STATE 0//EXEC_INTERLOCKING_FAIL //EXEC_IDLE
uint8_t cnc_get_exec_state(uint8_t state) {
	return (CNC_STATE) & state;
}

bool cnc_has_alarm() {
	return (CNC_STATE) & EXEC_ALARM;
}

uint8_t cnc_get_alarm() {
	return 0;
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

planner_state_t g_planner_state;

void serial_stream_register(serial_stream_t *stream) {}

void print_str(print_cb cb, const char *__s)
{
	while (*__s)
	{
		cb(*__s++);
	}
}

void print_bytes(print_cb cb, const uint8_t *data, uint8_t count)
{
	do
	{
		cb(' ');
		uint8_t up = *data >> 4;
		uint8_t c = (up > 9) ? ('a' + up - 10) : ('0' + up);
		cb(c);
		up = *data & 0x0F;
		c = (up > 9) ? ('a' + up - 10) : ('0' + up);
		cb(c);
		data++;
	} while (--count);
}

void print_int(print_cb cb, int32_t num)
{
	if (num == 0)
	{
		cb('0');
		return;
	}

	uint8_t buffer[11];
	uint8_t i = 0;

	if (num < 0)
	{
		cb('-');
		num = -num;
	}

	while (num > 0)
	{
		uint8_t digit = num % 10;
		num = (uint32_t)truncf((float)num * 0.1f);
		buffer[i++] = digit;
	}

	do
	{
		i--;
		cb('0' + buffer[i]);
	} while (i);
}

void print_flt(print_cb cb, float num)
{
	if (num < 0)
	{
		cb('-');
		num = -num;
	}

	uint32_t interger = (uint32_t)floorf(num);
	num -= interger;
	uint32_t mult = (!g_settings.report_inches) ? 1000 : 10000;
	num *= mult;
	uint32_t digits = (uint32_t)lroundf(num);
	if (digits == mult)
	{
		interger++;
		digits = 0;
	}

	print_int(cb, interger);
	cb('.');
	if (g_settings.report_inches)
	{
		if (digits < 1000)
		{
			cb('0');
		}
	}

	if (digits < 100)
	{
		cb('0');
	}

	if (digits < 10)
	{
		cb('0');
	}

	print_int(cb, digits);
}

void print_fltunits(print_cb cb, float num)
{
	num = (!g_settings.report_inches) ? num : (num * MM_INCH_MULT);
	print_flt(cb, num);
}

void print_intarr(print_cb cb, int32_t *arr, uint8_t count)
{
	do
	{
		print_int(cb, *arr++);
		count--;
		if (count)
		{
			cb(',');
		}

	} while (count);
}

void print_fltarr(print_cb cb, float *arr, uint8_t count)
{
	uint8_t i = count;
	do
	{
		print_fltunits(cb, *arr++);
		i--;
		if (i)
		{
			cb(',');
		}

	} while (i);

	if (count < 3)
	{
		i = 3 - count;
		do
		{
			cb(',');
			print_flt(cb, 0);
		} while (--i);
	}
}

uint8_t g_module_lockguard;

void protocol_send_error(uint8_t error)
{
}

bool cnc_dotasks()
{
	return true;
}

uint8_t mcu_eeprom_getc(uint16_t address)
{
  return 0;
}

void mcu_eeprom_putc(uint16_t address, uint8_t value)
{
}

void mcu_eeprom_flush()
{
}

char serial_getc()
{
	return 0;
}

void cnc_call_rt_command(uint8_t command)
{

}

void protocol_send_cnc_settings(void)
{

}

void kinematics_steps_to_coordinates(int32_t *steps, float *axis)
{
}

uint8_t serial_freebytes()
{
	return 0;
}

// event_cnc_reset_handler
WEAK_EVENT_HANDLER(cnc_reset)
{
	DEFAULT_EVENT_HANDLER(cnc_reset);
}

// event_rtc_tick_handler
WEAK_EVENT_HANDLER(rtc_tick)
{
	DEFAULT_EVENT_HANDLER(rtc_tick);
}

// event_cnc_dotasks_handler
WEAK_EVENT_HANDLER(cnc_dotasks)
{
	DEFAULT_EVENT_HANDLER(cnc_dotasks);
}

// event_cnc_dotasks_handler
WEAK_EVENT_HANDLER(cnc_io_dotasks)
{
	DEFAULT_EVENT_HANDLER(cnc_io_dotasks);
}

// event_cnc_stop_handler
WEAK_EVENT_HANDLER(cnc_stop)
{
	DEFAULT_EVENT_HANDLER(cnc_stop);
}

// event_cnc_parse_cmd_error_handler
WEAK_EVENT_HANDLER(cnc_parse_cmd_error)
{
	DEFAULT_EVENT_HANDLER(cnc_parse_cmd_error);
}

// event_cnc_alarm
WEAK_EVENT_HANDLER(cnc_alarm)
{
	DEFAULT_EVENT_HANDLER(cnc_alarm);
}

void mcu_enable_global_isr(void) { }
void mcu_disable_global_isr(void) { }
bool mcu_get_global_isr(void) { }

