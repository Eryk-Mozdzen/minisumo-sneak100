#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "adc.h"
#include "i2c1.h"
#include "uart2.h"
#include "uart3.h"

#include "cli.h"
#include "motors.h"
#include "periph.h"
#include "display.h"

#include "sprites.h"

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

	//GPIOB->ODR |=GPIO_ODR_OD14;

	while(1) {
		//GPIOB->ODR ^=GPIO_ODR_OD14;
		//GPIOB->ODR ^=GPIO_ODR_OD15;
		
		//uint8_t result;
		//char buffer[256] = {0};

		//uint8_t src[8] = {0x69, 0x01, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0C};
		//result = eeprom_write(0, 0, &src, 8);
		//sprintf(buffer, "Write: %u\n", result);
		//uart2_transmit(buffer, strlen(buffer));
		
		//uint8_t byte[8] = {0};
		//result = eeprom_read(0, 0, &byte, 8);
		//sprintf(buffer, "Read: %u\tData: 0x%02X\t0x%02X\t0x%02X\t0x%02X\t0x%02X\t0x%02X\t0x%02X\t0x%02X\n", result, byte[0], byte[1], byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]);
		//uart2_transmit(buffer, strlen(buffer));

		//display_fill(DISPLAY_COLOR_BLACK);

		display_printf(0, 0, DISPLAY_COLOR_WHITE, display_font_6x8, "                 7.4V");
		display_line(0, 9, 127, 9, DISPLAY_COLOR_WHITE);

		display_printf(0, 16, DISPLAY_COLOR_WHITE, display_font_6x8, "view");
		display_printf(0, 26, DISPLAY_COLOR_WHITE, display_font_6x8, "settings");
		display_printf(0, 36, DISPLAY_COLOR_WHITE, display_font_6x8, "fight");
		display_inverse(30, 30, 32, 10);

		display_line(0, 54, 127, 54, DISPLAY_COLOR_WHITE);
		display_printf(0, 56, DISPLAY_COLOR_WHITE, display_font_6x8, "next     prev     esc");

		//display_bitmap(0, 0, DISPLAY_COLOR_WHITE, bitmap_sneak100_128_64, 128, 64);

		vTaskDelay(200);
	}
}

int main() {

	NVIC_SetPriorityGrouping(0);
	clock_init();
	uart2_init();
    uart3_init();
	i2c1_init();
	adc_init();
    
    cli_init();
	line_init();
	motors_init();
	display_init();
	proximity_init();

	xTaskCreate(blink, "blink", 512, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}