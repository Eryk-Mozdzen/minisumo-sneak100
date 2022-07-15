#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "cli.h"
#include "uart2.h"
#include "uart3.h"
#include "motors.h"

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
	(void)pcTaskName;
	(void)pxTask;

	taskDISABLE_INTERRUPTS();
	while(1);
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationMallocFailedHook() {
	while(1);
}

void clock_init() {
	RCC->CR |=RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY));

    RCC->APB1ENR |=RCC_APB1ENR_PWREN;
    PWR->CR |=(3<<PWR_CR_VOS_Pos);
    FLASH->ACR |=FLASH_ACR_LATENCY_3WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

    RCC->CFGR |=RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_HPRE_DIV1;
    
    RCC->PLLCFGR &=~(0x03F<<RCC_PLLCFGR_PLLM_Pos);
    RCC->PLLCFGR &=~(0x1FF<<RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR &=~(0x003<<RCC_PLLCFGR_PLLP_Pos);
    RCC->PLLCFGR &=~(0x00F<<RCC_PLLCFGR_PLLQ_Pos);
    RCC->PLLCFGR |=(4<<RCC_PLLCFGR_PLLM_Pos) | (168<<RCC_PLLCFGR_PLLN_Pos) | (4<<RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSE;

    RCC->CR |=RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |=RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SW)!=RCC_CFGR_SW_PLL);
}

static void blink(void *param) {
	(void)param;
	
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |=(1<<GPIO_MODER_MODER14_Pos) | (1<<GPIO_MODER_MODER15_Pos);

	GPIOB->ODR |=GPIO_ODR_OD14;

	while(1) {
		GPIOB->ODR ^=GPIO_ODR_OD14;
		GPIOB->ODR ^=GPIO_ODR_OD15;
		vTaskDelay(100);
	}
}

int main() {

	NVIC_SetPriorityGrouping(0);
	clock_init();
	uart2_init();
    uart3_init();
    
    cli_init();
	motors_init();

	xTaskCreate(blink, "blink", 130, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}