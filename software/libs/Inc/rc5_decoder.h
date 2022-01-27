/*
 * rc5_decoder.h
 *
 *  Created on: Dec 30, 2021
 *      Author: ermoz
 */

#ifndef INC_RC5_DECODER_H_
#define INC_RC5_DECODER_H_

#include <stdlib.h>
#include <stdint.h>
#include "finite_state_machine.h"
#include "stm32f4xx_hal.h"

#define RC5_TIME_SHORT		889		// us
#define RC5_TIME_LONG		1778	// us
#define RC5_TIME_TOLERANCE	444		// us
#define RC5_TIME_PRESCALER	1		// us/LSB

typedef enum {
	RC5_STATE_START1,
	RC5_STATE_MID1,
	RC5_STATE_START0,
	RC5_STATE_MID0,
	RC5_STATE_RESET
} __RC5_State_t;

typedef union {
	struct {
		uint16_t command : 6;
		uint16_t address : 5;
		uint16_t toggle : 1;
		uint16_t start : 2;
	};
	uint16_t frame;
} RC5_Message_t;

typedef struct {
	uint8_t bits_ready;
	RC5_Message_t message;

	uint8_t state;
	uint32_t counter;

	uint16_t rx_pin;
	GPIO_TypeDef *rx_port;
	TIM_HandleTypeDef *timer;

	FiniteStateMachine_t fsm;
} DecoderRC5_t;

void DecoderRC5_Init(DecoderRC5_t *, TIM_HandleTypeDef *, GPIO_TypeDef *, uint16_t);
uint8_t DecoderRC5_GetMessage(DecoderRC5_t *, RC5_Message_t *);

void DecoderRC5_EXTI_Callback(DecoderRC5_t *, uint16_t);
void DecoderRC5_PeriodElapsedCallback(DecoderRC5_t *, TIM_HandleTypeDef *);

void __rc5_emit1(void *);
void __rc5_emit0(void *);
void __rc5_reset(void *);

uint8_t __rc5_get_short_space(void *);
uint8_t __rc5_get_short_pulse(void *);
uint8_t __rc5_get_long_space(void *);
uint8_t __rc5_get_long_pulse(void *);
uint8_t __rc5_pass(void *);

#endif
