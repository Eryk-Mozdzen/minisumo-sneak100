#ifndef CONFIG_H
#define CONFIG_H

#include <inttypes.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

void Clock_Init();

void vApplicationStackOverflowHook(TaskHandle_t, char *);
void vApplicationGetIdleTaskMemory(StaticTask_t **, StackType_t **, uint32_t *);
void vApplicationMallocFailedHook();

void UsageFault_Handler();
void BusFault_Handler();
void MemMang_Handler();
void HardFault_Handler();


#endif