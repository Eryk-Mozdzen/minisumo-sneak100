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

int16_t Encoder_Reset(Encoder_t *encoder) {
	encoder->prev_position = encoder->prev_position - ((float)((int16_t)__HAL_TIM_GET_COUNTER(encoder->timer)))/encoder->cpr;
	int16_t raw = __HAL_TIM_GET_COUNTER(encoder->timer);

	__HAL_TIM_SET_COUNTER(encoder->timer, 0);

	return raw;
}

float Encoder_GetPosition(Encoder_t *encoder) {
	float pos = ((float)((int16_t)__HAL_TIM_GET_COUNTER(encoder->timer)))/encoder->cpr;

	if(fabs(pos)>80)
		Encoder_Reset(encoder);

	return pos;
}

float Encoder_GetVelocity(Encoder_t *encoder) {
	float delta_time = TimeBase_GetScale(&encoder->tbase) * TimeBase_Restart(&encoder->tbase);
	float curr_position = Encoder_GetPosition(encoder);

	float rps = (curr_position - encoder->prev_position)/delta_time;

	encoder->prev_position = curr_position;

	return rps;
}
