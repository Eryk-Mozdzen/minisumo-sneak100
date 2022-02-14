/*
 * sneak100_core.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_CORE_H_
#define INC_CORE_H_

#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "main.h"
#include "usart.h"

#include "line.h"
#include "motor.h"
#include "memory.h"
#include "encoder.h"
#include "display.h"
#include "proximity.h"
#include "bluetooth.h"
#include "rc5_decoder.h"

#include "core_conf.h"
#include "core_def.h"

typedef struct {
	Motor_StructTypeDef motors[4];
	Encoder_StructTypeDef encoders[4];

	LineSensor_StructTypeDef lines[4];
	ProximitySensor_StructTypeDef proximity[4];

	Memory_StryctTypeDef memory;
	Display_StructTypeDef display;

	DecoderRC5_t decoder_rc5;
	Bluetooth_StructTypeDef bluetooth;
} Sneak100_t;

extern Sneak100_t sneak100;

void SNEAK100_Init(Sneak100_t *);

#endif
