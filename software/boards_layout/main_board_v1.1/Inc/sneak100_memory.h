/*
 * sneak100_memory.h
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#ifndef INC_SNEAK100_MEMORY_H_
#define INC_SNEAK100_MEMORY_H_

#include "i2c.h"
#include "memory.h"

extern Memory_StryctTypeDef memory;

#define SNEAK100_MEMORY_SETTINGS_ADDRESS	0x00

typedef enum {
	SETTINGS_MODE_MODULE,
	SETTINGS_MODE_BUTTON,
	SETTINGS_MODE_RC_RC5,
	SETTINGS_MODE_RC_BLUETOOTH,
	SETTINGS_MODE_NUM
} Settings_Mode_EnumTypeDef;

typedef enum {
	SETTINGS_DYHLO_BLACK,
	SETTINGS_DYHLO_WHITE,
	SETTINGS_DYHLO_AUTO,
	SETTINGS_DYHLO_NUM
} Settings_Dyhlo_EnumTypeDef;

typedef enum {
	SETTINGS_STRATEGY_AGRESSIVE,
	SETTINGS_STRATEGY_DEFENSIVE,
	SETTINGS_STRATEGY_PASSIVE,
	SETTINGS_STRATEGY_NUM
} Settings_Strategy_EnumTypeDef;

typedef struct {
	Settings_Mode_EnumTypeDef mode;
	Settings_Dyhlo_EnumTypeDef dyhlo;
	Settings_Strategy_EnumTypeDef strategy;
} RobotSettings_StructTypeDef;

void SNEAK100_Memory_Init();

RobotSettings_StructTypeDef SNEAK100_Memory_ReadSettings();
void SNEAK100_Memory_WriteSettings(RobotSettings_StructTypeDef);

#endif
