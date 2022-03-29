/*
 * sneak100_core_conf.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_CONF_H_
#define INC_CORE_CONF_H_

#define MOTOR_GEAR_RATIO				30		// input/output
#define ENCODER_CPR						12		// counts per rotation
#define WHEEL_DIAMETER					0.0292f	// m
#define WHEEL_RADIUS					0.0146f	// m
#define WHEEL_SPACING					0.085f	// m
#define WHEEL_ROT_TO_CHASSIE_ROT_CONST	0.4f

#define MOTOR_PID_P						0.07f
#define MOTOR_PID_I						0.0275f
#define MOTOR_PID_D						0.00125f

#define LINE_THRESHOLD					2000
#define LINE_SPACING					0.0232f	// m

#define SUPPLY_VOLTAGE_DIVIDER_R1		18000	// ohm
#define SUPPLY_VOLTAGE_DIVIDER_R2		10000	// ohm
#define BATTERY_CRITICAL_VOLTAGE		6.5f	// volt

#define ADC_REF_VOLTAGE					3.27f	// volt
#define ADC_RESOLUTION					4095
#define ADC_GET_VOLTAGE(adc)			(((float)(adc)*ADC_REF_VOLTAGE)/ADC_RESOLUTION)

#define MEMORY_SETTINGS_ADDRESS			0x00
#define MEMORY_FIGHT_DATA_ADDRESS		0x10

#define BLUETOOTH_NAME					"Sneak100"
#define BLUETOOTH_PASSWORD				"7777"

#define MODULE_RC5_ADD_START_STOP		0x07
#define MODULE_RC5_ADD_PROGRAM			0x0B
#define MODULE_RC5_CMD_MASK_DYHLO		0x3E
#define MODULE_RC5_CMD_MASK_START_STOP	0x01
#define MODULE_RC5_LED_BLINK_PERIOD		400		// ms

#define BUTTON_START_WAIT_TIME			5000	// ms

#define CORE_UPDATE_PERIOD				50		// ms
#define CORE_BUILD_DATE					__DATE__
#define CORE_BUILD_TIME					__TIME__

#endif
