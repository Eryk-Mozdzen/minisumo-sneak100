#ifndef FIGHT_H
#define FIGHT_H

#include "finite_state_machine.h"
#include "periph.h"
#include "motors.h"

#ifdef FIGHT_DEBUG
	#include "uart2.h"
	#include "uart3.h"
#endif

#define FIGHT_PID_KP		0.011f
#define FIGHT_PWR			0.75f		// [-1; 1]
#define FOLLOW_TIMEOUT		2000		// ms
#define EXPLORE_VEL			5			// RPS
#define MEASURE_VEL			2			// RPS
#define TURN_VEL			2			// RPS

typedef enum {
	FIGHT_STATE_FOLLOW,
	FIGHT_STATE_FIGHT,
	FIGHT_STATE_EXPLORE,
	FIGHT_STATE_MEASURE,
	FIGHT_STATE_TURN
} fight_state_t;

void fight_init();
void fight_update();

fight_state_t fight_get_state();

#endif