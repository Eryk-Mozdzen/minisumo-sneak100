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
	Motor_t motors[4];
	Encoder_t encoders[4];

	LineSensor_t lines[4];
	ProximitySensor_t proximity[4];

	Memory_t memory;
	Display_t display;

	DecoderRC5_t decoder_rc5;
	Bluetooth_t bluetooth;
} Sneak100_t;

extern Sneak100_t sneak100;

void SNEAK100_Core_Init(Sneak100_t *);

float SNEAK100_Core_GetTemperature();
float SNEAK100_Core_GetSupplyVoltage();

#endif
