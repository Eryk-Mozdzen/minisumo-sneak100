#ifndef SENSORS_H
#define SENSORS_H

#include <string.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"
#include "i2c1.h"

#define LINE_READ_FREQ				50
#define LINE_THRESHOLD				1500
#define BATT_SCALE					0.357f
#define INTERNAL_V_25				0.76f
#define INTERNAL_AVG_SLOPE			0.0025f

#define EEPROM_PAGE_NUM				512
#define EEPROM_PAGE_SIZE			64
#define EEPROM_PAGE_ADDRESS_BITS	6		// log(EEPROM_PAGE_SIZE)/log(2)
#define EEPROM_ADDRESS				0x50
#define EEPROM_WRITE_CYCLE_TIME		10		// ms

#define DISPLAY_ADDRESS				0x3C

#define display_read(address, dest, len)	i2c1_read_8(DISPLAY_ADDRESS, (address), (dest), (len), 100)
#define display_write(address, src, len)	i2c1_write_8(DISPLAY_ADDRESS, (address), (src), (len), 100)

void proximity_init();
void proximity_get_state(uint8_t *);

void line_init();
void line_get_state(uint8_t *);
void line_get_raw(uint16_t *);

float get_voltage();
float get_temperature();

uint8_t eeprom_read(uint16_t, uint8_t, void *, uint8_t);
uint8_t eeprom_write(uint16_t, uint8_t, const void *, uint8_t);

#endif