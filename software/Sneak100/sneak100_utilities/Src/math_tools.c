/*
 * math_tools.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "math_tools.h"

void swap(uint16_t *a, uint16_t *b) {
	uint16_t tmp = *a;
	*a = *b;
	*b = tmp;
}
