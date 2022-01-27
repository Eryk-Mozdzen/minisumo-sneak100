/*
 * senak100_proximity.h
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_HARDWARE_INC_SNEAK100_PROXIMITY_H_
#define SNEAK100_HARDWARE_INC_SNEAK100_PROXIMITY_H_

#include "proximity.h"
#include "main.h"

typedef enum {
	PROXIMITY_LL,
	PROXIMITY_FL,
	PROXIMITY_FR,
	PROXIMITY_RR
} Proximity_EnumTypeDef;

extern ProximitySensor_StructTypeDef proximity[4];

void SNEAK100_Proximity_Init();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_PROXIMITY_H_ */
