/*
 * motor.h
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_MOTOR_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "pid.h"
#include "encoder.h"

#include <stdlib.h>
#include <stdint.h>

#define MOTOR_POWER_MAX		9999

#define MIN(__A__, __B__) (((__A__)<=(__B__)) ? (__A__) : (__B__))
#define MAX(__A__, __B__) (((__A__)>=(__B__)) ? (__A__) : (__B__))

typedef enum {
	MOTOR_CONTROL_MODE_OPEN_LOOP_POWER,
	MOTOR_CONTROL_MODE_CLOSE_LOOP_VELOCITY
} MotorControlMode_t;

typedef enum {
	MOTOR_BRAKE_MODE_BREAK,
	MOTOR_BRAKE_MODE_COAST
} MotorBrakeMode_t;

typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel_in1;
	uint32_t channel_in2;

	MotorBrakeMode_t break_mode;
	MotorControlMode_t control_mode;

	float curr_vel;

	float velocity_set_value;
	float power_set_value;

	float output;
	Encoder_t *encoder;
	PID_StructTypeDef pid;
} Motor_t;

void Motor_Init(Motor_t*, Encoder_t *, TIM_HandleTypeDef *, uint32_t, uint32_t, float, float, float);
void Motor_Update(Motor_t *);
void Motor_SetControlMode(Motor_t*, MotorControlMode_t);
void Motor_SetBreakMode(Motor_t *, MotorBrakeMode_t);

void Motor_SetVelocity(Motor_t *, float);
void Motor_SetPower(Motor_t *, float);

#endif
