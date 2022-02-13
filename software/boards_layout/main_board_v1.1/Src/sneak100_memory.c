/*
 * sneak100_memory.c
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#include "sneak100_memory.h"

Memory_StryctTypeDef memory;

void SNEAK100_Memory_Init() {
	Memory_Init(&memory, &hi2c1, 0x00);
}

RobotSettings_StructTypeDef SNEAK100_Memory_ReadSettings() {
	RobotSettings_StructTypeDef settings;

	Memory_Read(&memory, SNEAK100_MEMORY_SETTINGS_ADDRESS, &settings, sizeof(RobotSettings_StructTypeDef));

	return settings;
}

void SNEAK100_Memory_WriteSettings(RobotSettings_StructTypeDef settings) {
	Memory_Write(&memory, SNEAK100_MEMORY_SETTINGS_ADDRESS, &settings, sizeof(RobotSettings_StructTypeDef));
}
