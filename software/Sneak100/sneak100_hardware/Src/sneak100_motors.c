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

Encoder_StructTypeDef encoderFL;
Encoder_StructTypeDef encoderFR;
Encoder_StructTypeDef encoderBL;
Encoder_StructTypeDef encoderBR;

void SNEAK100_Motors_Init() {

	Encoder_Init(&encoderFL, &htim3, 512);
	//Encoder_Init(&encoderFL, &htim3, 360);
	//Encoder_Init(&encoderFL, &htim3, 360);
	//Encoder_Init(&encoderFL, &htim3, 360);

	Motor_ConfigTypeDef config = {0};
	config.pid_p = MOTOR_PID_P;
	config.pid_i = MOTOR_PID_I;
	config.pid_d = MOTOR_PID_D;
	config.pid_iband = MOTOR_PID_IBAND;

	config.timer_in1 = &htim1;
	config.timer_in2 = &htim1;
	config.channel_in1 = TIM_CHANNEL_2;
	config.channel_in2 = TIM_CHANNEL_3 | TIM_CHANNEL_N ;
	config.direction = DIRECTION_CW;
	Motor_Init(&motorFL, &encoderFL, config);


	//Motor_Init(&motorFR, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	//Motor_Init(&motorBL, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	//Motor_Init(&motorBR, &htim3, &htim3, &htim2, 512, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);

}
