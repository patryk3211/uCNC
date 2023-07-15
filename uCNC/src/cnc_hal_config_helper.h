/*
	Name: cnc_hal_config_helper.h
	Description: Compile time configurations for µCNC. This file takes care of some final configuration definitions based on the user options

	Copyright: Copyright (c) João Martins
	Author: João Martins
	Date: 2022-01-04

	µCNC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. Please see <http://www.gnu.org/licenses/>

	µCNC is distributed WITHOUT ANY WARRANTY;
	Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the	GNU General Public License for more details.
*/

#ifndef CNC_HAL_CONFIG_HELPER_H
#define CNC_HAL_CONFIG_HELPER_H

#ifdef __cplusplus
extern "C"
{
#endif

//undefined pin
#define UNDEF_PIN 0
// assert pin (io or extended)
#define ASSERT_PIN(X) (X != 0)
#define _EVAL_DIO_(X) DIO##X
#define EVAL_DIO(X) DIO##X
// assert pin io
#define ASSERT_PIN_IO(X) (EVAL_DIO(X) > 0)
// assert pin extended
#define ASSERT_PIN_EXTENDED(X) (EVAL_DIO(X) < 0)
// assert pin extended offset
#define ASSERT_IO_OFFSET(X) (X >= 0)

	/**
	 *
	 * Controls limits and probe pins
	 *
	 */

#ifdef DISABLE_ALL_CONTROLS
#ifdef ESTOP
#undef ESTOP
#endif
#ifdef FHOLD
#undef FHOLD
#endif
#ifdef CS_RES
#undef CS_RES
#endif
#ifdef SAFETY_DOOR
#undef SAFETY_DOOR
#endif
#endif

#ifdef DISABLE_ALL_LIMITS
#ifdef LIMIT_X
#undef LIMIT_X
#endif
#ifdef LIMIT_X2
#undef LIMIT_X2
#endif
#ifdef LIMIT_Y
#undef LIMIT_Y
#endif
#ifdef LIMIT_Y2
#undef LIMIT_Y2
#endif
#ifdef LIMIT_Z
#undef LIMIT_Z
#endif
#ifdef LIMIT_Z2
#undef LIMIT_Z2
#endif
#ifdef LIMIT_A
#undef LIMIT_A
#endif
#ifdef LIMIT_B
#undef LIMIT_B
#endif
#ifdef LIMIT_C
#undef LIMIT_C
#endif
#endif

#ifdef DISABLE_PROBE
#ifdef PROBE
#undef PROBE
#endif
#ifndef DISABLE_PROBING_SUPPORT
#define DISABLE_PROBING_SUPPORT
#endif
#endif

#ifdef LIMIT_X_DISABLE
#ifdef LIMIT_X
#undef LIMIT_X
#endif
#endif
#ifdef LIMIT_X2_DISABLE
#ifdef LIMIT_X2
#undef LIMIT_X2
#endif
#endif
#ifdef LIMIT_Y_DISABLE
#ifdef LIMIT_Y
#undef LIMIT_Y
#endif
#endif
#ifdef LIMIT_Y2_DISABLE
#ifdef LIMIT_Y2
#undef LIMIT_Y2
#endif
#endif
#ifdef LIMIT_Z_DISABLE
#ifdef LIMIT_Z
#undef LIMIT_Z
#endif
#endif
#ifdef LIMIT_Z2_DISABLE
#ifdef LIMIT_Z2
#undef LIMIT_Z2
#endif
#endif
#ifdef LIMIT_A_DISABLE
#ifdef LIMIT_A
#undef LIMIT_A
#endif
#endif
#ifdef LIMIT_B_DISABLE
#ifdef LIMIT_B
#undef LIMIT_B
#endif
#endif
#ifdef LIMIT_C_DISABLE
#ifdef LIMIT_C
#undef LIMIT_C
#endif
#endif

#ifdef LIMIT_X_PULLUP_ENABLE
#define LIMIT_X_PULLUP
#endif
#ifdef LIMIT_Y_PULLUP_ENABLE
#define LIMIT_Y_PULLUP
#endif
#ifdef LIMIT_Z_PULLUP_ENABLE
#define LIMIT_Z_PULLUP
#endif
#ifdef LIMIT_X2_PULLUP_ENABLE
#define LIMIT_X2_PULLUP
#endif
#ifdef LIMIT_Y2_PULLUP_ENABLE
#define LIMIT_Y2_PULLUP
#endif
#ifdef LIMIT_Z2_PULLUP_ENABLE
#define LIMIT_Z2_PULLUP
#endif
#ifdef LIMIT_A_PULLUP_ENABLE
#define LIMIT_A_PULLUP
#endif
#ifdef LIMIT_B_PULLUP_ENABLE
#define LIMIT_B_PULLUP
#endif
#ifdef LIMIT_C_PULLUP_ENABLE
#define LIMIT_C_PULLUP
#endif

#ifdef PROBE_PULLUP_ENABLE
#define PROBE_PULLUP
#endif

#ifdef ESTOP_PULLUP_ENABLE
#define ESTOP_PULLUP
#endif
#ifdef SAFETY_DOOR_PULLUP_ENABLE
#define SAFETY_DOOR_PULLUP
#endif
#ifdef FHOLD_PULLUP_ENABLE
#define FHOLD_PULLUP
#endif
#ifdef CS_RES_PULLUP_ENABLE
#define CS_RES_PULLUP
#endif

#ifndef ENCODERS
#define ENCODERS 0
#endif

#if ENCODERS > 0

#if ENCODERS > 0
#if (!ASSERT_PIN(ENC0_PULSE))
#error "The ENC0 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC0_DIR))
#error "The ENC0 dir pin is not defined"
#endif
#define ENC0_MASK (1 << (ENC0_PULSE - DIN_PINS_OFFSET))
#endif
#if ENCODERS > 1
#if (!ASSERT_PIN(ENC1_PULSE))
#error "The ENC1 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC1_DIR))
#error "The ENC1 dir pin is not defined"
#endif
#define ENC1_MASK (1 << ENC1)
#endif
#if ENCODERS > 2
#if (!ASSERT_PIN(ENC2_PULSE))
#error "The ENC2 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC2_DIR))
#error "The ENC2 dir pin is not defined"
#endif
#define ENC2_MASK (1 << ENC2)
#endif
#if ENCODERS > 3
#if (!ASSERT_PIN(ENC3_PULSE))
#error "The ENC3 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC3_DIR))
#error "The ENC3 dir pin is not defined"
#endif
#define ENC3_MASK (1 << ENC3)
#endif
#if ENCODERS > 4
#if (!ASSERT_PIN(ENC4_PULSE))
#error "The ENC4 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC4_DIR))
#error "The ENC4 dir pin is not defined"
#endif
#define ENC4_MASK (1 << ENC4)
#endif
#if ENCODERS > 5
#if (!ASSERT_PIN(ENC5_PULSE))
#error "The ENC5 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC5_DIR))
#error "The ENC5 dir pin is not defined"
#endif
#define ENC5_MASK (1 << ENC5)
#endif
#if ENCODERS > 6
#if (!ASSERT_PIN(ENC6_PULSE))
#error "The ENC6 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC6_DIR))
#error "The ENC6 dir pin is not defined"
#endif
#define ENC6_MASK (1 << ENC6)
#endif
#if ENCODERS > 7
#if (!ASSERT_PIN(ENC7_PULSE))
#error "The ENC7 pulse pin is not defined"
#endif
#if (!ASSERT_PIN(ENC7_DIR))
#error "The ENC7 dir pin is not defined"
#endif
#define ENC7_MASK (1 << ENC7)
#endif
#ifdef ENABLE_ENCODER_RPM
#if (RPM_ENCODER < ENC0 || RPM_ENCODER > ENC7 || ENCODERS < ENCODERS)
#error "The RPM encoder must be assign to one of the available encoders"
#endif
#define __encoder_mask__(X) ENC##X##_MASK
#define encoder_mask(X) __encoder_mask__(X)
#define RPM_ENCODER_MASK encoder_mask(RPM_ENCODER)
#endif

#ifdef STEP0_ENCODER
#define STEP0_ENCODER_MASK (1 << STEP0_ENCODER)
#else
#define STEP0_ENCODER_MASK 0
#endif
#ifdef STEP1_ENCODER
#define STEP1_ENCODER_MASK (1 << STEP1_ENCODER)
#else
#define STEP1_ENCODER_MASK 0
#endif
#ifdef STEP2_ENCODER
#define STEP2_ENCODER_MASK (1 << STEP2_ENCODER)
#else
#define STEP2_ENCODER_MASK 0
#endif
#ifdef STEP3_ENCODER
#define STEP3_ENCODER_MASK (1 << STEP3_ENCODER)
#else
#define STEP3_ENCODER_MASK 0
#endif
#ifdef STEP4_ENCODER
#define STEP4_ENCODER_MASK (1 << STEP4_ENCODER)
#else
#define STEP4_ENCODER_MASK 0
#endif
#ifdef STEP5_ENCODER
#define STEP5_ENCODER_MASK (1 << STEP5_ENCODER)
#else
#define STEP5_ENCODER_MASK 0
#endif

#define STEPPERS_ENCODERS_MASK (STEP0_ENCODER_MASK | STEP1_ENCODER_MASK | STEP2_ENCODER_MASK | STEP3_ENCODER_MASK | STEP4_ENCODER_MASK | STEP5_ENCODER_MASK)

#endif

#ifndef STEPPERS_ENCODERS_MASK
#define STEPPERS_ENCODERS_MASK 0
#endif

#ifndef PID_CONTROLLERS
#define PID_CONTROLLERS 0
#endif

#if PID_CONTROLLERS > 0
	/*PID controllers*/
#if PID_CONTROLLERS == 1
#define PID_DIVISIONS 0
#elif PID_CONTROLLERS == 2
#define PID_DIVISIONS 1
#elif PID_CONTROLLERS <= 4
#define PID_DIVISIONS 2
#else
#define PID_DIVISIONS 3
#endif

#define PID_SAMP_FREQ (1 << (10 - PID_DIVISIONS))
#endif

#if PID_CONTROLLERS > 0
#ifdef PID0_DELTA
#error "The PID0 is reserved for the tool PID"
#else
#define PID0_DELTA() tool_pid_error()
#endif
#ifdef PID0_OUTPUT
#error "The PID0 is reserved for the tool PID"
#else
#define PID0_OUTPUT(X) tool_pid_update(X)
#endif
#ifdef PID0_STOP
#error "The PID0 is reserved for the tool PID"
#else
#define PID0_STOP() tool_stop()
#endif
#ifndef PID0_FREQ_DIV
#define PID0_FREQ_DIV 1
#elif (PID0_FREQ_DIV < 1 || PID0_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID0 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 1
#ifndef PID1_DELTA
#error "The PID1 error is not defined"
#endif
#ifndef PID1_OUTPUT
#error "The PID1 output is not defined"
#endif
#ifndef PID1_STOP
#error "The PID1 stop is not defined"
#endif
#ifndef PID1_FREQ_DIV
#define PID1_FREQ_DIV 1
#elif (PID1_FREQ_DIV < 1 || PID1_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID1 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 2
#ifndef PID2_DELTA
#error "The PID2 error is not defined"
#endif
#ifndef PID2_OUTPUT
#error "The PID2 output is not defined"
#endif
#ifndef PID2_STOP
#error "The PID2 stop is not defined"
#endif
#ifndef PID2_FREQ_DIV
#define PID2_FREQ_DIV 1
#elif (PID2_FREQ_DIV < 1 || PID2_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID2 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 3
#ifndef PID3_DELTA
#error "The PID3 error is not defined"
#endif
#ifndef PID3_OUTPUT
#error "The PID3 output is not defined"
#endif
#ifndef PID3_STOP
#error "The PID3 stop is not defined"
#endif
#ifndef PID3_FREQ_DIV
#define PID3_FREQ_DIV 1
#elif (PID3_FREQ_DIV < 1 || PID3_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID3 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 4
#ifndef PID4_DELTA
#error "The PID4 error is not defined"
#endif
#ifndef PID4_OUTPUT
#error "The PID4 output is not defined"
#endif
#ifndef PID4_STOP
#error "The PID4 stop is not defined"
#endif
#ifndef PID4_FREQ_DIV
#define PID4_FREQ_DIV 1
#elif (PID4_FREQ_DIV < 1 || PID4_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID4 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 5
#ifndef PID5_DELTA
#error "The PID5 error is not defined"
#endif
#ifndef PID5_OUTPUT
#error "The PID5 output is not defined"
#endif
#ifndef PID5_STOP
#error "The PID5 stop is not defined"
#endif
#ifndef PID5_FREQ_DIV
#define PID5_FREQ_DIV 1
#elif (PID5_FREQ_DIV < 1 || PID5_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID5 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 6
#ifndef PID6_DELTA
#error "The PID6 error is not defined"
#endif
#ifndef PID6_OUTPUT
#error "The PID6 output is not defined"
#endif
#ifndef PID6_STOP
#error "The PID6 stop is not defined"
#endif
#ifndef PID6_FREQ_DIV
#define PID6_FREQ_DIV 1
#elif (PID6_FREQ_DIV < 1 || PID6_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID6 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif
#if PID_CONTROLLERS > 7
#ifndef PID7_DELTA
#error "The PID7 error is not defined"
#endif
#ifndef PID7_OUTPUT
#error "The PID7 output is not defined"
#endif
#ifndef PID7_STOP
#error "The PID7 stop is not defined"
#endif
#ifndef PID7_FREQ_DIV
#define PID7_FREQ_DIV 1
#elif (PID7_FREQ_DIV < 1 || PID7_FREQ_DIV > PID_SAMP_FREQ)
#error "The PID7 sampling frequency devider value must be between 1 and MAX SAMPLE RATE = 1000/log2(Total PID's)"
#endif
#endif

#ifdef STEPPER0_HAS_TMC
#if (STEPPER0_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER0_UART_TX) || !ASSERT_PIN(STEPPER0_UART_RX))
#undef STEPPER0_HAS_TMC
#error "Stepper 0 undefined UART pins"
#endif
#elif (STEPPER0_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER0_UART_DO) || !ASSERT_PIN(STEPPER0_UART_DI) || !ASSERT_PIN(STEPPER0_UART_CLK) || !ASSERT_PIN(STEPPER0_UART_CS))
#undef STEPPER0_HAS_TMC
#error "Stepper 0 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER1_HAS_TMC
#if (STEPPER1_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER1_UART_TX) || !ASSERT_PIN(STEPPER1_UART_RX))
#undef STEPPER1_HAS_TMC
#error "Stepper 1 undefined UART pins"
#endif
#elif (STEPPER1_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER1_UART_DO) || !ASSERT_PIN(STEPPER1_UART_DI) || !ASSERT_PIN(STEPPER1_UART_CLK) || !ASSERT_PIN(STEPPER1_UART_CS))
#undef STEPPER1_HAS_TMC
#error "Stepper 1 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER2_HAS_TMC
#if (STEPPER2_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER2_UART_TX) || !ASSERT_PIN(STEPPER2_UART_RX))
#undef STEPPER2_HAS_TMC
#error "Stepper 2 undefined UART pins"
#endif
#elif (STEPPER2_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER2_UART_DO) || !ASSERT_PIN(STEPPER2_UART_DI) || !ASSERT_PIN(STEPPER2_UART_CLK) || !ASSERT_PIN(STEPPER2_UART_CS))
#undef STEPPER2_HAS_TMC
#error "Stepper 2 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER3_HAS_TMC
#if (STEPPER3_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER3_UART_TX) || !ASSERT_PIN(STEPPER3_UART_RX))
#undef STEPPER3_HAS_TMC
#error "Stepper 3 undefined UART pins"
#endif
#elif (STEPPER3_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER3_UART_DO) || !ASSERT_PIN(STEPPER3_UART_DI) || !ASSERT_PIN(STEPPER3_UART_CLK) || !ASSERT_PIN(STEPPER3_UART_CS))
#undef STEPPER3_HAS_TMC
#error "Stepper 3 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER4_HAS_TMC
#if (STEPPER4_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER4_UART_TX) || !ASSERT_PIN(STEPPER4_UART_RX))
#undef STEPPER4_HAS_TMC
#error "Stepper 4 undefined UART pins"
#endif
#elif (STEPPER4_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER4_UART_DO) || !ASSERT_PIN(STEPPER4_UART_DI) || !ASSERT_PIN(STEPPER4_UART_CLK) || !ASSERT_PIN(STEPPER4_UART_CS))
#undef STEPPER4_HAS_TMC
#error "Stepper 4 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER5_HAS_TMC
#if (STEPPER5_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER5_UART_TX) || !ASSERT_PIN(STEPPER5_UART_RX))
#undef STEPPER5_HAS_TMC
#error "Stepper 5 undefined UART pins"
#endif
#elif (STEPPER5_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER5_UART_DO) || !ASSERT_PIN(STEPPER5_UART_DI) || !ASSERT_PIN(STEPPER5_UART_CLK) || !ASSERT_PIN(STEPPER5_UART_CS))
#undef STEPPER5_HAS_TMC
#error "Stepper 5 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER6_HAS_TMC
#if (STEPPER6_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER6_UART_TX) || !ASSERT_PIN(STEPPER6_UART_RX))
#undef STEPPER6_HAS_TMC
#error "Stepper 6 undefined UART pins"
#endif
#elif (STEPPER6_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER6_UART_DO) || !ASSERT_PIN(STEPPER6_UART_DI) || !ASSERT_PIN(STEPPER6_UART_CLK) || !ASSERT_PIN(STEPPER6_UART_CS))
#undef STEPPER6_HAS_TMC
#error "Stepper 6 undefined SPI pins"
#endif
#endif
#endif
#ifdef STEPPER7_HAS_TMC
#if (STEPPER7_TMC_INTERFACE == TMC_UART)
// if driver uses uart set pins
#if (!ASSERT_PIN(STEPPER7_UART_TX) || !ASSERT_PIN(STEPPER7_UART_RX))
#undef STEPPER7_HAS_TMC
#error "Stepper 7 undefined UART pins"
#endif
#elif (STEPPER7_TMC_INTERFACE == TMC_SPI)
#if (!ASSERT_PIN(STEPPER7_UART_DO) || !ASSERT_PIN(STEPPER7_UART_DI) || !ASSERT_PIN(STEPPER7_UART_CLK) || !ASSERT_PIN(STEPPER7_UART_CS))
#undef STEPPER7_HAS_TMC
#error "Stepper 7 undefined SPI pins"
#endif
#endif
#endif

#if defined(STEPPER0_HAS_TMC) || defined(STEPPER1_HAS_TMC) || defined(STEPPER2_HAS_TMC) || defined(STEPPER3_HAS_TMC) || defined(STEPPER4_HAS_TMC) || defined(STEPPER5_HAS_TMC) || defined(STEPPER6_HAS_TMC) || defined(STEPPER7_HAS_TMC)
#define ENABLE_TMC_DRIVERS
#ifndef ENABLE_MAIN_LOOP_MODULES
#define ENABLE_MAIN_LOOP_MODULES
#endif
#endif

#if defined(STEPPER0_HAS_MSTEP) || defined(STEPPER1_HAS_MSTEP) || defined(STEPPER2_HAS_MSTEP) || defined(STEPPER3_HAS_MSTEP) || defined(STEPPER4_HAS_MSTEP) || defined(STEPPER5_HAS_MSTEP) || defined(STEPPER6_HAS_MSTEP) || defined(STEPPER7_HAS_MSTEP)
#define ENABLE_DIGITAL_MSTEP
#endif

#ifdef STEPPER_CURR_DIGIPOT
#ifndef ENABLE_MAIN_LOOP_MODULES
#define ENABLE_MAIN_LOOP_MODULES
#endif
#endif

/*laser ppi*/
#if (TOOL_COUNT < 1)
#undef ENABLE_LASER_PPI
#endif
#ifdef ENABLE_LASER_PPI
#ifndef MCU_HAS_ONESHOT_TIMER
#error "The current MCU does not support ONESHOT_TIMER or the ONESHOT_TIMER is not configured"
#endif
// #ifdef BRESENHAM_16BIT
// #undef BRESENHAM_16BIT
// #warning "BRESENHAM_16BIT was disabled for Laser PPI mode"
// #endif
#ifdef ENABLE_LINACT_PLANNER
#undef ENABLE_LINACT_PLANNER
#warning "ENABLE_LINACT_PLANNER was disabled for Laser PPI mode"
#endif
#if (STEPPER_COUNT == 1)
#undef STEPPER_COUNT
#define STEPPER_COUNT 2
#define LASER_PPI_MASK STEP1_MASK
#elif (STEPPER_COUNT == 2)
#undef STEPPER_COUNT
#define STEPPER_COUNT 3
#define LASER_PPI_MASK STEP2_MASK
#elif (STEPPER_COUNT == 3)
#undef STEPPER_COUNT
#define STEPPER_COUNT 4
#define LASER_PPI_MASK STEP3_MASK
#elif (STEPPER_COUNT == 4)
#undef STEPPER_COUNT
#define STEPPER_COUNT 5
#define LASER_PPI_MASK STEP4_MASK
#elif (STEPPER_COUNT == 5)
#undef STEPPER_COUNT
#define STEPPER_COUNT 6
#define LASER_PPI_MASK STEP5_MASK
#elif (STEPPER_COUNT == 6)
#undef STEPPER_COUNT
#define STEPPER_COUNT 7
#define LASER_PPI_MASK STEP6_MASK
#endif
#ifndef LASER_PPI
#define LASER_PPI -1
#endif
// #ifdef STEP_ISR_SKIP_MAIN
// #undef STEP_ISR_SKIP_MAIN
// #warning "STEP_ISR_SKIP_MAIN was disabled for Laser PPI mode"
// #endif
#else
#define LASER_PPI -1
#endif

#define __stepname_helper__(x) STEP##x##_MASK
#define __stepname__(x) __stepname_helper__(x)

#define __axisname_helper__(x) AXIS_##x
#define __axisname__(x) __axisname_helper__(x)

#define __limitname_helper__(x) LIMIT_##x##_MASK
#define __limitname__(x) __limitname_helper__(x)

#ifdef ENABLE_DUAL_DRIVE_AXIS

#ifndef DUAL_DRIVE0_STEPPER
#define DUAL_DRIVE0_STEPPER 6
#endif
#ifndef DUAL_DRIVE1_STEPPER
#define DUAL_DRIVE1_STEPPER 7
#endif
#ifndef DUAL_DRIVE2_STEPPER
#define DUAL_DRIVE2_STEPPER 6
#endif
#ifndef DUAL_DRIVE3_STEPPER
#define DUAL_DRIVE3_STEPPER 7
#endif

#if (!defined(DUAL_DRIVE0_AXIS) && !defined(DUAL_DRIVE1_AXIS) && !defined(DUAL_DRIVE2_AXIS) && !defined(DUAL_DRIVE3_AXIS))
#error "Enabling dual axis drive requires to configure at least one axis with dual drive"
#endif

#if (STEPPER_COUNT > 0 && (DUAL_DRIVE0_STEPPER == 0 || DUAL_DRIVE1_STEPPER == 0 || DUAL_DRIVE2_STEPPER == 0 || DUAL_DRIVE3_STEPPER == 0))
#error "Stepper 0 cannot be used as a axis drive and a dual axis drive at the same time"
#endif
#if (STEPPER_COUNT > 1 && (DUAL_DRIVE0_STEPPER == 1 || DUAL_DRIVE1_STEPPER == 1 || DUAL_DRIVE2_STEPPER == 1 || DUAL_DRIVE3_STEPPER == 1))
#error "Stepper 1 cannot be used as a axis drive and a dual axis drive at the same time"
#endif
#if (STEPPER_COUNT > 2 && (DUAL_DRIVE0_STEPPER == 2 || DUAL_DRIVE1_STEPPER == 2 || DUAL_DRIVE2_STEPPER == 2 || DUAL_DRIVE3_STEPPER == 2))
#error "Stepper 2 cannot be used as a axis drive and a dual axis drive at the same time"
#endif
#if (STEPPER_COUNT > 3 && (DUAL_DRIVE0_STEPPER == 3 || DUAL_DRIVE1_STEPPER == 3 || DUAL_DRIVE2_STEPPER == 3 || DUAL_DRIVE3_STEPPER == 3))
#error "Stepper 3 cannot be used as a axis drive and a dual axis drive at the same time"
#endif
#if (STEPPER_COUNT > 4 && (DUAL_DRIVE0_STEPPER == 4 || DUAL_DRIVE1_STEPPER == 4 || DUAL_DRIVE2_STEPPER == 4 || DUAL_DRIVE3_STEPPER == 4))
#error "Stepper 4 cannot be used as a axis drive and a dual axis drive at the same time"
#endif
#if (STEPPER_COUNT > 5 && (DUAL_DRIVE0_STEPPER == 5 || DUAL_DRIVE1_STEPPER == 5 || DUAL_DRIVE2_STEPPER == 5 || DUAL_DRIVE3_STEPPER == 5))
#error "Stepper 5 cannot be used as a axis drive and a dual axis drive at the same time"
#endif

// dual axis0
#ifdef DUAL_DRIVE0_AXIS
#define AXIS_DUAL0 __axisname__(DUAL_DRIVE0_AXIS)
#define STEP_DUAL0 (1 << AXIS_DUAL0)
#ifdef DUAL_DRIVE0_ENABLE_SELFSQUARING
#define LIMIT_DUAL0_MASK (1 << AXIS_DUAL0)
#endif
#define STEP_DUAL0_MASK (1 << DUAL_DRIVE0_STEPPER)
#endif

// dual axis1
#ifdef DUAL_DRIVE1_AXIS
#define AXIS_DUAL1 __axisname__(DUAL_DRIVE1_AXIS)
#define STEP_DUAL1 (1 << AXIS_DUAL1)
#ifdef DUAL_DRIVE1_ENABLE_SELFSQUARING
#define LIMIT_DUAL1_MASK (1 << AXIS_DUAL1)
#endif
#define STEP_DUAL1_MASK (1 << DUAL_DRIVE1_STEPPER)
#endif

// axis2 and 3 are only replicating axis (no self-squaring)

// dual axis2
#ifdef DUAL_DRIVE2_AXIS
#define AXIS_DUAL2 __axisname__(DUAL_DRIVE2_AXIS)
#define STEP_DUAL2 (1 << AXIS_DUAL2)
#define STEP_DUAL2_MASK (1 << DUAL_DRIVE2_STEPPER)
#endif

// dual axis3
#ifdef DUAL_DRIVE3_AXIS
#define AXIS_DUAL3 __axisname__(DUAL_DRIVE3_AXIS)
#define STEP_DUAL3 (1 << AXIS_DUAL3)
#define STEP_DUAL3_MASK (1 << DUAL_DRIVE3_STEPPER)
#endif

#endif

#ifndef LIMIT_DUAL0_MASK
#define LIMIT_DUAL0_MASK 0
#endif
#ifndef LIMIT_DUAL1_MASK
#define LIMIT_DUAL1_MASK 0
#endif

#define LIMITS_DUAL_MASK (LIMIT_DUAL0_MASK | LIMIT_DUAL1_MASK)

#if (STEP0_MASK == STEP_DUAL0)
#define STEP0_ITP_MASK (STEP0_MASK | STEP_DUAL0_MASK)
#elif (STEP0_MASK == STEP_DUAL1)
#define STEP0_ITP_MASK (STEP0_MASK | STEP_DUAL1_MASK)
#elif (STEP0_MASK == STEP_DUAL2)
#define STEP0_ITP_MASK (STEP0_MASK | STEP_DUAL2_MASK)
#elif (STEP0_MASK == STEP_DUAL3)
#define STEP0_ITP_MASK (STEP0_MASK | STEP_DUAL3_MASK)
#else
#define STEP0_ITP_MASK STEP0_MASK
#endif
#if (STEP1_MASK == STEP_DUAL0)
#define STEP1_ITP_MASK (STEP1_MASK | STEP_DUAL0_MASK)
#elif (STEP1_MASK == STEP_DUAL1)
#define STEP1_ITP_MASK (STEP1_MASK | STEP_DUAL1_MASK)
#elif (STEP1_MASK == STEP_DUAL2)
#define STEP1_ITP_MASK (STEP1_MASK | STEP_DUAL2_MASK)
#elif (STEP1_MASK == STEP_DUAL3)
#define STEP1_ITP_MASK (STEP1_MASK | STEP_DUAL3_MASK)
#else
#define STEP1_ITP_MASK STEP1_MASK
#endif
#if (STEP2_MASK == STEP_DUAL0)
#define STEP2_ITP_MASK (STEP2_MASK | STEP_DUAL0_MASK)
#elif (STEP2_MASK == STEP_DUAL1)
#define STEP2_ITP_MASK (STEP2_MASK | STEP_DUAL1_MASK)
#elif (STEP2_MASK == STEP_DUAL2)
#define STEP2_ITP_MASK (STEP2_MASK | STEP_DUAL2_MASK)
#elif (STEP2_MASK == STEP_DUAL3)
#define STEP2_ITP_MASK (STEP2_MASK | STEP_DUAL3_MASK)
#else
#define STEP2_ITP_MASK STEP2_MASK
#endif
#if (STEP3_MASK == STEP_DUAL0)
#define STEP3_ITP_MASK (STEP3_MASK | STEP_DUAL0_MASK)
#elif (STEP3_MASK == STEP_DUAL1)
#define STEP3_ITP_MASK (STEP3_MASK | STEP_DUAL1_MASK)
#elif (STEP3_MASK == STEP_DUAL2)
#define STEP3_ITP_MASK (STEP3_MASK | STEP_DUAL2_MASK)
#elif (STEP3_MASK == STEP_DUAL3)
#define STEP3_ITP_MASK (STEP3_MASK | STEP_DUAL3_MASK)
#else
#define STEP3_ITP_MASK STEP3_MASK
#endif
#if (STEP5_MASK == STEP_DUAL0)
#define STEP5_ITP_MASK (STEP5_MASK | STEP_DUAL0_MASK)
#elif (STEP5_MASK == STEP_DUAL1)
#define STEP5_ITP_MASK (STEP5_MASK | STEP_DUAL1_MASK)
#elif (STEP5_MASK == STEP_DUAL2)
#define STEP5_ITP_MASK (STEP5_MASK | STEP_DUAL2_MASK)
#elif (STEP5_MASK == STEP_DUAL3)
#define STEP5_ITP_MASK (STEP5_MASK | STEP_DUAL3_MASK)
#else
#define STEP5_ITP_MASK STEP5_MASK
#endif

#ifndef STEP_DUAL0
#define STEP_DUAL0 -1
#endif

#ifndef STEP_DUAL1
#define STEP_DUAL1 -1
#endif

#ifndef STEP_DUAL2
#define STEP_DUAL2 -1
#endif

#ifndef STEP_DUAL3
#define STEP_DUAL3 -1
#endif

#if (STEPPER_COUNT < 1 && DUAL_DRIVE0_STEPPER != 0 && DUAL_DRIVE1_STEPPER != 0 && DUAL_DRIVE2_STEPPER != 0 && DUAL_DRIVE3_STEPPER != 0)
#ifdef STEP0
#undef STEP0
#endif
#ifdef DIR0
#undef DIR0
#endif
#endif
#if (STEPPER_COUNT < 2 && DUAL_DRIVE0_STEPPER != 1 && DUAL_DRIVE1_STEPPER != 1 && DUAL_DRIVE2_STEPPER != 1 && DUAL_DRIVE3_STEPPER != 1)
#ifdef STEP1
#undef STEP1
#endif
#ifdef DIR1
#undef DIR1
#endif
#endif
#if (STEPPER_COUNT < 3 && DUAL_DRIVE0_STEPPER != 2 && DUAL_DRIVE1_STEPPER != 2 && DUAL_DRIVE2_STEPPER != 2 && DUAL_DRIVE3_STEPPER != 2)
#ifdef STEP2
#undef STEP2
#endif
#ifdef DIR2
#undef DIR2
#endif
#endif
#if (STEPPER_COUNT < 4 && DUAL_DRIVE0_STEPPER != 3 && DUAL_DRIVE1_STEPPER != 3 && DUAL_DRIVE2_STEPPER != 3 && DUAL_DRIVE3_STEPPER != 3)
#ifdef STEP3
#undef STEP3
#endif
#ifdef DIR3
#undef DIR3
#endif
#endif
#if (STEPPER_COUNT < 5 && DUAL_DRIVE0_STEPPER != 4 && DUAL_DRIVE1_STEPPER != 4 && DUAL_DRIVE2_STEPPER != 4 && DUAL_DRIVE3_STEPPER != 4)
#ifdef STEP4
#undef STEP4
#endif
#ifdef DIR4
#undef DIR4
#endif
#endif
#if (STEPPER_COUNT < 6 && DUAL_DRIVE0_STEPPER != 5 && DUAL_DRIVE1_STEPPER != 5 && DUAL_DRIVE2_STEPPER != 5 && DUAL_DRIVE3_STEPPER != 5)
#ifdef STEP5
#undef STEP5
#endif
#ifdef DIR5
#undef DIR5
#endif
#endif
#if (DUAL_DRIVE0_STEPPER != 6 && DUAL_DRIVE1_STEPPER != 6 && DUAL_DRIVE2_STEPPER != 6 && DUAL_DRIVE3_STEPPER != 6)
#ifdef STEP6
#undef STEP6
#endif
#ifdef DIR6
#undef DIR6
#endif
#endif
#if (DUAL_DRIVE0_STEPPER != 7 && DUAL_DRIVE1_STEPPER != 7 && DUAL_DRIVE2_STEPPER != 7 && DUAL_DRIVE3_STEPPER != 7)
#ifdef STEP7
#undef STEP7
#endif
#ifdef DIR7
#undef DIR7
#endif
#endif

/**
 * final pin cleaning and configuration
 **/
#ifndef STEP0
#define STEP0 UNDEF_PIN
#ifdef DIO1
#undef DIO1
#endif
#define DIO1 UNDEF_PIN
#endif
#ifndef STEP1
#define STEP1 UNDEF_PIN
#ifdef DIO2
#undef DIO2
#endif
#define DIO2 UNDEF_PIN
#endif
#ifndef STEP2
#define STEP2 UNDEF_PIN
#ifdef DIO3
#undef DIO3
#endif
#define DIO3 UNDEF_PIN
#endif
#ifndef STEP3
#define STEP3 UNDEF_PIN
#ifdef DIO4
#undef DIO4
#endif
#define DIO4 UNDEF_PIN
#endif
#ifndef STEP4
#define STEP4 UNDEF_PIN
#ifdef DIO5
#undef DIO5
#endif
#define DIO5 UNDEF_PIN
#endif
#ifndef STEP5
#define STEP5 UNDEF_PIN
#ifdef DIO6
#undef DIO6
#endif
#define DIO6 UNDEF_PIN
#endif
#ifndef STEP6
#define STEP6 UNDEF_PIN
#ifdef DIO7
#undef DIO7
#endif
#define DIO7 UNDEF_PIN
#endif
#ifndef STEP7
#define STEP7 UNDEF_PIN
#ifdef DIO8
#undef DIO8
#endif
#define DIO8 UNDEF_PIN
#endif
#ifndef DIR0
#define DIR0 UNDEF_PIN
#ifdef DIO9
#undef DIO9
#endif
#define DIO9 UNDEF_PIN
#endif
#ifndef DIR1
#define DIR1 UNDEF_PIN
#ifdef DIO10
#undef DIO10
#endif
#define DIO10 UNDEF_PIN
#endif
#ifndef DIR2
#define DIR2 UNDEF_PIN
#ifdef DIO11
#undef DIO11
#endif
#define DIO11 UNDEF_PIN
#endif
#ifndef DIR3
#define DIR3 UNDEF_PIN
#ifdef DIO12
#undef DIO12
#endif
#define DIO12 UNDEF_PIN
#endif
#ifndef DIR4
#define DIR4 UNDEF_PIN
#ifdef DIO13
#undef DIO13
#endif
#define DIO13 UNDEF_PIN
#endif
#ifndef DIR5
#define DIR5 UNDEF_PIN
#ifdef DIO14
#undef DIO14
#endif
#define DIO14 UNDEF_PIN
#endif
#ifndef DIR6
#define DIR6 UNDEF_PIN
#ifdef DIO15
#undef DIO15
#endif
#define DIO15 UNDEF_PIN
#endif
#ifndef DIR7
#define DIR7 UNDEF_PIN
#ifdef DIO16
#undef DIO16
#endif
#define DIO16 UNDEF_PIN
#endif
#ifndef STEP0_EN
#define STEP0_EN UNDEF_PIN
#ifdef DIO17
#undef DIO17
#endif
#define DIO17 UNDEF_PIN
#endif
#ifndef STEP1_EN
#define STEP1_EN UNDEF_PIN
#ifdef DIO18
#undef DIO18
#endif
#define DIO18 UNDEF_PIN
#endif
#ifndef STEP2_EN
#define STEP2_EN UNDEF_PIN
#ifdef DIO19
#undef DIO19
#endif
#define DIO19 UNDEF_PIN
#endif
#ifndef STEP3_EN
#define STEP3_EN UNDEF_PIN
#ifdef DIO20
#undef DIO20
#endif
#define DIO20 UNDEF_PIN
#endif
#ifndef STEP4_EN
#define STEP4_EN UNDEF_PIN
#ifdef DIO21
#undef DIO21
#endif
#define DIO21 UNDEF_PIN
#endif
#ifndef STEP5_EN
#define STEP5_EN UNDEF_PIN
#ifdef DIO22
#undef DIO22
#endif
#define DIO22 UNDEF_PIN
#endif
#ifndef STEP6_EN
#define STEP6_EN UNDEF_PIN
#ifdef DIO23
#undef DIO23
#endif
#define DIO23 UNDEF_PIN
#endif
#ifndef STEP7_EN
#define STEP7_EN UNDEF_PIN
#ifdef DIO24
#undef DIO24
#endif
#define DIO24 UNDEF_PIN
#endif
#ifndef PWM0
#define PWM0 UNDEF_PIN
#ifdef DIO25
#undef DIO25
#endif
#define DIO25 UNDEF_PIN
#endif
#ifndef PWM1
#define PWM1 UNDEF_PIN
#ifdef DIO26
#undef DIO26
#endif
#define DIO26 UNDEF_PIN
#endif
#ifndef PWM2
#define PWM2 UNDEF_PIN
#ifdef DIO27
#undef DIO27
#endif
#define DIO27 UNDEF_PIN
#endif
#ifndef PWM3
#define PWM3 UNDEF_PIN
#ifdef DIO28
#undef DIO28
#endif
#define DIO28 UNDEF_PIN
#endif
#ifndef PWM4
#define PWM4 UNDEF_PIN
#ifdef DIO29
#undef DIO29
#endif
#define DIO29 UNDEF_PIN
#endif
#ifndef PWM5
#define PWM5 UNDEF_PIN
#ifdef DIO30
#undef DIO30
#endif
#define DIO30 UNDEF_PIN
#endif
#ifndef PWM6
#define PWM6 UNDEF_PIN
#ifdef DIO31
#undef DIO31
#endif
#define DIO31 UNDEF_PIN
#endif
#ifndef PWM7
#define PWM7 UNDEF_PIN
#ifdef DIO32
#undef DIO32
#endif
#define DIO32 UNDEF_PIN
#endif
#ifndef PWM8
#define PWM8 UNDEF_PIN
#ifdef DIO33
#undef DIO33
#endif
#define DIO33 UNDEF_PIN
#endif
#ifndef PWM9
#define PWM9 UNDEF_PIN
#ifdef DIO34
#undef DIO34
#endif
#define DIO34 UNDEF_PIN
#endif
#ifndef PWM10
#define PWM10 UNDEF_PIN
#ifdef DIO35
#undef DIO35
#endif
#define DIO35 UNDEF_PIN
#endif
#ifndef PWM11
#define PWM11 UNDEF_PIN
#ifdef DIO36
#undef DIO36
#endif
#define DIO36 UNDEF_PIN
#endif
#ifndef PWM12
#define PWM12 UNDEF_PIN
#ifdef DIO37
#undef DIO37
#endif
#define DIO37 UNDEF_PIN
#endif
#ifndef PWM13
#define PWM13 UNDEF_PIN
#ifdef DIO38
#undef DIO38
#endif
#define DIO38 UNDEF_PIN
#endif
#ifndef PWM14
#define PWM14 UNDEF_PIN
#ifdef DIO39
#undef DIO39
#endif
#define DIO39 UNDEF_PIN
#endif
#ifndef PWM15
#define PWM15 UNDEF_PIN
#ifdef DIO40
#undef DIO40
#endif
#define DIO40 UNDEF_PIN
#endif
#ifndef SERVO0
#define SERVO0 UNDEF_PIN
#ifdef DIO41
#undef DIO41
#endif
#define DIO41 UNDEF_PIN
#endif
#ifndef SERVO1
#define SERVO1 UNDEF_PIN
#ifdef DIO42
#undef DIO42
#endif
#define DIO42 UNDEF_PIN
#endif
#ifndef SERVO2
#define SERVO2 UNDEF_PIN
#ifdef DIO43
#undef DIO43
#endif
#define DIO43 UNDEF_PIN
#endif
#ifndef SERVO3
#define SERVO3 UNDEF_PIN
#ifdef DIO44
#undef DIO44
#endif
#define DIO44 UNDEF_PIN
#endif
#ifndef SERVO4
#define SERVO4 UNDEF_PIN
#ifdef DIO45
#undef DIO45
#endif
#define DIO45 UNDEF_PIN
#endif
#ifndef SERVO5
#define SERVO5 UNDEF_PIN
#ifdef DIO46
#undef DIO46
#endif
#define DIO46 UNDEF_PIN
#endif
#ifndef DOUT0
#define DOUT0 UNDEF_PIN
#ifdef DIO47
#undef DIO47
#endif
#define DIO47 UNDEF_PIN
#endif
#ifndef DOUT1
#define DOUT1 UNDEF_PIN
#ifdef DIO48
#undef DIO48
#endif
#define DIO48 UNDEF_PIN
#endif
#ifndef DOUT2
#define DOUT2 UNDEF_PIN
#ifdef DIO49
#undef DIO49
#endif
#define DIO49 UNDEF_PIN
#endif
#ifndef DOUT3
#define DOUT3 UNDEF_PIN
#ifdef DIO50
#undef DIO50
#endif
#define DIO50 UNDEF_PIN
#endif
#ifndef DOUT4
#define DOUT4 UNDEF_PIN
#ifdef DIO51
#undef DIO51
#endif
#define DIO51 UNDEF_PIN
#endif
#ifndef DOUT5
#define DOUT5 UNDEF_PIN
#ifdef DIO52
#undef DIO52
#endif
#define DIO52 UNDEF_PIN
#endif
#ifndef DOUT6
#define DOUT6 UNDEF_PIN
#ifdef DIO53
#undef DIO53
#endif
#define DIO53 UNDEF_PIN
#endif
#ifndef DOUT7
#define DOUT7 UNDEF_PIN
#ifdef DIO54
#undef DIO54
#endif
#define DIO54 UNDEF_PIN
#endif
#ifndef DOUT8
#define DOUT8 UNDEF_PIN
#ifdef DIO55
#undef DIO55
#endif
#define DIO55 UNDEF_PIN
#endif
#ifndef DOUT9
#define DOUT9 UNDEF_PIN
#ifdef DIO56
#undef DIO56
#endif
#define DIO56 UNDEF_PIN
#endif
#ifndef DOUT10
#define DOUT10 UNDEF_PIN
#ifdef DIO57
#undef DIO57
#endif
#define DIO57 UNDEF_PIN
#endif
#ifndef DOUT11
#define DOUT11 UNDEF_PIN
#ifdef DIO58
#undef DIO58
#endif
#define DIO58 UNDEF_PIN
#endif
#ifndef DOUT12
#define DOUT12 UNDEF_PIN
#ifdef DIO59
#undef DIO59
#endif
#define DIO59 UNDEF_PIN
#endif
#ifndef DOUT13
#define DOUT13 UNDEF_PIN
#ifdef DIO60
#undef DIO60
#endif
#define DIO60 UNDEF_PIN
#endif
#ifndef DOUT14
#define DOUT14 UNDEF_PIN
#ifdef DIO61
#undef DIO61
#endif
#define DIO61 UNDEF_PIN
#endif
#ifndef DOUT15
#define DOUT15 UNDEF_PIN
#ifdef DIO62
#undef DIO62
#endif
#define DIO62 UNDEF_PIN
#endif
#ifndef DOUT16
#define DOUT16 UNDEF_PIN
#ifdef DIO63
#undef DIO63
#endif
#define DIO63 UNDEF_PIN
#endif
#ifndef DOUT17
#define DOUT17 UNDEF_PIN
#ifdef DIO64
#undef DIO64
#endif
#define DIO64 UNDEF_PIN
#endif
#ifndef DOUT18
#define DOUT18 UNDEF_PIN
#ifdef DIO65
#undef DIO65
#endif
#define DIO65 UNDEF_PIN
#endif
#ifndef DOUT19
#define DOUT19 UNDEF_PIN
#ifdef DIO66
#undef DIO66
#endif
#define DIO66 UNDEF_PIN
#endif
#ifndef DOUT20
#define DOUT20 UNDEF_PIN
#ifdef DIO67
#undef DIO67
#endif
#define DIO67 UNDEF_PIN
#endif
#ifndef DOUT21
#define DOUT21 UNDEF_PIN
#ifdef DIO68
#undef DIO68
#endif
#define DIO68 UNDEF_PIN
#endif
#ifndef DOUT22
#define DOUT22 UNDEF_PIN
#ifdef DIO69
#undef DIO69
#endif
#define DIO69 UNDEF_PIN
#endif
#ifndef DOUT23
#define DOUT23 UNDEF_PIN
#ifdef DIO70
#undef DIO70
#endif
#define DIO70 UNDEF_PIN
#endif
#ifndef DOUT24
#define DOUT24 UNDEF_PIN
#ifdef DIO71
#undef DIO71
#endif
#define DIO71 UNDEF_PIN
#endif
#ifndef DOUT25
#define DOUT25 UNDEF_PIN
#ifdef DIO72
#undef DIO72
#endif
#define DIO72 UNDEF_PIN
#endif
#ifndef DOUT26
#define DOUT26 UNDEF_PIN
#ifdef DIO73
#undef DIO73
#endif
#define DIO73 UNDEF_PIN
#endif
#ifndef DOUT27
#define DOUT27 UNDEF_PIN
#ifdef DIO74
#undef DIO74
#endif
#define DIO74 UNDEF_PIN
#endif
#ifndef DOUT28
#define DOUT28 UNDEF_PIN
#ifdef DIO75
#undef DIO75
#endif
#define DIO75 UNDEF_PIN
#endif
#ifndef DOUT29
#define DOUT29 UNDEF_PIN
#ifdef DIO76
#undef DIO76
#endif
#define DIO76 UNDEF_PIN
#endif
#ifndef DOUT30
#define DOUT30 UNDEF_PIN
#ifdef DIO77
#undef DIO77
#endif
#define DIO77 UNDEF_PIN
#endif
#ifndef DOUT31
#define DOUT31 UNDEF_PIN
#ifdef DIO78
#undef DIO78
#endif
#define DIO78 UNDEF_PIN
#endif
#ifndef LIMIT_X
#define LIMIT_X UNDEF_PIN
#ifdef DIO100
#undef DIO100
#endif
#define DIO100 UNDEF_PIN
#endif
#ifndef LIMIT_Y
#define LIMIT_Y UNDEF_PIN
#ifdef DIO101
#undef DIO101
#endif
#define DIO101 UNDEF_PIN
#endif
#ifndef LIMIT_Z
#define LIMIT_Z UNDEF_PIN
#ifdef DIO102
#undef DIO102
#endif
#define DIO102 UNDEF_PIN
#endif
#ifndef LIMIT_X2
#define LIMIT_X2 UNDEF_PIN
#ifdef DIO103
#undef DIO103
#endif
#define DIO103 UNDEF_PIN
#endif
#ifndef LIMIT_Y2
#define LIMIT_Y2 UNDEF_PIN
#ifdef DIO104
#undef DIO104
#endif
#define DIO104 UNDEF_PIN
#endif
#ifndef LIMIT_Z2
#define LIMIT_Z2 UNDEF_PIN
#ifdef DIO105
#undef DIO105
#endif
#define DIO105 UNDEF_PIN
#endif
#ifndef LIMIT_A
#define LIMIT_A UNDEF_PIN
#ifdef DIO106
#undef DIO106
#endif
#define DIO106 UNDEF_PIN
#endif
#ifndef LIMIT_B
#define LIMIT_B UNDEF_PIN
#ifdef DIO107
#undef DIO107
#endif
#define DIO107 UNDEF_PIN
#endif
#ifndef LIMIT_C
#define LIMIT_C UNDEF_PIN
#ifdef DIO108
#undef DIO108
#endif
#define DIO108 UNDEF_PIN
#endif
#ifndef PROBE
#define PROBE UNDEF_PIN
#ifdef DIO109
#undef DIO109
#endif
#define DIO109 UNDEF_PIN
#endif
#ifndef ESTOP
#define ESTOP UNDEF_PIN
#ifdef DIO110
#undef DIO110
#endif
#define DIO110 UNDEF_PIN
#endif
#ifndef SAFETY_DOOR
#define SAFETY_DOOR UNDEF_PIN
#ifdef DIO111
#undef DIO111
#endif
#define DIO111 UNDEF_PIN
#endif
#ifndef FHOLD
#define FHOLD UNDEF_PIN
#ifdef DIO112
#undef DIO112
#endif
#define DIO112 UNDEF_PIN
#endif
#ifndef CS_RES
#define CS_RES UNDEF_PIN
#ifdef DIO113
#undef DIO113
#endif
#define DIO113 UNDEF_PIN
#endif
#ifndef ANALOG0
#define ANALOG0 UNDEF_PIN
#ifdef DIO114
#undef DIO114
#endif
#define DIO114 UNDEF_PIN
#endif
#ifndef ANALOG1
#define ANALOG1 UNDEF_PIN
#ifdef DIO115
#undef DIO115
#endif
#define DIO115 UNDEF_PIN
#endif
#ifndef ANALOG2
#define ANALOG2 UNDEF_PIN
#ifdef DIO116
#undef DIO116
#endif
#define DIO116 UNDEF_PIN
#endif
#ifndef ANALOG3
#define ANALOG3 UNDEF_PIN
#ifdef DIO117
#undef DIO117
#endif
#define DIO117 UNDEF_PIN
#endif
#ifndef ANALOG4
#define ANALOG4 UNDEF_PIN
#ifdef DIO118
#undef DIO118
#endif
#define DIO118 UNDEF_PIN
#endif
#ifndef ANALOG5
#define ANALOG5 UNDEF_PIN
#ifdef DIO119
#undef DIO119
#endif
#define DIO119 UNDEF_PIN
#endif
#ifndef ANALOG6
#define ANALOG6 UNDEF_PIN
#ifdef DIO120
#undef DIO120
#endif
#define DIO120 UNDEF_PIN
#endif
#ifndef ANALOG7
#define ANALOG7 UNDEF_PIN
#ifdef DIO121
#undef DIO121
#endif
#define DIO121 UNDEF_PIN
#endif
#ifndef ANALOG8
#define ANALOG8 UNDEF_PIN
#ifdef DIO122
#undef DIO122
#endif
#define DIO122 UNDEF_PIN
#endif
#ifndef ANALOG9
#define ANALOG9 UNDEF_PIN
#ifdef DIO123
#undef DIO123
#endif
#define DIO123 UNDEF_PIN
#endif
#ifndef ANALOG10
#define ANALOG10 UNDEF_PIN
#ifdef DIO124
#undef DIO124
#endif
#define DIO124 UNDEF_PIN
#endif
#ifndef ANALOG11
#define ANALOG11 UNDEF_PIN
#ifdef DIO125
#undef DIO125
#endif
#define DIO125 UNDEF_PIN
#endif
#ifndef ANALOG12
#define ANALOG12 UNDEF_PIN
#ifdef DIO126
#undef DIO126
#endif
#define DIO126 UNDEF_PIN
#endif
#ifndef ANALOG13
#define ANALOG13 UNDEF_PIN
#ifdef DIO127
#undef DIO127
#endif
#define DIO127 UNDEF_PIN
#endif
#ifndef ANALOG14
#define ANALOG14 UNDEF_PIN
#ifdef DIO128
#undef DIO128
#endif
#define DIO128 UNDEF_PIN
#endif
#ifndef ANALOG15
#define ANALOG15 UNDEF_PIN
#ifdef DIO129
#undef DIO129
#endif
#define DIO129 UNDEF_PIN
#endif
#ifndef DIN0
#define DIN0 UNDEF_PIN
#ifdef DIO130
#undef DIO130
#endif
#define DIO130 UNDEF_PIN
#endif
#ifndef DIN1
#define DIN1 UNDEF_PIN
#ifdef DIO131
#undef DIO131
#endif
#define DIO131 UNDEF_PIN
#endif
#ifndef DIN2
#define DIN2 UNDEF_PIN
#ifdef DIO132
#undef DIO132
#endif
#define DIO132 UNDEF_PIN
#endif
#ifndef DIN3
#define DIN3 UNDEF_PIN
#ifdef DIO133
#undef DIO133
#endif
#define DIO133 UNDEF_PIN
#endif
#ifndef DIN4
#define DIN4 UNDEF_PIN
#ifdef DIO134
#undef DIO134
#endif
#define DIO134 UNDEF_PIN
#endif
#ifndef DIN5
#define DIN5 UNDEF_PIN
#ifdef DIO135
#undef DIO135
#endif
#define DIO135 UNDEF_PIN
#endif
#ifndef DIN6
#define DIN6 UNDEF_PIN
#ifdef DIO136
#undef DIO136
#endif
#define DIO136 UNDEF_PIN
#endif
#ifndef DIN7
#define DIN7 UNDEF_PIN
#ifdef DIO137
#undef DIO137
#endif
#define DIO137 UNDEF_PIN
#endif
#ifndef DIN8
#define DIN8 UNDEF_PIN
#ifdef DIO138
#undef DIO138
#endif
#define DIO138 UNDEF_PIN
#endif
#ifndef DIN9
#define DIN9 UNDEF_PIN
#ifdef DIO139
#undef DIO139
#endif
#define DIO139 UNDEF_PIN
#endif
#ifndef DIN10
#define DIN10 UNDEF_PIN
#ifdef DIO140
#undef DIO140
#endif
#define DIO140 UNDEF_PIN
#endif
#ifndef DIN11
#define DIN11 UNDEF_PIN
#ifdef DIO141
#undef DIO141
#endif
#define DIO141 UNDEF_PIN
#endif
#ifndef DIN12
#define DIN12 UNDEF_PIN
#ifdef DIO142
#undef DIO142
#endif
#define DIO142 UNDEF_PIN
#endif
#ifndef DIN13
#define DIN13 UNDEF_PIN
#ifdef DIO143
#undef DIO143
#endif
#define DIO143 UNDEF_PIN
#endif
#ifndef DIN14
#define DIN14 UNDEF_PIN
#ifdef DIO144
#undef DIO144
#endif
#define DIO144 UNDEF_PIN
#endif
#ifndef DIN15
#define DIN15 UNDEF_PIN
#ifdef DIO145
#undef DIO145
#endif
#define DIO145 UNDEF_PIN
#endif
#ifndef DIN16
#define DIN16 UNDEF_PIN
#ifdef DIO146
#undef DIO146
#endif
#define DIO146 UNDEF_PIN
#endif
#ifndef DIN17
#define DIN17 UNDEF_PIN
#ifdef DIO147
#undef DIO147
#endif
#define DIO147 UNDEF_PIN
#endif
#ifndef DIN18
#define DIN18 UNDEF_PIN
#ifdef DIO148
#undef DIO148
#endif
#define DIO148 UNDEF_PIN
#endif
#ifndef DIN19
#define DIN19 UNDEF_PIN
#ifdef DIO149
#undef DIO149
#endif
#define DIO149 UNDEF_PIN
#endif
#ifndef DIN20
#define DIN20 UNDEF_PIN
#ifdef DIO150
#undef DIO150
#endif
#define DIO150 UNDEF_PIN
#endif
#ifndef DIN21
#define DIN21 UNDEF_PIN
#ifdef DIO151
#undef DIO151
#endif
#define DIO151 UNDEF_PIN
#endif
#ifndef DIN22
#define DIN22 UNDEF_PIN
#ifdef DIO152
#undef DIO152
#endif
#define DIO152 UNDEF_PIN
#endif
#ifndef DIN23
#define DIN23 UNDEF_PIN
#ifdef DIO153
#undef DIO153
#endif
#define DIO153 UNDEF_PIN
#endif
#ifndef DIN24
#define DIN24 UNDEF_PIN
#ifdef DIO154
#undef DIO154
#endif
#define DIO154 UNDEF_PIN
#endif
#ifndef DIN25
#define DIN25 UNDEF_PIN
#ifdef DIO155
#undef DIO155
#endif
#define DIO155 UNDEF_PIN
#endif
#ifndef DIN26
#define DIN26 UNDEF_PIN
#ifdef DIO156
#undef DIO156
#endif
#define DIO156 UNDEF_PIN
#endif
#ifndef DIN27
#define DIN27 UNDEF_PIN
#ifdef DIO157
#undef DIO157
#endif
#define DIO157 UNDEF_PIN
#endif
#ifndef DIN28
#define DIN28 UNDEF_PIN
#ifdef DIO158
#undef DIO158
#endif
#define DIO158 UNDEF_PIN
#endif
#ifndef DIN29
#define DIN29 UNDEF_PIN
#ifdef DIO159
#undef DIO159
#endif
#define DIO159 UNDEF_PIN
#endif
#ifndef DIN30
#define DIN30 UNDEF_PIN
#ifdef DIO160
#undef DIO160
#endif
#define DIO160 UNDEF_PIN
#endif
#ifndef DIN31
#define DIN31 UNDEF_PIN
#ifdef DIO161
#undef DIO161
#endif
#define DIO161 UNDEF_PIN
#endif
#ifndef TX
#define TX UNDEF_PIN
#ifdef DIO200
#undef DIO200
#endif
#define DIO200 UNDEF_PIN
#endif
#ifndef RX
#define RX UNDEF_PIN
#ifdef DIO201
#undef DIO201
#endif
#define DIO201 UNDEF_PIN
#endif
#ifndef USB_DM
#define USB_DM UNDEF_PIN
#ifdef DIO202
#undef DIO202
#endif
#define DIO202 UNDEF_PIN
#endif
#ifndef USB_DP
#define USB_DP UNDEF_PIN
#ifdef DIO203
#undef DIO203
#endif
#define DIO203 UNDEF_PIN
#endif
#ifndef SPI_CLK
#define SPI_CLK UNDEF_PIN
#ifdef DIO204
#undef DIO204
#endif
#define DIO204 UNDEF_PIN
#endif
#ifndef SPI_SDI
#define SPI_SDI UNDEF_PIN
#ifdef DIO205
#undef DIO205
#endif
#define DIO205 UNDEF_PIN
#endif
#ifndef SPI_SDO
#define SPI_SDO UNDEF_PIN
#ifdef DIO206
#undef DIO206
#endif
#define DIO206 UNDEF_PIN
#endif
#ifndef SPI_CS
#define SPI_CS UNDEF_PIN
#ifdef DIO207
#undef DIO207
#endif
#define DIO207 UNDEF_PIN
#endif
#ifndef I2C_CLK
#define I2C_CLK UNDEF_PIN
#ifdef DIO208
#undef DIO208
#endif
#define DIO208 UNDEF_PIN
#endif
#ifndef I2C_DATA
#define I2C_DATA UNDEF_PIN
#ifdef DIO209
#undef DIO209
#endif
#define DIO209 UNDEF_PIN
#endif
#ifndef TX2
#define TX2 UNDEF_PIN
#ifdef DIO210
#undef DIO210
#endif
#define DIO210 UNDEF_PIN
#endif
#ifndef RX2
#define RX2 UNDEF_PIN
#ifdef DIO211
#undef DIO211
#endif
#define DIO211 UNDEF_PIN
#endif

	// if the pins are undefined turn on option
#if (!ASSERT_PIN(ESTOP) && !ASSERT_PIN(SAFETY_DOOR) && !ASSERT_PIN(FHOLD) && !ASSERT_PIN(CS_RES) && !defined(DISABLE_ALL_CONTROLS))
#define DISABLE_ALL_CONTROLS
#endif

#if (!ASSERT_PIN(ESTOP))
#define ESTOP_INV_MASK 0
#else
#define ESTOP_INV_MASK 1
#endif
#if (!ASSERT_PIN(SAFETY_DOOR))
#define SAFETY_DOOR_INV_MASK 0
#else
#define SAFETY_DOOR_INV_MASK 2
#endif
#if (!ASSERT_PIN(FHOLD))
#define FHOLD_INV_MASK 0
#else
#define FHOLD_INV_MASK 4
#endif
#if (!ASSERT_PIN(CS_RES))
#define CS_RES_INV_MASK 0
#else
#define CS_RES_INV_MASK 8
#endif

#define CONTROLS_INV_MASK (ESTOP_INV_MASK | SAFETY_DOOR_INV_MASK | FHOLD_INV_MASK | CS_RES_INV_MASK)

#if (!ASSERT_PIN(LIMIT_X) && !ASSERT_PIN(LIMIT_X2) && !ASSERT_PIN(LIMIT_Y) && !ASSERT_PIN(LIMIT_Y2) && !ASSERT_PIN(LIMIT_Z) && !ASSERT_PIN(LIMIT_Z2) && !ASSERT_PIN(LIMIT_A) && !ASSERT_PIN(LIMIT_B) && !ASSERT_PIN(LIMIT_C) && !defined(DISABLE_ALL_LIMITS))
#define DISABLE_ALL_LIMITS
#endif

#if (!ASSERT_PIN(LIMIT_X))
#define LIMIT_X_INV_MASK 0
#else
#define LIMIT_X_INV_MASK 1
#endif
#if (!ASSERT_PIN(LIMIT_Y))
#define LIMIT_Y_INV_MASK 0
#else
#define LIMIT_Y_INV_MASK 2
#endif
#if (!ASSERT_PIN(LIMIT_Z))
#define LIMIT_Z_INV_MASK 0
#else
#define LIMIT_Z_INV_MASK 4
#endif
#if (!ASSERT_PIN(LIMIT_A))
#define LIMIT_A_INV_MASK 0
#else
#define LIMIT_A_INV_MASK 8
#endif
#if (!ASSERT_PIN(LIMIT_B))
#define LIMIT_B_INV_MASK 0
#else
#define LIMIT_B_INV_MASK 16
#endif
#if (!ASSERT_PIN(LIMIT_C))
#define LIMIT_C_INV_MASK 0
#else
#define LIMIT_C_INV_MASK 32
#endif

#if (!ASSERT_PIN(LIMIT_X2))
#define LIMIT_X2_INV_MASK 0
#else
#define LIMIT_X2_INV_MASK 1
#endif
#if (!ASSERT_PIN(LIMIT_Y2))
#define LIMIT_Y2_INV_MASK 0
#else
#define LIMIT_Y2_INV_MASK 2
#endif
#if (!ASSERT_PIN(LIMIT_Z2))
#define LIMIT_Z2_INV_MASK 0
#else
#define LIMIT_Z2_INV_MASK 4
#endif

#define LIMITS_INV_MASK (LIMIT_X_INV_MASK | LIMIT_Y_INV_MASK | LIMIT_Z_INV_MASK | LIMIT_A_INV_MASK | LIMIT_B_INV_MASK | LIMIT_B_INV_MASK)
#define LIMITS_DUAL_INV_MASK (LIMIT_X2_INV_MASK | LIMIT_Y2_INV_MASK | LIMIT_Z2_INV_MASK)

#if (ASSERT_PIN(DIN0) && defined(DIN0_ISR))
#define DIN0_MASK 1
#else
#define DIN0_MASK 0
#endif
#if (ASSERT_PIN(DIN1) && defined(DIN1_ISR))
#define DIN1_MASK 2
#else
#define DIN1_MASK 0
#endif
#if (ASSERT_PIN(DIN2) && defined(DIN2_ISR))
#define DIN2_MASK 4
#else
#define DIN2_MASK 0
#endif
#if (ASSERT_PIN(DIN3) && defined(DIN3_ISR))
#define DIN3_MASK 8
#else
#define DIN3_MASK 0
#endif
#if (ASSERT_PIN(DIN4) && defined(DIN4_ISR))
#define DIN4_MASK 16
#else
#define DIN4_MASK 0
#endif
#if (ASSERT_PIN(DIN5) && defined(DIN5_ISR))
#define DIN5_MASK 32
#else
#define DIN5_MASK 0
#endif
#if (ASSERT_PIN(DIN6) && defined(DIN6_ISR))
#define DIN6_MASK 64
#else
#define DIN6_MASK 0
#endif
#if (ASSERT_PIN(DIN7) && defined(DIN7_ISR))
#define DIN7_MASK 128
#else
#define DIN7_MASK 0
#endif

#define DIN_ONCHANGE_MASK (DIN0_MASK | DIN1_MASK | DIN2_MASK | DIN3_MASK | DIN4_MASK | DIN5_MASK | DIN6_MASK | DIN7_MASK)

#if (!ASSERT_PIN(PROBE) && !defined(DISABLE_PROBE))
#define DISABLE_PROBE
#endif

#if ASSERT_PIN(SERVO0)
#define SERVO0_MASK (1U << 0)
#define SERVO0_FRAME 0
#else
#define SERVO0_MASK 0
#endif
#if ASSERT_PIN(SERVO1)
#define SERVO1_MASK (1U << 1)
#define SERVO1_FRAME 3
#else
#define SERVO1_MASK 0
#endif
#if ASSERT_PIN(SERVO2)
#define SERVO2_MASK (1U << 2)
#define SERVO2_FRAME 6
#else
#define SERVO2_MASK 0
#endif
#if ASSERT_PIN(SERVO3)
#define SERVO3_MASK (1U << 3)
#define SERVO3_FRAME 9
#else
#define SERVO3_MASK 0
#endif
#if ASSERT_PIN(SERVO4)
#define SERVO4_MASK (1U << 4)
#define SERVO4_FRAME 12
#else
#define SERVO4_MASK 0
#endif
#if ASSERT_PIN(SERVO5)
#define SERVO5_MASK (1U << 5)
#define SERVO5_FRAME 15
#else
#define SERVO5_MASK 0
#endif

#define SERVOS_MASK (SERVO0_MASK | SERVO1_MASK | SERVO2_MASK | SERVO3_MASK | SERVO4_MASK | SERVO5_MASK)

#ifdef BRESENHAM_16BIT
#if (DSS_MAX_OVERSAMPLING < 0 || DSS_MAX_OVERSAMPLING > 3)
#error DSS_MAX_OVERSAMPLING invalid value! Should be set between 0 and 3
#endif
#else
#if (DSS_MAX_OVERSAMPLING < 0 || DSS_MAX_OVERSAMPLING > 5)
#error DSS_MAX_OVERSAMPLING invalid value! Should be set between 0 and 5
#endif
#endif

#ifndef CTRL_SCHED_CHECK
#define CTRL_SCHED_CHECK -1
#else
#if CTRL_SCHED_CHECK > 7
#error CTRL_SCHED_CHECK invalid value! Max is 7
#endif
#define CTRL_SCHED_CHECK_MASK ((1 << (CTRL_SCHED_CHECK + 1)) - 1)
#define CTRL_SCHED_CHECK_VAL (1 << (CTRL_SCHED_CHECK))
#endif

#ifndef BRESENHAM_16BIT
	typedef uint32_t step_t;
#define MAX_STEPS_PER_LINE_BITS (32 - (2 + DSS_MAX_OVERSAMPLING))
#else
typedef uint16_t step_t;
#define MAX_STEPS_PER_LINE_BITS (16 - (2 + DSS_MAX_OVERSAMPLING))
#endif
#define MAX_STEPS_PER_LINE (1UL << MAX_STEPS_PER_LINE_BITS)

#if DSS_CUTOFF_FREQ > (F_STEP_MAX >> 3)
#error "DSS_CUTOFF_FREQ should not be set above 1/8th of the max step rate"
#endif

#ifdef ENABLE_S_CURVE_ACCELERATION
#ifdef USE_LEGACY_STEP_INTERPOLATOR
#undef USE_LEGACY_STEP_INTERPOLATOR
#endif
#endif

#if (defined(KINEMATICS_MOTION_BY_SEGMENTS))
#ifdef ENABLE_DUAL_DRIVE_AXIS
#error "Delta does not support dual drive axis"
#endif
#if ((!ASSERT_PIN(LIMIT_X)) && (!ASSERT_PIN(LIMIT_X2)))
#error "Delta requires at least one X axis endstop"
#endif
#if ((!ASSERT_PIN(LIMIT_Y)) && (!ASSERT_PIN(LIMIT_Y2)))
#error "Delta requires at least one Y axis endstop"
#endif
#if ((!ASSERT_PIN(LIMIT_Z)) && (!ASSERT_PIN(LIMIT_Z2)))
#error "Delta requires at least one Z axis endstop"
#endif
#endif

#ifdef DISABLE_COORD_SYS_SUPPORT
#undef COORD_SYS_COUNT
#define COORD_SYS_COUNT 1
#endif

// some sanity checks
#if (COORD_SYS_COUNT < 1 || COORD_SYS_COUNT > 9)
#error "Invalid config option COORD_SYS_COUNT must be set between 1 and 9"
#endif

#if (N_ARC_CORRECTION < 1 || N_ARC_CORRECTION > 100)
#error "Invalid config option N_ARC_CORRECTION must be set between 1 and 100"
#endif

#if (TOOL_COUNT < 0 || TOOL_COUNT > 16)
#error "Invalid config option TOOL_COUNT must be set between 0 and 16"
#endif

#ifdef TOOL_WAIT_FOR_SPEED_MAX_ERROR
#if (TOOL_WAIT_FOR_SPEED_MAX_ERROR < 0 || TOOL_WAIT_FOR_SPEED_MAX_ERROR > 100)
#error "Invalid config option TOOL_WAIT_FOR_SPEED_MAX_ERROR must be set between 0 and 100"
#endif
#endif

#if (DELAY_ON_RESUME_SPINDLE < 0 || DELAY_ON_RESUME_SPINDLE > 60)
#error "Invalid config option DELAY_ON_RESUME_SPINDLE must be set between 0 and 60"
#endif

#if (DELAY_ON_SPINDLE_SPEED_CHANGE < 0 || DELAY_ON_SPINDLE_SPEED_CHANGE > 60)
#error "Invalid config option DELAY_ON_SPINDLE_SPEED_CHANGE must be set between 0 and 60"
#endif

#if (DELAY_ON_RESUME_COOLANT < 0 || DELAY_ON_RESUME_COOLANT > 60)
#error "Invalid config option DELAY_ON_RESUME_COOLANT must be set between 0 and 60"
#endif

#if (FEED_OVR_MAX < 100 || FEED_OVR_MAX > 250)
#error "Invalid config option FEED_OVR_MAX must be set between 100 and 250"
#endif

#if (FEED_OVR_MIN < 1 || FEED_OVR_MIN > 20)
#error "Invalid config option FEED_OVR_MIN must be set between 1 and 20"
#endif

#if (FEED_OVR_COARSE < 5 || FEED_OVR_COARSE > FEED_OVR_MIN)
#error "Invalid config option FEED_OVR_COARSE must be set between 5 and FEED_OVR_MIN"
#endif

#if (FEED_OVR_FINE < 1 || FEED_OVR_FINE > FEED_OVR_COARSE)
#error "Invalid config option FEED_OVR_FINE must be set between 1 and FEED_OVR_COARSE"
#endif

#if (RAPID_FEED_OVR1 < 25 || RAPID_FEED_OVR1 > 90)
#error "Invalid config option RAPID_FEED_OVR1 must be set between 25 and 90"
#endif

#if (RAPID_FEED_OVR2 < 10 || RAPID_FEED_OVR2 > RAPID_FEED_OVR1)
#error "Invalid config option RAPID_FEED_OVR2 must be set between 10 and RAPID_FEED_OVR1"
#endif

#if (SPINDLE_OVR_MAX < 100 || SPINDLE_OVR_MAX > 250)
#error "Invalid config option SPINDLE_OVR_MAX must be set between 100 and 250"
#endif

#if (SPINDLE_OVR_MIN < 1 || SPINDLE_OVR_MIN > 20)
#error "Invalid config option SPINDLE_OVR_MIN must be set between 1 and 20"
#endif

#if (SPINDLE_OVR_COARSE < 5 || SPINDLE_OVR_COARSE > SPINDLE_OVR_MIN)
#error "Invalid config option SPINDLE_OVR_COARSE must be set between 5 and SPINDLE_OVR_MIN"
#endif

#if (SPINDLE_OVR_FINE < 1 || SPINDLE_OVR_FINE > SPINDLE_OVR_COARSE)
#error "Invalid config option SPINDLE_OVR_FINE must be set between 1 and SPINDLE_OVR_COARSE"
#endif

#if (STATUS_WCO_REPORT_MIN_FREQUENCY < 10 || STATUS_WCO_REPORT_MIN_FREQUENCY > 100)
#error "Invalid config option STATUS_WCO_REPORT_MIN_FREQUENCY must be set between 10 and 100"
#endif

#if (STATUS_AUTOMATIC_REPORT_INTERVAL < 0 || STATUS_AUTOMATIC_REPORT_INTERVAL > 1000)
#error "Invalid config option STATUS_AUTOMATIC_REPORT_INTERVAL must be set between 0 and 1000"
#endif

#ifdef MCU_HAS_I2C

// defaults to master I2C
#ifndef I2C_ADDRESS
#define I2C_ADDRESS 0
#endif

#if !defined(MCU_SUPPORTS_I2C_SLAVE) && (I2C_ADDRESS != 0)
#error "I2C can't be configured in slave mode"
#endif
#endif

#ifdef DISABLE_PROBING_SUPPORT
#ifdef ENABLE_G39_H_MAPPING
#undef ENABLE_G39_H_MAPPING
#warning "ENABLE_G39_H_MAPPING disabled via DISABLE_PROBING_SUPPORT"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
