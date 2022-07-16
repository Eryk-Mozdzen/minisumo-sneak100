#ifndef I2C1_H
#define I2C1_H

#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define I2C_RW_WRITE	0
#define I2C_RW_READ		1

void i2c1_init();

uint8_t i2c1_write_8(const uint8_t, const uint8_t, const void *, const uint32_t, const uint32_t);
uint8_t i2c1_read_8(const uint8_t, const uint8_t, void *, const uint32_t, const uint32_t);

uint8_t i2c1_write_16(const uint8_t, const uint16_t, const void *, const uint32_t, const uint32_t);
uint8_t i2c1_read_16(const uint8_t, const uint16_t, void *, const uint32_t, const uint32_t);

#endif