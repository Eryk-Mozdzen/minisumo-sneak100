/*
 * core_fsm.h
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_EVENTS_H_
#define INC_CORE_EVENTS_H_

#include <stdint.h>
#include "core_def.h"
#include "core_conf.h"

uint8_t __Core_Program_SelectEvent(void *);
uint8_t __Core_Program_SignalEvent(void *);
uint8_t __Core_Start_SignalEvent(void *);
uint8_t __Core_Stop_SignalEvent(void *);

#endif
