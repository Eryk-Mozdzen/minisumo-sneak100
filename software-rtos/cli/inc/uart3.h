#ifndef UART3_H
#define UART3_H

#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void UART3_Init();

uint8_t UART3_Transmit(void *, uint16_t);
uint8_t UART3_Receive(void *, uint16_t);

void USART3_IRQHandler();

#endif