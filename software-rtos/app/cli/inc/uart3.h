#ifndef UART3_H
#define UART3_H

#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define UART3_TX_BUFFER_SIZE	128
#define UART3_RX_BUFFER_SIZE	128

void uart3_init();

void uart3_transmit(void *, uint16_t);
uint8_t uart3_receive(void *);

void USART3_IRQHandler();

#endif