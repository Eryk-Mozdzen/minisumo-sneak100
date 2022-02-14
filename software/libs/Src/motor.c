/*
 * motor.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#include "motor.h"

void swap(uint16_t *a, uint16_t *b) {
	uint16_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void Motor_Init(Motor_StructTypeDef *motor, Encoder_StructTypeDef *encoder, Motor_ConfigTypeDef config) {

	motor->timer = config.timer;
	motor->encoder = encoder;

	motor->channel_in1 = config.channel_in1;
	motor->channel_in2 = config.channel_in2;
	motor->position_set_value = 0;
	motor->velocity_set_value = 0;

	PID_Init(&motor->pid, config.pid_p, config.pid_i, config.pid_d, config.pid_iband);

	HAL_TIM_PWM_Start(motor->timer, motor->channel_in1);
	HAL_TIM_PWM_Start(motor->timer, motor->channel_in2);

	Motor_SetControlMode(motor, MODE_POSITION_CONTROL);
	Motor_SetBreakMode(motor, MODE_COAST);
}

void Motor_Update(Motor_StructTypeDef *motor) {

	switch(motor->control_mode) {
		case MODE_POSITION_CONTROL: {
			float curr_pos = Encoder_GetPosition(motor->encoder);

			// between [-1; 1]
			float output = PID_Update(&motor->pid, curr_pos, motor->position_set_value);

			__Motor_SetPower(motor, output*MOTOR_POWER_MAX);
		} break;
		case MODE_VELOCITY_CONTROL: {
			float curr_vel = Encoder_GetVelocity(motor->encoder);

			// between [-1; 1]
			float output = PID_Update(&motor->pid, curr_vel, motor->velocity_set_value);

			__Motor_SetPower(motor, output*MOTOR_POWER_MAX);
		} break;
	}
}

void Motor_SetControlMode(Motor_StructTypeDef *motor, MotorControlMode_EnumTypeDef mode) {
	motor->control_mode = mode;

	motor->position_set_value = Encoder_GetPosition(motor->encoder);
	motor->velocity_set_value = 0;
}

void Motor_SetBreakMode(Motor_StructTypeDef *motor, MotorBrakeMode_EnumTypeDef mode) {
	motor->break_mode = mode;
}

void Motor_SetPosition(Motor_StructTypeDef *motor, float pos) {
	motor->position_set_value = pos;
}

void Motor_SetVelocity(Motor_StructTypeDef *motor, float vel) {
	motor->velocity_set_value = vel;
}

void __Motor_SetPower(Motor_StructTypeDef *motor, int32_t power) {
	power = MIN(MAX(-MOTOR_POWER_MAX, power), MOTOR_POWER_MAX);

	uint16_t power_in1 = 0;
	uint16_t power_in2 = 0;

	switch(motor->break_mode) {
		case MODE_COAST: {
			power_in1 = abs(MAX(power, 0));
			power_in2 = abs(MIN(power, 0));
		} break;
		case MODE_BREAK: {
			power_in1 = MOTOR_POWER_MAX - abs(MIN(power, 0));
			power_in2 = MOTOR_POWER_MAX - abs(MAX(power, 0));
		} break;
	}

	if(motor->direction==DIRECTION_CC)
		swap(&power_in1, &power_in2);

	__HAL_TIM_SET_COMPARE(motor->timer, motor->channel_in1, power_in1);
	__HAL_TIM_SET_COMPARE(motor->timer, motor->channel_in2, power_in2);
}

