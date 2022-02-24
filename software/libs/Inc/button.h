/*
 * button.h
 *
 *  Created on: Feb 24, 2022
 *      Author: emozdzen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;

	uint8_t prev_state : 1;
	uint8_t curr_state : 1;
} Button_t;

void Button_Init(Button_t *, GPIO_TypeDef *, uint16_t);
void Button_Update(Button_t *);

uint8_t Button_IsPressed(Button_t *);
uint8_t Button_IsChanged(Button_t *);
uint8_t Button_IsClicked(Button_t *);

#endif
