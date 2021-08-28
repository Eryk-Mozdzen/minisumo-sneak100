/*
 * uart.c
 *
 *  Created on: Aug 28, 2021
 *      Author: ermoz
 */

#include "uart.h"

static UART_HandleTypeDef *communication_uart;

int __io_putchar(int ch) {
	HAL_UART_Transmit(communication_uart, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

int __io_getchar() {
	uint8_t ch = 0;
	__HAL_UART_CLEAR_OREFLAG(communication_uart);
	HAL_UART_Receive(communication_uart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

void UART_SetActive(UART_HandleTypeDef *huart) {
	communication_uart = huart;

	//setvbuf(stdin, NULL, _IONBF, 0);
}
