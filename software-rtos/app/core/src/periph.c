#include "periph.h"

static uint32_t eeprom_last_write = 0;
static uint16_t line_values[4] = {0};
static float temp = 25;
static float batt = 7.4;

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
	state[2] = (line_values[2]<LINE_THRESHOLD);
	state[3] = (line_values[3]<LINE_THRESHOLD);
}

void line_get_raw(uint16_t *raw) {
	memcpy(raw, line_values, 4*sizeof(uint16_t));
}

float get_voltage() {
	const float adc = adc_get_voltage(ADC_CHANNEL_BATT_V);
	const float b = adc/BATT_SCALE;

	batt = (1.f - BATT_ALPHA)*batt + BATT_ALPHA*b;

	return batt;
}

float get_temperature() {
	const float adc = adc_get_voltage(ADC_CHANNEL_TEMP_UC);
	const float t = ((adc - INTERNAL_V_25)/INTERNAL_AVG_SLOPE) + 25.f;

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