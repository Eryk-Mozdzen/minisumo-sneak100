#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "adc.h"
#include "i2c1.h"
#include "uart2.h"
#include "uart3.h"

#include "cli.h"
#include "gui.h"
#include "motors.h"
#include "periph.h"
#include "display.h"
#include "rc5.h"

#include "robot.h"

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

/*static void blink(void *param) {
	(void)param;

	uint8_t state = 0;

	while(1) {
		led_set_green(state);
		//led_set_yellow(!state);

		state = !state;

		vTaskDelay(200);
	}
}*/

int main() {

	NVIC_SetPriorityGrouping(0);
	clock_init();
	uart2_init();
    uart3_init();
	i2c1_init();
	adc_init();
    
    cli_init();
	gui_init();
	motors_init();
	periph_init();
	rc5_init();

	robot_init();

	//xTaskCreate(blink, "blink", 130, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}