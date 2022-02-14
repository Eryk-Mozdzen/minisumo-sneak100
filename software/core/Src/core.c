/*
 * sneak100_core.c
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#include "core.h"

Sneak100_t sneak100;

static uint16_t adc_dma_buffer[6] = {0};

void SNEAK100_Core_Init(Sneak100_t *sneak100) {
	Display_Init(&sneak100->display, &hi2c1);

	Memory_Init(&sneak100->memory, &hi2c1, 0x00);

	DecoderRC5_Init(&sneak100->decoder_rc5, &htim7, RECEIVER_OUT_GPIO_Port, RECEIVER_OUT_Pin);

	Bluetooth_Init(&sneak100->bluetooth, &huart2, BLUETOOTH_EN_GPIO_Port, BLUETOOTH_EN_Pin, BLUETOOTH_ST_GPIO_Port, BLUETOOTH_ST_Pin, BLUETOOTH_PWR_GPIO_Port, BLUETOOTH_PWR_Pin);

	Encoder_Init(&sneak100->encoders[MOTOR_LF], &htim2, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_LB], &htim3, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_RF], &htim4, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_RB], &htim5, ENCODER_CPR*MOTOR_GEAR_RATIO);

	Motor_Init(&sneak100->motors[MOTOR_LF], &sneak100->encoders[MOTOR_LF], &htim1, TIM_CHANNEL_3, TIM_CHANNEL_4, DIRECTION_CW, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100->motors[MOTOR_LB], &sneak100->encoders[MOTOR_LB], &htim1, TIM_CHANNEL_1, TIM_CHANNEL_2, DIRECTION_CW, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100->motors[MOTOR_RF], &sneak100->encoders[MOTOR_RF], &htim8, TIM_CHANNEL_3, TIM_CHANNEL_4, DIRECTION_CC, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100->motors[MOTOR_RB], &sneak100->encoders[MOTOR_RB], &htim8, TIM_CHANNEL_1, TIM_CHANNEL_2, DIRECTION_CC, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, 6);

	Line_Init(&sneak100->lines[LINE_LL], &adc_dma_buffer[3], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100->lines[LINE_LM], &adc_dma_buffer[2], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100->lines[LINE_RM], &adc_dma_buffer[1], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100->lines[LINE_RR], &adc_dma_buffer[0], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);

	ProximitySensor_Init(&sneak100->proximity[PROXIMITY_LL], PROXIMITY_LL_GPIO_Port, PROXIMITY_LL_Pin);
	ProximitySensor_Init(&sneak100->proximity[PROXIMITY_FL], PROXIMITY_FL_GPIO_Port, PROXIMITY_FL_Pin);
	ProximitySensor_Init(&sneak100->proximity[PROXIMITY_FR], PROXIMITY_FR_GPIO_Port, PROXIMITY_FR_Pin);
	ProximitySensor_Init(&sneak100->proximity[PROXIMITY_RR], PROXIMITY_RR_GPIO_Port, PROXIMITY_RR_Pin);
}

float SNEAK100_Core_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(ADC_REF_VOLTAGE*1000, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}

float SNEAK100_Core_GetSupplyVoltage() {
	const uint16_t raw = adc_dma_buffer[4];
	const float scale = (SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2)/SUPPLY_VOLTAGE_DIVIDER_R2;
	return ADC_GET_VOLTAGE(raw)*scale;
}

