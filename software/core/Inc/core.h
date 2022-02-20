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

extern Sneak100_t sneak100;

void SNEAK100_Core_Init();
void SNEAK100_Core_Update();
void SNEAK100_Core_UpdateRequest();

void SNEAK100_Core_ReadState();
void SNEAK100_Core_ReadSettings();
void SNEAK100_Core_WriteSettings();

void SNEAK100_Core_ApplySettings();

float SNEAK100_Core_GetTemperature();
float SNEAK100_Core_GetSupplyVoltage();

#endif
