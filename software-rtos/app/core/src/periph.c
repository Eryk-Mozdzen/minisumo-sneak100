#include "periph.h"

static uint32_t eeprom_last_write = 0;
static uint16_t line_values[4] = {0};
static float temp;
static float batt;

static void reader(void *param) {
	(void)param;

	batt = GET_SUPPLY_VOLTAGE(adc_get_voltage(ADC_CHANNEL_BATT_V));
	temp = GET_TEMPERATURE(adc_get_voltage(ADC_CHANNEL_TEMP_UC));

	while(1) {

		line_values[0] = adc_get_raw(ADC_CHANNEL_LINE_LL);
		line_values[1] = adc_get_raw(ADC_CHANNEL_LINE_LM);
		line_values[2] = adc_get_raw(ADC_CHANNEL_LINE_RM);
		line_values[3] = adc_get_raw(ADC_CHANNEL_LINE_RR);

		vTaskDelay(1000/LINE_READ_FREQ);
	}
}

void periph_init() {
	// PB0  -> FL
	// PB1  -> LL
	// PC14 -> FR
	// PC15 -> RR
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	GPIOB->MODER &=~((3<<GPIO_MODER_MODE0_Pos) | (3<<GPIO_MODER_MODE1_Pos));
	GPIOC->MODER &=~((3<<GPIO_MODER_MODE14_Pos) | (3<<GPIO_MODER_MODE15_Pos));

	// PB14 -> yellow led
	// PB15 -> green led
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |=(1<<GPIO_MODER_MODER14_Pos) | (1<<GPIO_MODER_MODER15_Pos);

	xTaskCreate(reader, "periph reader", 1024, NULL, 4, NULL);
}

void proximity_get_state(uint8_t *state) {
	state[0] = (GPIOB->IDR & GPIO_IDR_ID1)==0;
	state[1] = (GPIOB->IDR & GPIO_IDR_ID0)==0;
	state[2] = (GPIOC->IDR & GPIO_IDR_ID14)==0;
	state[3] = (GPIOC->IDR & GPIO_IDR_ID15)==0;
}

void led_set_yellow(uint8_t state) {
	if(state)
		GPIOB->ODR |=GPIO_ODR_OD14;
	else
		GPIOB->ODR &=~GPIO_ODR_OD14;
}

void led_set_green(uint8_t state) {
	if(state)
		GPIOB->ODR |=GPIO_ODR_OD15;
	else
		GPIOB->ODR &=~GPIO_ODR_OD15;
}

void line_get_state(uint8_t *state) {
	state[0] = (line_values[0]<LINE_THRESHOLD);
	state[1] = (line_values[1]<LINE_THRESHOLD);
	state[2] = (line_values[2]<LINE_THRESHOLD);
	state[3] = (line_values[3]<LINE_THRESHOLD);
}

void line_get_raw(uint16_t *raw) {
	memcpy(raw, line_values, 4*sizeof(uint16_t));
}

float get_voltage() {
	const float b = GET_SUPPLY_VOLTAGE(adc_get_voltage(ADC_CHANNEL_BATT_V));

	batt = (1.f - BATT_ALPHA)*batt + BATT_ALPHA*b;

	return batt;
}

float get_temperature() {
	const float t = GET_TEMPERATURE(adc_get_voltage(ADC_CHANNEL_TEMP_UC));

	temp = (1.f - INTERNAL_ALPHA)*temp + INTERNAL_ALPHA*t;

	return temp;
}

uint8_t eeprom_read(uint16_t page, uint8_t offset, void *dest, uint8_t size) {
	xTaskDelayUntil(&eeprom_last_write, EEPROM_WRITE_CYCLE_TIME);

	if(page>=EEPROM_PAGE_NUM)
		page = EEPROM_PAGE_NUM - 1;
	if(offset>=EEPROM_PAGE_SIZE)
		offset = EEPROM_PAGE_SIZE - 1;
	if(size>=(EEPROM_PAGE_SIZE - offset))
		size = EEPROM_PAGE_SIZE - offset;

	return i2c1_read_16(EEPROM_ADDRESS, (page<<EEPROM_PAGE_ADDRESS_BITS) | offset, dest, size, 100);
}

uint8_t eeprom_write(uint16_t page, uint8_t offset, const void *src, uint8_t size) {
	xTaskDelayUntil(&eeprom_last_write, EEPROM_WRITE_CYCLE_TIME);
	
	eeprom_last_write = xTaskGetTickCount();

	if(page>=EEPROM_PAGE_NUM)
		page = EEPROM_PAGE_NUM - 1;
	if(offset>=EEPROM_PAGE_SIZE)
		offset = EEPROM_PAGE_SIZE - 1;
	if(size>=(EEPROM_PAGE_SIZE - offset))
		size = EEPROM_PAGE_SIZE - offset;

	return i2c1_write_16(EEPROM_ADDRESS, (page<<EEPROM_PAGE_ADDRESS_BITS) | offset, src, size, 100);
}