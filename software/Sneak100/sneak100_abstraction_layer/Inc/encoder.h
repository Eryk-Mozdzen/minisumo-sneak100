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

typedef struct {
	TIM_HandleTypeDef *timer;
	uint16_t cpr;

	float prev_position;

	TimeBase_StructTypeDef tbase;
} Encoder_StructTypeDef;

void Encoder_Init(Encoder_StructTypeDef *, TIM_HandleTypeDef *, TIM_HandleTypeDef *, uint16_t);
void Encoder_Reset(Encoder_StructTypeDef *);

float Encoder_GetPosition(Encoder_StructTypeDef *);
float Encoder_GetVelocity(Encoder_StructTypeDef *);

#endif /* SNEAK100_ABSTRACTION_LAYER_INC_ENCODER_H_ */
