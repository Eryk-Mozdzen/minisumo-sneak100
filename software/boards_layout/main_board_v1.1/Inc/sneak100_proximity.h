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

extern ProximitySensor_StructTypeDef proximityLL;
extern ProximitySensor_StructTypeDef proximityFL;
extern ProximitySensor_StructTypeDef proximityFR;
extern ProximitySensor_StructTypeDef proximityRR;

void SNEAK100_Proximity_Init();

#endif /* SNEAK100_HARDWARE_INC_SNEAK100_PROXIMITY_H_ */
