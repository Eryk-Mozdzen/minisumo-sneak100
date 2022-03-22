/*
 * sneak100_core.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_H_
#define INC_CORE_H_


#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "main.h"
#include "usart.h"

#include <string.h>

#include "core_def.h"
#include "core_conf.h"
#include "core_events.h"
#include "core_states.h"

#include "fight_events.h"
#include "fight_states.h"

extern Sneak100_Core_t core;

void SNEAK100_Core_Init();
void SNEAK100_Core_Update();
void SNEAK100_Core_UpdateRequest();

#endif
