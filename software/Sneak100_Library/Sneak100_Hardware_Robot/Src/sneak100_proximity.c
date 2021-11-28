/*
 * sneak100_proximity.c
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#include "sneak100_proximity.h"

ProximitySensor_StructTypeDef proximityLL;
ProximitySensor_StructTypeDef proximityFL;
ProximitySensor_StructTypeDef proximityFR;
ProximitySensor_StructTypeDef proximityRR;

void SNEAK100_ProximitySensors_Init() {

	proximityLL.GPIOx = PROXIMITY_LL_GPIO_Port;
	proximityLL.GPIO_Pin = PROXIMITY_LL_Pin;

	proximityFL.GPIOx = PROXIMITY_FL_GPIO_Port;
	proximityFL.GPIO_Pin = PROXIMITY_FL_Pin;

	proximityFR.GPIOx = PROXIMITY_FR_GPIO_Port;
	proximityFR.GPIO_Pin = PROXIMITY_FR_Pin;

	proximityRR.GPIOx = PROXIMITY_RR_GPIO_Port;
	proximityRR.GPIO_Pin = PROXIMITY_RR_Pin;
}
