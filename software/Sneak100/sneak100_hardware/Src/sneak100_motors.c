/*
 * sneak100_motors.c
 *
 *  Created on: Aug 20, 2021
 *      Author: ermoz
 */

#include "sneak100_motors.h"

Motor_StructTypeDef motorFL;
Motor_StructTypeDef motorFR;
Motor_StructTypeDef motorBL;
Motor_StructTypeDef motorBR;

void SNEAK100_Motors_Init() {

	Motor_Init(&motorFL, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	//Motor_Init(&motorFR, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	//Motor_Init(&motorBL, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	//Motor_Init(&motorBR, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);

}
