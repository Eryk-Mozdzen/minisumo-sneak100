/*
 * motor.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#include "motor.h"

void Motor_Init(Motor_StructTypeDef *motor,
		TIM_HandleTypeDef *motor_timer,
		TIM_HandleTypeDef *encoder_timer,
		TIM_HandleTypeDef *time_base_timer,
		uint16_t encoder_cpr, float pid_p, float pid_i, float pid_d) {

	motor->motor_timer = motor_timer;
	motor->encoder_timer = encoder_timer;
	motor->encoder_cpr = encoder_cpr;
	motor->position_set_value = 0;
	motor->velocity_set_value = 0;

	TimeBase_Init(&motor->tbase, time_base_timer);
	PID_Init(&motor->pid, time_base_timer, pid_p, pid_i, pid_d);

	HAL_TIM_Encoder_Start(encoder_timer, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(encoder_timer, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(motor_timer, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(motor_timer, TIM_CHANNEL_4);

	Motor_SetMode(motor, MODE_POSITION_CONTROL);
}

void Motor_SetMode(Motor_StructTypeDef *motor, MotorControlMode_EnumTypeDef mode) {
	motor->mode = mode;

	motor->position_set_value = Motor_GetPosition(motor);
	motor->velocity_set_value = 0;
}

void Motor_SetPosition(Motor_StructTypeDef *motor, float pos) {
	assert(motor->mode==MODE_POSITION_CONTROL);

	float curr_pos = Motor_GetPosition(motor);

	float output = PID_Update(&motor->pid, curr_pos, pos);

	//motor->motor_timer
}

void Motor_SetVelocity(Motor_StructTypeDef *motor, float vel) {
	assert(motor->mode==MODE_VELOCITY_CONTROL);

	float curr_vel = Motor_GetVelocity(motor);

	float output = PID_Update(&motor->pid, curr_vel, vel);

	//motor->motor_timer
}

float Motor_GetPosition(Motor_StructTypeDef *motor) {
	return __HAL_TIM_GetCounter(motor->encoder_timer);
}
