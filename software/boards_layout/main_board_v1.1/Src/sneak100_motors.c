/*
 * sneak100_motors.c
 *
 *  Created on: Aug 20, 2021
 *      Author: ermoz
 */

#include "sneak100_motors.h"

Motor_StructTypeDef motors[4];
Encoder_StructTypeDef encoders[4];

void SNEAK100_Motors_Init() {

	Encoder_Init(&encoders[MOTOR_LF], &htim2, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&encoders[MOTOR_LB], &htim3, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&encoders[MOTOR_RF], &htim4, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&encoders[MOTOR_RB], &htim5, ENCODER_CPR*MOTOR_GEAR_RATIO);

	Motor_ConfigTypeDef config = {0};
	config.pid_p = MOTOR_PID_P;
	config.pid_i = MOTOR_PID_I;
	config.pid_d = MOTOR_PID_D;
	config.pid_iband = MOTOR_PID_IBAND;

	config.timer = &htim1;
	config.channel_in1 = TIM_CHANNEL_3;
	config.channel_in2 = TIM_CHANNEL_4;
	config.direction = DIRECTION_CW;
	Motor_Init(&motors[MOTOR_LF], &encoders[MOTOR_LF], config);

	config.timer = &htim1;
	config.channel_in1 = TIM_CHANNEL_1;
	config.channel_in2 = TIM_CHANNEL_2;
	config.direction = DIRECTION_CW;
	Motor_Init(&motors[MOTOR_LB], &encoders[MOTOR_LB], config);

	config.timer = &htim8;
	config.channel_in1 = TIM_CHANNEL_3;
	config.channel_in2 = TIM_CHANNEL_4;
	config.direction = DIRECTION_CC;
	Motor_Init(&motors[MOTOR_RF], &encoders[MOTOR_RF], config);

	config.timer = &htim8;
	config.channel_in1 = TIM_CHANNEL_1;
	config.channel_in2 = TIM_CHANNEL_2;
	config.direction = DIRECTION_CC;
	Motor_Init(&motors[MOTOR_RB], &encoders[MOTOR_RB], config);

	SNEAK100_Motors_SetBrakeMode(MODE_BREAK);
	SNEAK100_Motors_SetControlMode(MODE_VELOCITY_CONTROL);
}

void SNEAK100_Motors_SetBrakeMode(MotorBrakeMode_EnumTypeDef mode) {
	for(uint8_t i=0; i<4; i++)
		Motor_SetBreakMode(&motors[i], mode);
}

void SNEAK100_Motors_SetControlMode(MotorControlMode_EnumTypeDef mode) {
	for(uint8_t i=0; i<4; i++)
		Motor_SetControlMode(&motors[i], mode);
}

void SNEAK100_Motors_Update() {
	for(uint8_t i=0; i<4; i++)
		Motor_Update(&motors[i]);
}

void SNEAK100_Motors_SetSpeeds_1(float vel) {
	for(uint8_t i=0; i<4; i++)
		Motor_SetVelocity(&motors[i], vel);
}

void SNEAK100_Motors_SetSpeeds_2(float vel_l, float vel_r) {
	Motor_SetVelocity(&motors[MOTOR_LF], vel_l);
	Motor_SetVelocity(&motors[MOTOR_LB], vel_l);

	Motor_SetVelocity(&motors[MOTOR_RF], vel_r);
	Motor_SetVelocity(&motors[MOTOR_RB], vel_r);
}

void SNEAK100_Motors_SetSpeeds_4(float vel_lf, float vel_lb, float vel_rf, float vel_rb) {
	Motor_SetVelocity(&motors[MOTOR_LF], vel_lf);
	Motor_SetVelocity(&motors[MOTOR_LB], vel_lb);
	Motor_SetVelocity(&motors[MOTOR_RF], vel_rf);
	Motor_SetVelocity(&motors[MOTOR_RB], vel_rb);
}
