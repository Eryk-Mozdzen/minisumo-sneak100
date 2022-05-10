#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "config.h"
#include "cli.h"

int main() {

    Setup();
    UART3_Init();

    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |=GPIO_MODER_MODER15_0 | GPIO_MODER_MODER14_0;
    
    CLI_Init();

    vTaskStartScheduler();

    return 0;
}