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

#define MOTOR_POWER_MAX		65535

#define MIN(__A__, __B__) (((__A__)<=(__B__)) ? (__A__) : (__B__))
#define MAX(__A__, __B__) (((__A__)>=(__B__)) ? (__A__) : (__B__))

typedef enum {
	MODE_POSITION_CONTROL,
	MODE_VELOCITY_CONTROL
} MotorControlMode_t;

typedef enum {
	DIRECTION_CW,
	DIRECTION_CC
} MotorDirection_t;

typedef enum {
	MODE_BREAK,
	MODE_COAST
} MotorBrakeMode_t;

typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel_in1;
	uint32_t channel_in2;

	MotorDirection_t direction;
	MotorBrakeMode_t break_mode;
	MotorControlMode_t control_mode;

	float position_set_value;
	float velocity_set_value;

	Encoder_t *encoder;
	PID_StructTypeDef pid;
} Motor_t;

void Motor_Init(Motor_t*, Encoder_t *, TIM_HandleTypeDef *, uint32_t, uint32_t, MotorDirection_t, float, float, float, float);
void Motor_Update(Motor_t *);
void Motor_SetControlMode(Motor_t*, MotorControlMode_t);
void Motor_SetBreakMode(Motor_t *, MotorBrakeMode_t);

void Motor_SetPosition(Motor_t *, float);
void Motor_SetVelocity(Motor_t *, float);

void __Motor_SetPower(Motor_t *, int32_t);

#endif
