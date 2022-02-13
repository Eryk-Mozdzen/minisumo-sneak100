/*
 * memory.h
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint16_t address;

	HAL_StatusTypeDef status;
} Memory_StryctTypeDef;

void Memory_Init(Memory_StryctTypeDef *, I2C_HandleTypeDef *, uint8_t);

HAL_StatusTypeDef Memory_Read(Memory_StryctTypeDef *, uint16_t, void *, size_t);
HAL_StatusTypeDef Memory_Write(Memory_StryctTypeDef *, uint16_t, void *, size_t);

#endif /* INC_MEMORY_H_ */
