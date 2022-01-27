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
#include "math_tools.h"
#include "encoder.h"

#include <stdlib.h>
#include <stdint.h>

#define MOTOR_POWER_MAX		65535

typedef enum {
	MODE_POSITION_CONTROL,
	MODE_VELOCITY_CONTROL
} MotorControlMode_EnumTypeDef;

typedef enum {
	DIRECTION_CW,
	DIRECTION_CC
} MotorDirection_EnumTypeDef;

typedef enum {
	MODE_BREAK,
	MODE_COAST
} MotorBrakeMode_EnumTypeDef;

typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel_in1;
	uint32_t channel_in2;

	MotorDirection_EnumTypeDef direction;

	float pid_p;
	float pid_i;
	float pid_d;
	float pid_iband;
} Motor_ConfigTypeDef;

typedef struct {
	TIM_HandleTypeDef *timer;
	uint32_t channel_in1;
	uint32_t channel_in2;

	MotorDirection_EnumTypeDef direction;
	MotorBrakeMode_EnumTypeDef break_mode;
	MotorControlMode_EnumTypeDef control_mode;

	float position_set_value;
	float velocity_set_value;

	Encoder_StructTypeDef *encoder;
	PID_StructTypeDef pid;
} Motor_StructTypeDef;

void Motor_Init(Motor_StructTypeDef *, Encoder_StructTypeDef *, Motor_ConfigTypeDef);
void Motor_Update(Motor_StructTypeDef *);
void Motor_SetControlMode(Motor_StructTypeDef *, MotorControlMode_EnumTypeDef);
void Motor_SetBreakMode(Motor_StructTypeDef *, MotorBrakeMode_EnumTypeDef);

void Motor_SetPosition(Motor_StructTypeDef *, float);
void Motor_SetVelocity(Motor_StructTypeDef *, float);

void __Motor_SetPower(Motor_StructTypeDef *, int32_t);

#endif
