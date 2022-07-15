#ifndef UART2_H
#define UART2_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "cli.h"

#define UART2_TX_BUFFER_SIZE	CLI_LINE_MAX_SIZE

void uart2_init();
void uart2_transmit(void *, size_t);

void USART2_IRQHandler();

#endif