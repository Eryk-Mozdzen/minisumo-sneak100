#include "adc.h"

static TaskHandle_t xTaskToNotify = NULL;
static SemaphoreHandle_t mutex;

void adc_init() {
	// IN10 -> PC0 -> RR
	// IN11 -> PC1 -> RM
	// IN12 -> PC2 -> LM
	// IN13 -> PC3 -> LL
	// IN14 -> PC4 -> batt
	// IN16 -> temp
	
	// GPIOC
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |=(3<<GPIO_MODER_MODE0_Pos) | (3<<GPIO_MODER_MODE1_Pos) | (3<<GPIO_MODER_MODE2_Pos) | (3<<GPIO_MODER_MODE3_Pos) | (3<<GPIO_MODER_MODE4_Pos);

	// ADC1
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |=ADC_CR2_ADON;
	ADC123_COMMON->CCR |=ADC_CCR_TSVREFE | (3<<ADC_CCR_ADCPRE_Pos) | (15<<ADC_CCR_DELAY_Pos);
	ADC1->SMPR1 |=(7<<ADC_SMPR1_SMP10_Pos) | (7<<ADC_SMPR1_SMP11_Pos) | (7<<ADC_SMPR1_SMP12_Pos) | (7<<ADC_SMPR1_SMP13_Pos) | (7<<ADC_SMPR1_SMP14_Pos) | (7<<ADC_SMPR1_SMP16_Pos);
	ADC1->CR1 |=ADC_CR1_EOCIE;

	NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(ADC_IRQn);

	mutex = xSemaphoreCreateBinary();
	xSemaphoreGive(mutex);
}

uint16_t adc_get_raw(const adc_channel_t channel) {
	if(!xSemaphoreTake(mutex, 100))
		return -1;

	ADC1->SQR3 &=~(0x1F<<ADC_SQR3_SQ1_Pos);
	ADC1->SQR3 |=(channel<<ADC_SQR3_SQ1_Pos);
	
	xTaskToNotify = xTaskGetCurrentTaskHandle();

	ADC1->CR2 |=ADC_CR2_SWSTART;
	
	uint16_t data = 0;

	if(ulTaskNotifyTakeIndexed(0, pdFALSE, 100))
		data = ADC1->DR;

	xSemaphoreGive(mutex);

	return data;
}

float adc_get_voltage(const adc_channel_t channel) {
	const uint16_t raw = adc_get_raw(channel);
	return ADC_REFERENCE*(((float)raw)/((float)ADC_RESOLUTION));
}

void ADC_IRQHandler() {
	if(ADC1->SR & ADC_SR_EOC) {
		ADC1->SR &=~ADC_SR_EOC;

		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveIndexedFromISR(xTaskToNotify, 0, &xHigherPriorityTaskWoken);

		xTaskToNotify = NULL;

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}