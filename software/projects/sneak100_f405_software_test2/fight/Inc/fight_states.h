/*
 * fight_states.h
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#ifndef INC_FIGHT_STATES_H_
#define INC_FIGHT_STATES_H_

#include <math.h>

#include "core_def.h"
#include "core_conf.h"

#define FIGHT_EXPLORE_SPEED			3.f
#define FIGHT_ANGLE_MEAS_SPEED		0.5f
#define FIGHT_LINE_BACK_SPEED		5.f
#define FIGHT_LINE_TURN_SPEED		5.f

void Fight_Start_Enter(void *);
void Fight_Explore_Enter(void *);
void Fight_AngleMeasurement_Enter(void *);
void Fight_LineManeuver_Enter(void *);

void Fight_Start_Execute(void *);
void Fight_Explore_Execute(void *);
void Fight_AngleMeasurement_Execute(void *);
void Fight_LineManeuver_Execute(void *);

void Fight_Start_Exit(void *);
void Fight_Explore_Exit(void *);
void Fight_AngleMeasurement_Exit(void *);
void Fight_LineManeuver_Exit(void *);

#endif
