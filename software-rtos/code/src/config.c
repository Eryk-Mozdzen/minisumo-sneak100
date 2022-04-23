#include "config.h"

void Clock_Init() {
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

}

void UsageFault_Handler() {
    while(1);
}

void BusFault_Handler() {
    while(1);
}

void MemMang_Handler() {
    while(1);
}

void HardFault_Handler() {
    while(1);
}