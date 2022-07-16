#include "sensors.h"

static float analog_values[6] = {0};

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

		analog_values[0] = adc_get_voltage(ADC_CHANNEL_LINE_LL);
		analog_values[1] = adc_get_voltage(ADC_CHANNEL_LINE_LM);
		analog_values[2] = adc_get_voltage(ADC_CHANNEL_LINE_RM);
		analog_values[3] = adc_get_voltage(ADC_CHANNEL_LINE_RR);
		analog_values[4] = adc_get_voltage(ADC_CHANNEL_BATT_V);
		analog_values[5] = adc_get_voltage(ADC_CHANNEL_TEMP_UC);

		char buffer[128] = {0};
		sprintf(buffer, "%f\t%f\t%f\t%f\n", (double)analog_values[0], (double)analog_values[1], (double)analog_values[2], (double)analog_values[3]);
		uart2_transmit(buffer, strlen(buffer));

		vTaskDelay(1000/ADC_READ_FREQ);
	}
}

void line_init() {
	
	xTaskCreate(reader, "adc", 1024, NULL, 4, NULL);
}

void line_get_state(uint8_t *state) {
	state[0] = (analog_values[0]<LINE_THRESHOLD);
	state[1] = (analog_values[1]<LINE_THRESHOLD);
	state[2] = (analog_values[2]<LINE_THRESHOLD);
	state[3] = (analog_values[3]<LINE_THRESHOLD);
}