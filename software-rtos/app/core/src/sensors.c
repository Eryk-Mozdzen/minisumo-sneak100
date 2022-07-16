#include "sensors.h"

static uint16_t line_values[4] = {0};

void proximity_init() {
	// PB0  -> FL
	// PB1  -> LL
	// PC14 -> FR
	// PC15 -> RR
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	GPIOB->MODER &=~((3<<GPIO_MODER_MODE0_Pos) | (3<<GPIO_MODER_MODE1_Pos));
	GPIOC->MODER &=~((3<<GPIO_MODER_MODE14_Pos) | (3<<GPIO_MODER_MODE15_Pos));
}

void proximity_get_state(uint8_t *state) {
	state[0] = (GPIOB->IDR & GPIO_IDR_ID1)==0;
	state[1] = (GPIOB->IDR & GPIO_IDR_ID0)==0;
	state[2] = (GPIOC->IDR & GPIO_IDR_ID14)==0;
	state[3] = (GPIOC->IDR & GPIO_IDR_ID15)==0;
}

static void reader(void *param) {
	(void)param;

	while(1) {

		line_values[0] = adc_get_raw(ADC_CHANNEL_LINE_LL);
		line_values[1] = adc_get_raw(ADC_CHANNEL_LINE_LM);
		line_values[2] = adc_get_raw(ADC_CHANNEL_LINE_RM);
		line_values[3] = adc_get_raw(ADC_CHANNEL_LINE_RR);

		vTaskDelay(1000/LINE_READ_FREQ);
	}
}

void line_init() {
	
	xTaskCreate(reader, "line reader", 1024, NULL, 4, NULL);
}

void line_get_state(uint8_t *state) {
	state[0] = (line_values[0]<LINE_THRESHOLD);
	state[1] = (line_values[1]<LINE_THRESHOLD);
	state[2] = 0;//(line_values[2]<LINE_THRESHOLD);
	state[3] = 0;//(line_values[3]<LINE_THRESHOLD);
}

void line_get_raw(uint16_t *raw) {
	memcpy(raw, line_values, 4*sizeof(uint16_t));
}

float get_voltage() {
	const float adc = adc_get_voltage(ADC_CHANNEL_BATT_V);
	return adc/BATT_SCALE;
}

float get_temperature() {
	const float adc = adc_get_voltage(ADC_CHANNEL_TEMP_UC);
	return ((adc - INTERNAL_V_25)/INTERNAL_AVG_SLOPE) + 25.f;
}