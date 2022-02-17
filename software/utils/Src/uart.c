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

void RxBufferUART_Init(RxBufferUART_t *buffer, UART_HandleTypeDef *huart, uint16_t max_size) {
	buffer->huart = huart;
	buffer->max_size = max_size;

	buffer->buffer = (uint8_t *)malloc(buffer->max_size);

	memset(buffer->buffer, 0, buffer->max_size);

	RxBufferUART_Start(buffer);
}

void RxBufferUART_Start(RxBufferUART_t *buffer) {
	HAL_UART_Receive_DMA(buffer->huart, buffer->buffer, buffer->max_size);
}

void RxBufferUART_Stop(RxBufferUART_t *buffer) {
	HAL_UART_AbortReceive(buffer->huart);
}

uint16_t RxBufferUART_ReadUntil(RxBufferUART_t *buffer, void *dest, uint8_t terminator, uint16_t dest_max_size) {

	uint8_t *first = (uint8_t *)memchr(buffer->buffer, terminator, dest_max_size < buffer->max_size ? dest_max_size : buffer->max_size);

	if(!first)
		return 0;

	RxBufferUART_Stop(buffer);

	uint32_t bytes = first - buffer->buffer + 1;

	memcpy(dest, buffer->buffer, bytes);
	memset(buffer->buffer, 0, buffer->max_size);

	((uint8_t *)dest)[bytes] = '\0';

	RxBufferUART_Start(buffer);

	return bytes + 1;
}

void RxBufferUART_RxCpltCallback(RxBufferUART_t *buffer, UART_HandleTypeDef *huart) {
	if(huart!=buffer->huart)
		return;

	RxBufferUART_Start(buffer);
}

