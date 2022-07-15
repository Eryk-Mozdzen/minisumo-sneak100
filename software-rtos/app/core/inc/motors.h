#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "arm_math.h"

#define MOTORS_PID_KP		0.01f
#define MOTORS_PID_KI		0.f
#define MOTORS_PID_KD		0.f
#define MOTORS_PID_FREQ		100		// Hz

void motors_init();

void motors_set_power(float *);
void motors_set_velocity(float *);
void motors_get_position(float *);

#endif