#ifndef I2C1_H
#define I2C1_H

#include <stdint.h>

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void I2C1_Init();

void I2C1_WriteReg(uint8_t, uint8_t, void *, uint8_t);
void I2C1_ReadReg(uint8_t, uint8_t, void *, uint8_t);

#endif