/*
 * encoder.h
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_ABSTRACTION_LAYER_INC_ENCODER_H_
#define SNEAK100_ABSTRACTION_LAYER_INC_ENCODER_H_

#include "stm32f4xx_hal.h"
#include "time_base.h"
#include <stdint.h>
#include <math.h>

typedef struct {
	TIM_HandleTypeDef *timer;
	uint16_t cpr;

	float prev_position;

	TimeBase_StructTypeDef tbase;
} Encoder_t;

void Encoder_Init(Encoder_t *, TIM_HandleTypeDef *, uint16_t);
int16_t Encoder_Reset(Encoder_t *);

float Encoder_GetPosition(Encoder_t *);
float Encoder_GetVelocity(Encoder_t *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_ENCODER_H_ */
