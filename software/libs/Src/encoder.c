/*
 * encoder.c
 *
 *  Created on: Aug 21, 2021
 *      Author: ermoz
 */

#include "encoder.h"

void Encoder_Init(Encoder_t *encoder, TIM_HandleTypeDef *encoder_timer, uint16_t cpr) {
	encoder->timer = encoder_timer;
	encoder->cpr = cpr;

	Encoder_Reset(encoder);
	TimeBase_Init(&encoder->tbase);

	HAL_TIM_Encoder_Start(encoder->timer, TIM_CHANNEL_ALL);
}

void Encoder_Reset(Encoder_t *encoder) {
	encoder->prev_position = 0;

	__HAL_TIM_SET_COUNTER(encoder->timer, 0);
}

uint16_t Encoder_GetPositionRaw(Encoder_t *encoder) {
	return __HAL_TIM_GET_COUNTER(encoder->timer);
}

float Encoder_GetPosition(Encoder_t *encoder) {
	return ((float)((int16_t)__HAL_TIM_GET_COUNTER(encoder->timer)))/encoder->cpr;
}

float Encoder_GetVelocity(Encoder_t *encoder) {
	float delta_time = TimeBase_GetScale(&encoder->tbase) * TimeBase_Restart(&encoder->tbase);
	float curr_position = Encoder_GetPosition(encoder);

	float rps = (curr_position - encoder->prev_position)/delta_time;

	encoder->prev_position = curr_position;

	return rps;
}
