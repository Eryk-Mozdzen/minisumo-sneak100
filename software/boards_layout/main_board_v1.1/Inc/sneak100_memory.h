/*
 * sneak100_memory.h
 *
 *  Created on: 28 lis 2021
 *      Author: ermoz
 */

#ifndef INC_SNEAK100_MEMORY_H_
#define INC_SNEAK100_MEMORY_H_

#include <stdio.h>
#include "i2c.h"
#include "memory.h"

#define MEMORY_ADDRESS_VALUE	0x01

extern Memory_StryctTypeDef memory;

void Memory_ErrorHandler(const char *, uint16_t);

void SNEAK100_Memory_Init();
uint8_t SNEAK100_Memory_ReadByte(uint16_t);
void SNEAK100_Memory_WriteByte(uint16_t, uint8_t);
float SNEAK100_Memory_ReadFloat(uint16_t);
void SNEAK100_Memory_WriteFloat(uint16_t, float);

#endif /* INC_SNEAK100_MEMORY_H_ */
