/*
 * line.c
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#include "line.h"

void Line_Init(LineSensor_StructTypeDef *line, uint16_t *read_src, uint16_t threshold) {
	line->read_src = read_src;
	line->threshold = threshold;
	line->polarity = DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE;
}

uint8_t Line_GetState(LineSensor_StructTypeDef *line) {
	return (*line->read_src<line->threshold)^line->polarity;
}
