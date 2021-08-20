/*
 * sneak100.h
 *
 *  Created on: Aug 20, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_

#include "motor.h"

#define MOTOR_PID_P		100.f
#define MOTOR_PID_I		1.f
#define MOTOR_PID_D		10.f

extern Motor_StructTypeDef motorFL;
extern Motor_StructTypeDef motorFR;
extern Motor_StructTypeDef motorBL;
extern Motor_StructTypeDef motorBR;

void SNEAK100_Motors_Init();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_ */
