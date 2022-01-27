/*
 * rc5_decoder.c
 *
 *  Created on: Jan 2, 2022
 *      Author: emozdzen
 */

#include "rc5_decoder.h"

void DecoderRC5_Init(DecoderRC5_t *decoder, TIM_HandleTypeDef *htim, GPIO_TypeDef *port, uint16_t pin) {
	decoder->timer = htim;
	decoder->rx_port = port;
	decoder->rx_pin = pin;

	FiniteStateMachine_Init(&decoder->fsm, decoder);

	// state definition
	FiniteStateMachine_DefineState(&decoder->fsm, RC5_STATE_START1,	NULL,			NULL, NULL);
	FiniteStateMachine_DefineState(&decoder->fsm, RC5_STATE_MID1,	&__rc5_emit1, 	NULL, NULL);
	FiniteStateMachine_DefineState(&decoder->fsm, RC5_STATE_START0,	NULL,			NULL, NULL);
	FiniteStateMachine_DefineState(&decoder->fsm, RC5_STATE_MID0,	&__rc5_emit0, 	NULL, NULL);
	FiniteStateMachine_DefineState(&decoder->fsm, RC5_STATE_RESET,	&__rc5_reset, 	NULL, NULL);

	// transition definition from RC5 graph and reset transition
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_START1,	RC5_STATE_MID1,		0,	NULL, &__rc5_get_short_space);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_MID1,		RC5_STATE_START1,	0,	NULL, &__rc5_get_short_pulse);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_MID1,		RC5_STATE_MID0,		0,	NULL, &__rc5_get_long_pulse);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_MID0,		RC5_STATE_MID1,		0,	NULL, &__rc5_get_long_space);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_MID0,		RC5_STATE_START0,	0,	NULL, &__rc5_get_short_space);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_START0,	RC5_STATE_MID0,		0,	NULL, &__rc5_get_short_pulse);
	FiniteStateMachine_DefineTransition(&decoder->fsm, RC5_STATE_RESET,		RC5_STATE_MID1,		0,	NULL, NULL);

	FiniteStateMachine_Start(&decoder->fsm, RC5_STATE_RESET);

	HAL_TIM_Base_Start_IT(decoder->timer);
}

uint8_t DecoderRC5_GetMessage(DecoderRC5_t *decoder, RC5_Message_t *message) {
	if(decoder->bits_ready!=14)
		return 0;

	*message = decoder->message;

	FiniteStateMachine_Start(&decoder->fsm, RC5_STATE_RESET);

	return 1;
}

void DecoderRC5_PeriodElapsedCallback(DecoderRC5_t *decoder, TIM_HandleTypeDef *htim) {
	if(htim->Instance!=decoder->timer->Instance)
		return;

	if(decoder->bits_ready==14)
		return;

	FiniteStateMachine_Start(&decoder->fsm, RC5_STATE_RESET);
}

void DecoderRC5_EXTI_Callback(DecoderRC5_t *decoder, uint16_t GPIO_Pin) {
	if(GPIO_Pin!=decoder->rx_pin)
		return;

	if(decoder->bits_ready==14)
		return;

	decoder->state = !HAL_GPIO_ReadPin(decoder->rx_port, decoder->rx_pin);
	decoder->counter = __HAL_TIM_GET_COUNTER(decoder->timer);

	__HAL_TIM_SET_COUNTER(decoder->timer, 0);

	FiniteStateMachine_Update(&decoder->fsm);
}

