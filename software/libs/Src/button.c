/*
 * button.c
 *
 *  Created on: Feb 24, 2022
 *      Author: emozdzen
 */

#include "button.h"

void Button_Init(Button_t *button, GPIO_TypeDef *port, uint16_t pin) {
	button->port = port;
	button->pin = pin;

	button->curr_state = 0;
	button->prev_state = 0;
}

void Button_Update(Button_t *button) {
	button->prev_state = button->curr_state;

	button->curr_state = !HAL_GPIO_ReadPin(button->port, button->pin);
}

uint8_t Button_IsPressed(Button_t *button) {
	return button->curr_state;
}

uint8_t Button_IsChanged(Button_t *button) {
	return button->curr_state ^ button->prev_state;
}

uint8_t Button_IsClicked(Button_t *button) {
	return (Button_IsPressed(button) && Button_IsChanged(button));
}
