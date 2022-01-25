/*
 * uart.c
 *
 *  Created on: Aug 28, 2021
 *      Author: ermoz
 */

#include "uart.h"

static UART_HandleTypeDef *uart_stdin;
static UART_HandleTypeDef *uart_stdout;

int __io_putchar(int ch) {
	HAL_UART_Transmit(uart_stdout, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

int __io_getchar() {
	__HAL_UART_CLEAR_OREFLAG(uart_stdin);

	uint8_t ch = 0;
	HAL_UART_Receive(uart_stdin, &ch, 1, HAL_MAX_DELAY);
	return ch;
}

void UART_SetSTDIN(UART_HandleTypeDef *huart) {
	uart_stdin = huart;

	setvbuf(stdin, NULL, _IONBF, 0);
}

void UART_SetSTDOUT(UART_HandleTypeDef *huart) {
	uart_stdout = huart;

	setvbuf(stdout, NULL, _IONBF, 0);
}
