#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "arm_math.h"

#define MOTORS_PID_KP		0.5f
#define MOTORS_PID_KI		0.1f
#define MOTORS_PID_KD		0.f
#define MOTORS_PID_FREQ		100		// Hz
#define MOTORS_ENCODER_CPR	512

void motors_init();

void motors_set_power(float *);
void motors_set_velocity(float *);
void motors_get_position(int32_t *);

#endif