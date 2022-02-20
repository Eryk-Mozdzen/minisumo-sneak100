/*
 * sneak100_core.c
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#include "core.h"

Sneak100_t sneak100;

static uint16_t adc_dma_buffer[6] = {0};

void SNEAK100_Core_Init() {

	sneak100.update_request = 0;

	Bluetooth_Init(&sneak100.bluetooth, &huart2, BLUETOOTH_EN_GPIO_Port, BLUETOOTH_EN_Pin, BLUETOOTH_ST_GPIO_Port, BLUETOOTH_ST_Pin);

	Display_Init(&sneak100.display, &hi2c1);

	Memory_Init(&sneak100.memory, &hi2c1, 0x00);

	DecoderRC5_Init(&sneak100.decoder_rc5, &htim7, RECEIVER_OUT_GPIO_Port, RECEIVER_OUT_Pin);

	Encoder_Init(&sneak100.encoders[MOTOR_LF], &htim2, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100.encoders[MOTOR_LB], &htim3, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100.encoders[MOTOR_RF], &htim4, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&sneak100.encoders[MOTOR_RB], &htim5, ENCODER_CPR*MOTOR_GEAR_RATIO);

	Motor_Init(&sneak100.motors[MOTOR_LF], &sneak100.encoders[MOTOR_LF], &htim1, TIM_CHANNEL_3, TIM_CHANNEL_4, MOTOR_DIRECTION_CW, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100.motors[MOTOR_LB], &sneak100.encoders[MOTOR_LB], &htim1, TIM_CHANNEL_1, TIM_CHANNEL_2, MOTOR_DIRECTION_CW, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100.motors[MOTOR_RF], &sneak100.encoders[MOTOR_RF], &htim8, TIM_CHANNEL_3, TIM_CHANNEL_4, MOTOR_DIRECTION_CC, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);
	Motor_Init(&sneak100.motors[MOTOR_RB], &sneak100.encoders[MOTOR_RB], &htim8, TIM_CHANNEL_1, TIM_CHANNEL_2, MOTOR_DIRECTION_CC, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_IBAND);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, 6);

	Line_Init(&sneak100.lines[LINE_LL], &adc_dma_buffer[3], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100.lines[LINE_LM], &adc_dma_buffer[2], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100.lines[LINE_RM], &adc_dma_buffer[1], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);
	Line_Init(&sneak100.lines[LINE_RR], &adc_dma_buffer[0], LINE_THRESHOLD, DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE);

	Proximity_Init(&sneak100.proximity[PROXIMITY_LL], PROXIMITY_LL_GPIO_Port, PROXIMITY_LL_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_FL], PROXIMITY_FL_GPIO_Port, PROXIMITY_FL_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_FR], PROXIMITY_FR_GPIO_Port, PROXIMITY_FR_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_RR], PROXIMITY_RR_GPIO_Port, PROXIMITY_RR_Pin);
}

void SNEAK100_Core_Update() {
	if(!sneak100.update_request)
		return;

	SNEAK100_Core_ReadState();

	Motor_Update(&sneak100.motors[MOTOR_LF]);
	Motor_Update(&sneak100.motors[MOTOR_LB]);
	Motor_Update(&sneak100.motors[MOTOR_RF]);
	Motor_Update(&sneak100.motors[MOTOR_RB]);

	if(Display_GetStatus(&sneak100.display)!=HAL_OK)
		HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin, GPIO_PIN_SET);

	sneak100.update_request = 0;
}

void SNEAK100_Core_UpdateRequest() {
	sneak100.update_request = 1;
}

void SNEAK100_Core_ReadState() {

	for(uint8_t i=0; i<4; i++) {
		sneak100.state.motor[i].position_raw = Encoder_GetPositionRaw(&sneak100.encoders[i]);
		sneak100.state.motor[i].position = Encoder_GetPosition(&sneak100.encoders[i]);
		sneak100.state.motor[i].velocity = Encoder_GetVelocity(&sneak100.encoders[i]);
		sneak100.state.motor[i].power = sneak100.motors[i].output;

		sneak100.state.line[i].value = *sneak100.lines[i].read_src;
		sneak100.state.line[i].threshold = sneak100.lines[i].threshold;
		sneak100.state.line[i].polarity = sneak100.lines[i].polarity;
		sneak100.state.line[i].state = Line_GetState(&sneak100.lines[i]);

		sneak100.state.proximity[i] = Proximity_GetState(&sneak100.proximity[i]);
	}

	sneak100.state.temperature = SNEAK100_Core_GetTemperature();
	sneak100.state.battery = SNEAK100_Core_GetSupplyVoltage();
	sneak100.state.bluetooth = Bluetooth_GetStatus(&sneak100.bluetooth);

	RC5_Message_t message;
	if(DecoderRC5_GetMessage(&sneak100.decoder_rc5, &message)) {
		sneak100.state.rc5.message = message;
		sneak100.state.rc5.seen = 0;
	}
}

void SNEAK100_Core_ReadSettings() {
	Memory_Read(&sneak100.memory, MEMORY_SETTINGS_ADDRESS, &sneak100.settings, sizeof(RobotSettings_t));

	// if settings in eeprom are invalid set default parameters
	if(sneak100.settings.mode>=SETTINGS_MODE_NUM)
		sneak100.settings.mode = SETTINGS_MODE_MODULE;
	if(sneak100.settings.dyhlo>=SETTINGS_DYHLO_NUM)
		sneak100.settings.dyhlo = SETTINGS_DYHLO_AUTO;
	if(sneak100.settings.strategy>=SETTINGS_STRATEGY_NUM)
		sneak100.settings.strategy = SETTINGS_STRATEGY_AGRESSIVE;

	SNEAK100_Core_ApplySettings();
}

void SNEAK100_Core_WriteSettings() {
	Memory_Write(&sneak100.memory, MEMORY_SETTINGS_ADDRESS, &sneak100.settings, sizeof(RobotSettings_t));

	SNEAK100_Core_ApplySettings();
}

void SNEAK100_Core_ApplySettings() {
	if(sneak100.settings.dyhlo!=SETTINGS_DYHLO_AUTO) {
		Line_SetPolarity(&sneak100.lines[LINE_LL], sneak100.settings.dyhlo);
		Line_SetPolarity(&sneak100.lines[LINE_LM], sneak100.settings.dyhlo);
		Line_SetPolarity(&sneak100.lines[LINE_RM], sneak100.settings.dyhlo);
		Line_SetPolarity(&sneak100.lines[LINE_RR], sneak100.settings.dyhlo);

		return;
	}

	uint8_t value = 0;
	value +=Line_GetState(&sneak100.lines[LINE_LL]);
	value +=Line_GetState(&sneak100.lines[LINE_LM]);
	value +=Line_GetState(&sneak100.lines[LINE_RM]);
	value +=Line_GetState(&sneak100.lines[LINE_RR]);

	if(!value)
		return;

	Line_Polarity_t polarity = DYHLO_BLACK_WITH_WHITE_CIRCUMFERENCE;
	if(value==4)
		polarity = !Line_GetPolarity(&sneak100.lines[LINE_LL]);

	Line_SetPolarity(&sneak100.lines[LINE_LL], polarity);
	Line_SetPolarity(&sneak100.lines[LINE_LM], polarity);
	Line_SetPolarity(&sneak100.lines[LINE_RM], polarity);
	Line_SetPolarity(&sneak100.lines[LINE_RR], polarity);
}

float SNEAK100_Core_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(ADC_REF_VOLTAGE*1000, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}

float SNEAK100_Core_GetSupplyVoltage() {
	const uint16_t raw = adc_dma_buffer[4];
	const float scale = ((float)(SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2))/SUPPLY_VOLTAGE_DIVIDER_R2;
	return ADC_GET_VOLTAGE(raw)*scale;
}

