/*
	Name: boardmap_mks_robin_nano_v1_2.h
	Description: Contains all MCU and PIN definitions for board MKS Robin Nano V1.2 to run µCNC.

	Copyright: Copyright (c) João Martins
	Author: João Martins
	Date: 04/02/2020

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the	GNU General Public License for more details.
*/

#ifndef BOARDMAP_MKS_ROBIN_NANO_V12_H
#define BOARDMAP_MKS_ROBIN_NANO_V12_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef BOARD_NAME
#define BOARD_NAME "SKR Pro 1.2"
#endif

#ifndef STM32F407xx
#define STM32F407xx
#endif

#ifndef F_CPU
#define F_CPU 168000000UL
#endif

#ifndef EXTERNAL_XTAL_MHZ
#define EXTERNAL_XTAL_MHZ 8
#endif

#ifndef FLASH_SIZE
#define FLASH_SIZE 0x100000
#endif

// Setup COM pins
// #define UART_PORT 3

// Setup step pins
#define STEP0_BIT 9	 // assigns STEP0 pin
#define STEP0_PORT E // assigns STEP0 port
#define STEP1_BIT 11	 // assigns STEP1 pin
#define STEP1_PORT E // assigns STEP1 port
#define STEP2_BIT 13	 // assigns STEP2 pin
#define STEP2_PORT E // assigns STEP2 port
#define STEP3_BIT 14	 // assigns STEP3 pin
#define STEP3_PORT E // assigns STEP3 port
#define STEP4_BIT 15	 // assigns STEP4 pin
#define STEP4_PORT D // assigns STEP4 port
#define STEP5_BIT 13	 // assigns STEP5 pin
#define STEP5_PORT D // assigns STEP5 port

// Setup dir pins
#define DIR0_BIT 1	// assigns DIR0 pin
#define DIR0_PORT F // assigns DIR0 port
#define DIR1_BIT 8	// assigns DIR1 pin
#define DIR1_PORT E // assigns DIR1 port
#define DIR2_BIT 2	// assigns DIR2 pin
#define DIR2_PORT C // assigns DIR2 port
#define DIR3_BIT 0	// assigns DIR3 pin
#define DIR3_PORT A // assigns DIR3 port
#define DIR4_BIT 7	// assigns DIR4 pin
#define DIR4_PORT E // assigns DIR4 port
#define DIR5_BIT 9	// assigns DIR5 pin
#define DIR5_PORT G // assigns DIR5 port

// Stepper enable pin. For Grbl on Uno board a single pin is used
#define STEP0_EN_BIT 2
#define STEP0_EN_PORT F
#define STEP1_EN_BIT 7
#define STEP1_EN_PORT D
#define STEP2_EN_BIT 0
#define STEP2_EN_PORT C
#define STEP3_EN_BIT 3
#define STEP3_EN_PORT C
#define STEP4_EN_BIT 3
#define STEP4_EN_PORT A
#define STEP5_EN_BIT 0
#define STEP5_EN_PORT F

// Setup limit pins
#define LIMIT_X_BIT 10	// assigns LIMIT_X pin
#define LIMIT_X_PORT B	// assigns LIMIT_X port
#define LIMIT_Y_BIT 12	// assigns LIMIT_Y pin
#define LIMIT_Y_PORT E	// assigns LIMIT_Y port
#define LIMIT_Z_BIT 8	// assigns LIMIT_Z pin
#define LIMIT_Z_PORT G	// assigns LIMIT_Z port
#define LIMIT_X2_BIT 15	// assigns LIMIT_X2 pin
#define LIMIT_X2_PORT E	// assigns LIMIT_X2 port
#define LIMIT_Y2_BIT 10	// assigns LIMIT_Y2 pin
#define LIMIT_Y2_PORT E	// assigns LIMIT_Y2 port
// #define LIMIT_Z2_BIT 5	// assigns LIMIT_Z2 pin
// #define LIMIT_Z2_PORT G	// assigns LIMIT_Z2 port

// Enable limits switch interrupt
#define LIMIT_X_ISR
#define LIMIT_Y_ISR
#define LIMIT_Z_ISR
#define LIMIT_X2_ISR
#define LIMIT_Y2_ISR
#define LIMIT_Z2_ISR

// Setup probe pin
#define PROBE_BIT 5
#define PROBE_PORT G
#define PROBE_ISR

#if (INTERFACE == INTERFACE_USART)
#define UART_PORT 3
#define TX_BIT 10
#define TX_PORT B
#define RX_BIT 11
#define RX_PORT B
#elif (INTERFACE == INTERFACE_USB)
#define USB_DM_BIT 11
#define USB_DM_PORT A
#define USB_DP_BIT 12
#define USB_DP_PORT A
#endif

// Setup PWM
#define PWM0_BIT 1	// assigns PWM0 pin
#define PWM0_PORT B // assigns PWM0 pin
#define PWM0_CHANNEL 4
#define PWM0_TIMER 3
#define PWM1_BIT 14	// assigns PWM2 pin
#define PWM1_PORT D // assigns PWM2 pin
#define PWM1_CHANNEL 3
#define PWM1_TIMER 4
// #define PWM2_BIT 1	// assigns PWM3 pin
// #define PWM2_PORT B // assigns PWM3 pin
// #define PWM2_CHANNEL 4
// #define PWM2_TIMER 3

// spindle dir
// analog input
// #define ANALOG0_BIT 0
// #define ANALOG0_PORT C
// #define ANALOG0_CHANNEL 10
// #define ANALOG1_BIT 1
// #define ANALOG1_PORT C
// #define ANALOG1_CHANNEL 11
// #define ANALOG2_BIT 2
// #define ANALOG2_PORT C
// #define ANALOG2_CHANNEL 12

// Setup the Step Timer used has the heartbeat for µCNC
#define ITP_TIMER 2
#define SERVO_TIMER 5

//activity led
#define DOUT32_BIT 7
#define DOUT32_PORT A

// TMC0 UART
#define DOUT20_BIT 4
#define DOUT20_PORT E
#define DIN20_BIT 13
#define DIN20_PORT C
#define DIN20_PULLUP

// TMC1 UART
#define DOUT21_BIT 2
#define DOUT21_PORT E
#define DIN21_BIT 3
#define DIN21_PORT E
#define DIN21_PULLUP

// TMC2 UART
#define DOUT22_BIT 0
#define DOUT22_PORT E
#define DIN22_BIT 1
#define DIN22_PORT E
#define DIN22_PULLUP

// TMC3 UART
#define DOUT23_BIT 2
#define DOUT23_PORT D
#define DIN23_BIT 4
#define DIN23_PORT D
#define DIN23_PULLUP

// TMC4 UART
#define DOUT24_BIT 0
#define DOUT24_PORT D
#define DIN24_BIT 1
#define DIN24_PORT D
#define DIN24_PULLUP

// TMC5 UART
#define DOUT25_BIT 5
#define DOUT25_PORT D
#define DIN25_BIT 6
#define DIN25_PORT D
#define DIN25_PULLUP

#ifdef __cplusplus
}
#endif

#endif
