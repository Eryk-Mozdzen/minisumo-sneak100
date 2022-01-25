/*
 * line.h
 *
 *  Created on: Sep 10, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTS_INC_LINE_H_
#define SNEAK100_ABSTRACTS_INC_LINE_H_

#include "stdint.h"

typedef enum {
	DYHLO_WHITE_WITH_BLACK_CIRCUMFERENCE,
	DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE,
	DYHLO_AUTO
} Line_Polarity_EnumTypeDef;

typedef struct {
	uint16_t *read_src;
	uint16_t threshold;
	Line_Polarity_EnumTypeDef polarity;
} LineSensor_StructTypeDef;

void Line_Init(LineSensor_StructTypeDef *, uint16_t *, uint16_t);

uint8_t Line_GetState(LineSensor_StructTypeDef *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_LINE_H_ */
