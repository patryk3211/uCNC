/*
	Name: softuart.c
	Description: A software based UART library for µCNC.

	Copyright: Copyright (c) João Martins
	Author: João Martins
	Date: 06-03-2022

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the	GNU General Public License for more details.
*/
#include "softuart.h"

void softuart_putc(softuart_port_t *port, char c)
{
	if (!port)
	{
#if (defined(MCU_HAS_UART2) && defined(DETACH_UART2_FROM_MAIN_PROTOCOL))
		mcu_uart_putc(c);
#endif
	}
	else
	{
		port->tx(false);
		port->wait();
		uint8_t bits = 8;
		do
		{
			if (c & 0x01)
			{
				port->tx(true);
			}
			else
			{
				port->tx(false);
			}
			c >>= 1;
			port->wait();
		} while (--bits);
		port->tx(true);
		port->wait();
	}
}

int16_t softuart_getc(softuart_port_t *port, uint32_t ms_timeout)
{
	char val = 0;

	if (!port)
	{
		return -1;
	}
	else
	{
		ms_timeout += mcu_millis();
		while (port->rx())
		{
			if (ms_timeout < mcu_millis())
			{
				return -1;
			}
		}
		port->waithalf();

		uint8_t bits = 8;
		uint8_t mask = 0x01;
		do
		{
			port->wait();
			if (port->rx())
			{
				val |= mask;
			}
			mask <<= 1;
		} while (--bits);
		port->waithalf();
	}

	return (int16_t)val;
}
