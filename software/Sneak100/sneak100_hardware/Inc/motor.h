/*
 * motor.h
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_MOTOR_H_
#define SNEAK100_HARDWARE_INC_MOTOR_H_

#include "tim.h"
#include "pid.h"
#include <stdint.h>

typedef struct {
	TIM_HandleTypeDef *motor_timer;
	TIM_HandleTypeDef *encoder_timer;
	TIM_HandleTypeDef *time_base_timer;

	PID_StructTypeDef pid;
} Motor_StructTypeDef;

extern Motor_StructTypeDef motorFL;
extern Motor_StructTypeDef motorFR;
extern Motor_StructTypeDef motorBL;
extern Motor_StructTypeDef motorBR;

void SNEAK100_Motors_Init();
uint16_t Motor_GetPosition(Motor_StructTypeDef *);

#endif /* SNEAK100_HARDWARE_INC_MOTOR_H_ */
