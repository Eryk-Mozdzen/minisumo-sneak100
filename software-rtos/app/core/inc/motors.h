#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "arm_math.h"

#define MOTORS_PID_KP			0.1f
#define MOTORS_PID_KI			0.01f
#define MOTORS_PID_KD			0.f
#define MOTORS_PID_FREQ			50		// Hz
#define MOTORS_ENCODER_CPR		360

#define MOTORS_PWR_COMP_EPS		0.01f
#define MOTORS_PWR_COMP_VAL		0.55f

#define MOTORS_WHEEL_READIUS	0.0145f	// m
#define MOTORS_TRACK_WIDTH		0.085f	// m
#define MOTORS_WHEELBASE		0.05f	// m

typedef enum {
	MOTORS_OPEN_LOOP,
	MOTORS_CLOSE_LOOP
} motors_control_type_t;

void motors_init();

void motors_set_control_type(motors_control_type_t);
void motors_set_power(float *);
void motors_set_velocity(float *);
void motors_get_position(int32_t *);
void motors_get_velocity(float *);
void motors_get_power(float *);

int32_t motors_get_position_delta(int32_t, int32_t);

#endif