/*
 * motor.h
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_MOTOR_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_MOTOR_H_

#include "tim.h"
#include "pid.h"
#include <stdint.h>
#include <assert.h>

typedef enum {
	MODE_POSITION_CONTROL,
	MODE_VELOCITY_CONTROL
} MotorControlMode_EnumTypeDef;

typedef struct {
	TIM_HandleTypeDef *motor_timer;

	float position_set_value, velocity_set_value;

	MotorControlMode_EnumTypeDef mode;
	TimeBase_StructTypeDef tbase;
	PID_StructTypeDef pid;
} Motor_StructTypeDef;

void Motor_Init(Motor_StructTypeDef *, TIM_HandleTypeDef *, TIM_HandleTypeDef *, TIM_HandleTypeDef *, uint16_t, float , float, float);
void Motor_Update(Motor_StructTypeDef *);
void Motor_SetMode(Motor_StructTypeDef *, MotorControlMode_EnumTypeDef);
void Motor_SetPosition(Motor_StructTypeDef *, float);
void Motor_SetVelocity(Motor_StructTypeDef *, float);

float Motor_GetPosition(Motor_StructTypeDef *);
float Motor_GetVelocity(Motor_StructTypeDef *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_MOTOR_H_ */
