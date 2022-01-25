/*
 * sneak100_memory.c
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#include "sneak100_memory.h"

Memory_StryctTypeDef memory;

void Memory_ErrorHandler(const char *file, uint16_t line) {
	printf("Error in %s: %u\n", file, line);
	Error_Handler();
}

void SNEAK100_Memory_Init() {
	Memory_Init(&memory, &hi2c1, 0x00);
}

uint8_t SNEAK100_Memory_ReadByte(uint16_t address) {
	uint8_t data;
	Memory_Read(&memory, address, &data, 1);
	return data;
}

void SNEAK100_Memory_WriteByte(uint16_t address, uint8_t data) {
	Memory_Write(&memory, address, &data, 1);
}

float SNEAK100_Memory_ReadFloat(uint16_t address) {
	float data;
	Memory_Read(&memory, address, &data, sizeof(float));
	return data;
}

void SNEAK100_Memory_WriteFloat(uint16_t address, float data) {
	Memory_Write(&memory, address, &data, sizeof(float));
}
