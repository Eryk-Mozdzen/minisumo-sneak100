/*
 * sneak100.h
 *
 *  Created on: Aug 20, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_

#include "tim.h"
#include "motor.h"

#define MOTOR_GEAR_RATIO	30
#define ENCODER_CPR			12

#define MOTOR_PID_P			100.f
#define MOTOR_PID_I			0.1f
#define MOTOR_PID_D			10.f
#define MOTOR_PID_IBAND		0.5f

typedef enum {
	MOTOR_LF,
	MOTOR_LB,
	MOTOR_RF,
	MOTOR_RB
} Motor_EnumTypeDef;

extern Motor_StructTypeDef motors[4];
extern Encoder_StructTypeDef encoders[4];

void SNEAK100_Motors_Init();
void SNEAK100_Motors_SetBrakeMode(MotorBrakeMode_EnumTypeDef);
void SNEAK100_Motors_SetControlMode(MotorControlMode_EnumTypeDef);

void SNEAK100_Motors_Update();
void SNEAK100_Motors_SetSpeeds_1(float);
void SNEAK100_Motors_SetSpeeds_2(float, float);
void SNEAK100_Motors_SetSpeeds_4(float, float, float, float);

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_MOTORS_H_ */
