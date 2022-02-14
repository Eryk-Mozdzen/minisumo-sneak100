/*
 * sneak100_core.c
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#include "core.h"

Sneak100_t sneak100;

static uint16_t adc_dma_buffer[6] = {0};

void SNEAK100_Init(Sneak100_t *sneak100) {
	Display_Init(&sneak100->display, &hi2c1);
	Memory_Init(&sneak100->memory, &hi2c1, 0x00);

	DecoderRC5_Init(&sneak100->decoder_rc5, &htim7, RECEIVER_OUT_GPIO_Port, RECEIVER_OUT_Pin);

	Encoder_Init(&sneak100->encoders[MOTOR_LF], &htim2, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_LB], &htim3, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_RF], &htim4, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100->encoders[MOTOR_RB], &htim5, ENCODER_CPR*MOTOR_GEAR_RATIO);

	Motor_ConfigTypeDef config = {0};
	config.pid_p = MOTOR_PID_P;
	config.pid_i = MOTOR_PID_I;
	config.pid_d = MOTOR_PID_D;
	config.pid_iband = MOTOR_PID_IBAND;

	config.timer = &htim1;
	config.channel_in1 = TIM_CHANNEL_3;
	config.channel_in2 = TIM_CHANNEL_4;
	config.direction = DIRECTION_CW;
	Motor_Init(&sneak100->motors[MOTOR_LF], &sneak100->encoders[MOTOR_LF], config);

	config.timer = &htim1;
	config.channel_in1 = TIM_CHANNEL_1;
	config.channel_in2 = TIM_CHANNEL_2;
	config.direction = DIRECTION_CW;
	Motor_Init(&sneak100->motors[MOTOR_LB], &sneak100->encoders[MOTOR_LB], config);

	config.timer = &htim8;
	config.channel_in1 = TIM_CHANNEL_3;
	config.channel_in2 = TIM_CHANNEL_4;
	config.direction = DIRECTION_CC;
	Motor_Init(&sneak100->motors[MOTOR_RF], &sneak100->encoders[MOTOR_RF], config);

	config.timer = &htim8;
	config.channel_in1 = TIM_CHANNEL_1;
	config.channel_in2 = TIM_CHANNEL_2;
	config.direction = DIRECTION_CC;
	Motor_Init(&sneak100->motors[MOTOR_RB], &sneak100->encoders[MOTOR_RB], config);

	sneak100->proximity[PROXIMITY_LL].GPIOx = PROXIMITY_LL_GPIO_Port;
	sneak100->proximity[PROXIMITY_LL].GPIO_Pin = PROXIMITY_LL_Pin;

	sneak100->proximity[PROXIMITY_FL].GPIOx = PROXIMITY_FL_GPIO_Port;
	sneak100->proximity[PROXIMITY_FL].GPIO_Pin = PROXIMITY_FL_Pin;

	sneak100->proximity[PROXIMITY_FR].GPIOx = PROXIMITY_FR_GPIO_Port;
	sneak100->proximity[PROXIMITY_FR].GPIO_Pin = PROXIMITY_FR_Pin;

	sneak100->proximity[PROXIMITY_RR].GPIOx = PROXIMITY_RR_GPIO_Port;
	sneak100->proximity[PROXIMITY_RR].GPIO_Pin = PROXIMITY_RR_Pin;

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, 6);

	Line_Init(&sneak100->lines[LINE_LL], &adc_dma_buffer[3], LINE_THRESHOLD);
	Line_Init(&sneak100->lines[LINE_LM], &adc_dma_buffer[2], LINE_THRESHOLD);
	Line_Init(&sneak100->lines[LINE_RM], &adc_dma_buffer[1], LINE_THRESHOLD);
	Line_Init(&sneak100->lines[LINE_RR], &adc_dma_buffer[0], LINE_THRESHOLD);

	sneak100->bluetooth.huart = &huart2;
	sneak100->bluetooth.EN_Port = BLUETOOTH_EN_GPIO_Port;
	sneak100->bluetooth.EN_Pin = BLUETOOTH_EN_Pin;
	sneak100->bluetooth.STATUS_Port = BLUETOOTH_ST_GPIO_Port;
	sneak100->bluetooth.STATUS_Pin = BLUETOOTH_ST_Pin;
	sneak100->bluetooth.rx_data_size = 8;
	Bluetooth_Init(&sneak100->bluetooth);

#if 0
	Bluetooth_ConfigTypeDef config = {0};
	config.name = "Sneak100";
	config.password = "7777";
	config.baudrate = BAUDRATE_38400;
	if(Bluetooth_SetConfig(&sneak100->bluetooth, config)!=HAL_OK) {
		HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin, GPIO_PIN_SET);
	}
#endif
}

static float __SNEAK100_ADC_ConvertToVoltage(uint16_t read_raw) {
	return ((float)read_raw/4095.f)*3.3f;
}

float SNEAK100_ADC_GetSupplyVoltage() {
	const uint16_t raw = adc_dma_buffer[4];
	const float scale = (SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2)/SUPPLY_VOLTAGE_DIVIDER_R2;
	return __SNEAK100_ADC_ConvertToVoltage(raw)*scale;
}

float SNEAK100_ADC_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(3270, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}
