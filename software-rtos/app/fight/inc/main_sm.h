#ifndef MAIN_SM_H
#define MAIN_SM_H

#include "finite_state_machine.h"
#include "FreeRTOS.h"
#include "task.h"
#include "rc5.h"
#include "uart2.h"

typedef enum {
	ROBOT_STATE_READY,
	ROBOT_STATE_PROGRAM,
	ROBOT_STATE_RUN,
	ROBOT_STATE_STOP
} robot_state_t;

void main_sm_init();

#endif