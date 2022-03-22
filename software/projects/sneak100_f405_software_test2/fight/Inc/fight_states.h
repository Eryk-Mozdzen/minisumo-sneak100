/*
 * fight_states.h
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#ifndef INC_FIGHT_STATES_H_
#define INC_FIGHT_STATES_H_

#include "core_def.h"
#include "core_conf.h"

void Fight_Start_Enter(void *);
void Fight_Explore_Enter(void *);
void Fight_Turn_Enter(void *);

void Fight_Explore_Execute(void *);
void Fight_Turn_Execute(void *);



#endif
