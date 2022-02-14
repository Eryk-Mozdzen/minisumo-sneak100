/*
 * sneak100_core_conf.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_CONF_H_
#define INC_CORE_CONF_H_

#define MOTOR_GEAR_RATIO	30
#define ENCODER_CPR			12

#define MOTOR_PID_P			100.f
#define MOTOR_PID_I			0.1f
#define MOTOR_PID_D			10.f
#define MOTOR_PID_IBAND		0.5f

#define LINE_THRESHOLD				1500

#define SUPPLY_VOLTAGE_DIVIDER_R1	18000.f
#define SUPPLY_VOLTAGE_DIVIDER_R2	10000.f

#define SNEAK100_MEMORY_SETTINGS_ADDRESS	0x00

#endif /* INC_CORE_CONF_H_ */
