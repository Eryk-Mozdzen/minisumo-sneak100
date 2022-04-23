#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "config.h"
#include "cli.h"

void greenTask(void *param) {
    (void)param;

    while(1) {
        GPIOB->BSRR |=GPIO_BSRR_BS15;
        vTaskDelay(1000);
        
        GPIOB->BSRR |=GPIO_BSRR_BR15;
        vTaskDelay(1000);
    }
}

void yellowTask(void *param) {
    (void)param;

    while(1) {
        GPIOB->BSRR |=GPIO_BSRR_BS14;
        vTaskDelay(100);
        
        GPIOB->BSRR |=GPIO_BSRR_BR14;
        vTaskDelay(100);
    }
}

int main() {

    Setup();

    CLI_Init();

    UART3_Init();
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |=GPIO_MODER_MODER15_0 | GPIO_MODER_MODER14_0;;

    xTaskCreate(greenTask, "led green", 1024, NULL, 4, NULL);
    xTaskCreate(yellowTask, "led yellow", 1024, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}