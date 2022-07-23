#ifndef RC5_H
#define RC5_H

#include <stdlib.h>
#include "finite_state_machine.h"
#include "stm32f4xx.h"

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
} rc5_state_t;

typedef union {
	struct {
		uint16_t command : 6;
		uint16_t address : 5;
		uint16_t toggle : 1;
		uint16_t start : 2;
		uint16_t unused : 2;
	};
	uint16_t frame;
} rc5_message_t;

void rc5_init();
uint8_t rc5_get_message(rc5_message_t *);

void TIM7_IRQHandler();
void EXTI15_10_IRQHandler();

#endif
