#ifndef UART3_H
#define UART3_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "cli.h"

#define UART3_TX_BUFFER_SIZE	CLI_LINE_MAX_SIZE
#define UART3_RX_BUFFER_SIZE	CLI_LINE_MAX_SIZE

void uart3_init();
void uart3_transmit(void *, size_t);

void USART3_IRQHandler();

#endif