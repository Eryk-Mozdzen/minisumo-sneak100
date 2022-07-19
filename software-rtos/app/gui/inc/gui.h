#ifndef GUI_H
#define GUI_H

#include <math.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "finite_state_machine.h"

#include "display.h"
#include "sprites.h"
#include "motors.h"
#include "periph.h"

#define GUI_UPDATE_FREQ		20

typedef enum {
	GUI_STATE_MENU,

	GUI_STATE_MOTORS,
	GUI_STATE_LINE,
	GUI_STATE_PROX,
	GUI_STATE_OTHER,

	GUI_STATE_FIGHT,

	GUI_STATE_ROBOT,
	GUI_STATE_KONAR
} gui_state_t;

void gui_init();

#endif