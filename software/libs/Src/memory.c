/*
 * memory.c
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#include "memory.h"

void Memory_Init(Memory_t *memory, I2C_HandleTypeDef *hi2c, uint8_t address) {
	memory->hi2c = hi2c;
	//memory->address = 0xA0 | address<<1;
	memory->address = 0xA1 | address<<1;

	memory->status = HAL_OK;
}

HAL_StatusTypeDef Memory_Read(Memory_t *memory, uint16_t address, void *data, size_t len) {
	memory->status = HAL_I2C_Mem_Read(memory->hi2c, memory->address, address, 2, (uint8_t*)data, len, 10);

	HAL_Delay(5);

	return memory->status;
}

HAL_StatusTypeDef Memory_Write(Memory_t *memory, uint16_t address, void *data, size_t len) {
	memory->status = HAL_I2C_Mem_Write(memory->hi2c, memory->address, address, 2, (uint8_t*)data, len, 10);

	HAL_Delay(5);

	return memory->status;
}
