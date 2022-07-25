#ifndef MAIN_SM_H
#define MAIN_SM_H

#include <assert.h>

#include "finite_state_machine.h"
#include "FreeRTOS.h"
#include "task.h"

#include "rc5.h"
#include "periph.h"
#include "motors.h"
#include "uart2.h"

#define ROBOT_DATA_EEPROM_PAGE		0
#define ROBOT_DATA_EEPROM_OFFSET	0

#define ROBOT_LOOP_FREQ				50	// Hz

typedef enum {
	ROBOT_STATE_READY,
	ROBOT_STATE_PROGRAM,
	ROBOT_STATE_RUN,
	ROBOT_STATE_STOP
} robot_state_t;

void robot_init();

#endif