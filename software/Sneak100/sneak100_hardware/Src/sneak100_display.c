/*
 * sneak100_display.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "sneak100_display.h"

Display_TypeDef oled;

void SNEAK100_Display_Init() {

	Display_Init(&oled, &hi2c1, 128, 64);

}
