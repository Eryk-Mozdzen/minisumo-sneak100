/*
 * uart.h
 *
 *  Created on: Aug 28, 2021
 *      Author: ermoz
 */

#ifndef SNEAK100_UTILITIES_INC_UART_H_
#define SNEAK100_UTILITIES_INC_UART_H_

#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int __io_putchar(int);
int __io_getchar();

void UART_SetSTDIN(UART_HandleTypeDef *);
void UART_SetSTDOUT(UART_HandleTypeDef *);

typedef struct {
	UART_HandleTypeDef *huart;

	uint16_t max_size;
	uint8_t *buffer;
} RxBufferUART_t;

void RxBufferUART_Init(RxBufferUART_t *, UART_HandleTypeDef *, uint16_t);
void RxBufferUART_Start(RxBufferUART_t *);
void RxBufferUART_Stop(RxBufferUART_t *);

uint16_t RxBufferUART_ReadUntil(RxBufferUART_t *, void *, uint8_t, uint16_t);

void RxBufferUART_RxCpltCallback(RxBufferUART_t *, UART_HandleTypeDef *);

#endif
