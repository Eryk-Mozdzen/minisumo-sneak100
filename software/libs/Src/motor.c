/*
 * motor.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#include "motor.h"

static void __Motor_SetPower(Motor_t *, int32_t);

void swap(uint16_t *a, uint16_t *b) {
	uint16_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void Motor_Init(Motor_t *motor, Encoder_t *encoder,
		TIM_HandleTypeDef *timer, uint32_t ch1, uint32_t ch2, MotorDirection_t dir,
		float kp, float ki, float kd, float iband) {

	motor->timer = timer;
	motor->encoder = encoder;

	motor->channel_in1 = ch1;
	motor->channel_in2 = ch2;
	motor->position_set_value = 0;
	motor->velocity_set_value = 0;
	motor->power_set_value = 0;
	motor->output = 0;

	PID_Init(&motor->pid, kp, ki, kd, iband);

	HAL_TIM_PWM_Start(motor->timer, motor->channel_in1);
	HAL_TIM_PWM_Start(motor->timer, motor->channel_in2);

	Motor_SetControlMode(motor, MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);
	Motor_SetBreakMode(motor, MOTOR_BRAKE_MODE_COAST);
	//Motor_SetBreakMode(motor, MOTOR_BRAKE_MODE_BREAK);
}

void Motor_Update(Motor_t *motor) {

	switch(motor->control_mode) {
		case MOTOR_CONTROL_MODE_CLOSE_LOOP_POSITION: {
			float curr_pos = Encoder_GetPosition(motor->encoder);

			// between [-1; 1]
			motor->output = PID_Update(&motor->pid, curr_pos, motor->position_set_value);
		} break;
		case MOTOR_CONTROL_MODE_CLOSE_LOOP_VELOCITY: {
			float curr_vel = Encoder_GetVelocity(motor->encoder);

			// between [-1; 1]
			motor->output = PID_Update(&motor->pid, curr_vel, motor->velocity_set_value);
		} break;
		case MOTOR_CONTROL_MODE_OPEN_LOOP_POWER: {
			// between [-1; 1]
			motor->output = motor->power_set_value;
		} break;
	}

	motor->output = MIN(MAX(-1.f, motor->output), 1.f);

	__Motor_SetPower(motor, motor->output*MOTOR_POWER_MAX);
}

void Motor_SetControlMode(Motor_t *motor, MotorControlMode_t mode) {
	motor->control_mode = mode;

	motor->position_set_value = Encoder_GetPosition(motor->encoder);
	motor->velocity_set_value = 0;
	motor->power_set_value = 0;
}

void Motor_SetBreakMode(Motor_t *motor, MotorBrakeMode_t mode) {
	motor->break_mode = mode;
}

void Motor_SetPosition(Motor_t *motor, float pos) {
	Motor_SetControlMode(motor, MOTOR_CONTROL_MODE_CLOSE_LOOP_POSITION);

	motor->position_set_value = pos;
}

void Motor_SetVelocity(Motor_t *motor, float vel) {
	Motor_SetControlMode(motor, MOTOR_CONTROL_MODE_CLOSE_LOOP_VELOCITY);

	motor->velocity_set_value = vel;
}

void Motor_SetPower(Motor_t *motor, float vel) {
	Motor_SetControlMode(motor, MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);

	motor->power_set_value = vel;
}

void __Motor_SetPower(Motor_t *motor, int32_t power) {
	power = MIN(MAX(-MOTOR_POWER_MAX, power), MOTOR_POWER_MAX);

	uint16_t power_in1 = 0;
	uint16_t power_in2 = 0;

	switch(motor->break_mode) {
		case MOTOR_BRAKE_MODE_COAST: {
			power_in1 = abs(MAX(power, 0));
			power_in2 = abs(MIN(power, 0));
		} break;
		case MOTOR_BRAKE_MODE_BREAK: {
			power_in1 = MOTOR_POWER_MAX - abs(MIN(power, 0));
			power_in2 = MOTOR_POWER_MAX - abs(MAX(power, 0));
		} break;
	}

	if(motor->direction==MOTOR_DIRECTION_CC)
		swap(&power_in1, &power_in2);

	__HAL_TIM_SET_COMPARE(motor->timer, motor->channel_in1, power_in1);
	__HAL_TIM_SET_COMPARE(motor->timer, motor->channel_in2, power_in2);
}

