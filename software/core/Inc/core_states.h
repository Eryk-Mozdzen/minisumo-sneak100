/*
 * core_states.h
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_STATES_H_
#define INC_CORE_STATES_H_

#include "main.h"

#include "core_def.h"
#include "core_conf.h"

void Core_Idle_Enter(void *);
void Core_Ready_Enter(void *);
void Core_Program_Enter(void *);
void Core_Run_Enter(void *);
void Core_Stop_Enter(void *);

void Core_Idle_Execute(void *);
void Core_Ready_Execute(void *);
void Core_Program_Execute(void *);
void Core_Run_Execute(void *);
void Core_Stop_Execute(void *);

void Core_Idle_Exit(void *);
void Core_Ready_Exit(void *);
void Core_Program_Exit(void *);
void Core_Run_Exit(void *);
void Core_Stop_Exit(void *);

#endif
