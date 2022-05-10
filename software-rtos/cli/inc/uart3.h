#ifndef UART3_H
#define UART3_H

#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define UART3_TX_BUFFER_SIZE	128
#define UART3_RX_BUFFER_SIZE	128

void UART3_Init();

void UART3_Transmit(void *, uint16_t);
uint8_t UART3_Receive(void *);

void USART3_IRQHandler();

#endif