/*
 * sneak100_proximity.c
 *
 *  Created on: Aug 22, 2021
 *      Author: ermoz
 */

#include "sneak100_proximity.h"

ProximitySensor_StructTypeDef proximity[4];

void SNEAK100_Proximity_Init() {

	proximity[PROXIMITY_LL].GPIOx = PROXIMITY_LL_GPIO_Port;
	proximity[PROXIMITY_LL].GPIO_Pin = PROXIMITY_LL_Pin;

	proximity[PROXIMITY_FL].GPIOx = PROXIMITY_FL_GPIO_Port;
	proximity[PROXIMITY_FL].GPIO_Pin = PROXIMITY_FL_Pin;

	proximity[PROXIMITY_FR].GPIOx = PROXIMITY_FR_GPIO_Port;
	proximity[PROXIMITY_FR].GPIO_Pin = PROXIMITY_FR_Pin;

	proximity[PROXIMITY_RR].GPIOx = PROXIMITY_RR_GPIO_Port;
	proximity[PROXIMITY_RR].GPIO_Pin = PROXIMITY_RR_Pin;
}
