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

int __io_putchar(int);
int __io_getchar();

void UART_SetSTDIN(UART_HandleTypeDef *);
void UART_SetSTDOUT(UART_HandleTypeDef *);

#endif /* SNEAK100_UTILITIES_INC_UART_H_ */
