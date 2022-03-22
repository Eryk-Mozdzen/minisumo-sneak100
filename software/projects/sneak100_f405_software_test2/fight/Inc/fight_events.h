/*
 * fight_events.h
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#ifndef INC_FIGHT_EVENTS_H_
#define INC_FIGHT_EVENTS_H_

#include <stdint.h>
#include "core_def.h"
#include "core_conf.h"

uint8_t __Fight_Line_DetectEvent(void *);
uint8_t __Fight_TurnEnd_Event(void *);

#endif
