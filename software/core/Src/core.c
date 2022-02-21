/*
 * sneak100_core.c
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#include "core.h"

Sneak100_t sneak100;

static uint16_t adc_dma_buffer[6] = {0};

static void SNEAK100_Core_ReadState();

static float SNEAK100_Core_GetTemperature();
static float SNEAK100_Core_GetSupplyVoltage();

void SNEAK100_Core_Init() {

	sneak100.update_request = 0;

	// state machine init

	FiniteStateMachine_Init(&sneak100.fsm, &sneak100);

	FiniteStateMachine_DefineState(&sneak100.fsm, CORE_STATE_IDLE,		&Core_Idle_Enter,		&Core_Idle_Execute,		NULL);
	FiniteStateMachine_DefineState(&sneak100.fsm, CORE_STATE_READY,		&Core_Ready_Enter,		&Core_Ready_Execute,	NULL);
	FiniteStateMachine_DefineState(&sneak100.fsm, CORE_STATE_PROGRAM,	&Core_Program_Enter,	&Core_Program_Execute,	NULL);
	FiniteStateMachine_DefineState(&sneak100.fsm, CORE_STATE_RUN,		&Core_Run_Enter,		&Core_Run_Execute,		NULL);
	FiniteStateMachine_DefineState(&sneak100.fsm, CORE_STATE_STOP,		&Core_Stop_Enter,		&Core_Stop_Execute,		NULL);

	FiniteStateMachine_DefineTransition(&sneak100.fsm, CORE_STATE_IDLE,		CORE_STATE_READY,	0, NULL, &__Core_Program_SelectEvent);
	FiniteStateMachine_DefineTransition(&sneak100.fsm, CORE_STATE_READY,	CORE_STATE_PROGRAM,	0, NULL, &__Core_Program_SignalEvent);
	FiniteStateMachine_DefineTransition(&sneak100.fsm, CORE_STATE_PROGRAM,	CORE_STATE_READY,	0, NULL, &__Core_ProgramEnd_Event);
	FiniteStateMachine_DefineTransition(&sneak100.fsm, CORE_STATE_READY,	CORE_STATE_RUN,		0, NULL, &__Core_Start_SignalEvent);
	FiniteStateMachine_DefineTransition(&sneak100.fsm, CORE_STATE_RUN,		CORE_STATE_STOP,	0, NULL, &__Core_Stop_SignalEvent);

	// hardware init

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

	Line_Init(&sneak100.lines[LINE_LL], &adc_dma_buffer[3], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&sneak100.lines[LINE_LM], &adc_dma_buffer[2], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&sneak100.lines[LINE_RM], &adc_dma_buffer[1], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&sneak100.lines[LINE_RR], &adc_dma_buffer[0], LINE_THRESHOLD, LINE_POLARITY_BLACK);

	Proximity_Init(&sneak100.proximity[PROXIMITY_LL], PROXIMITY_LL_GPIO_Port, PROXIMITY_LL_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_FL], PROXIMITY_FL_GPIO_Port, PROXIMITY_FL_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_FR], PROXIMITY_FR_GPIO_Port, PROXIMITY_FR_Pin);
	Proximity_Init(&sneak100.proximity[PROXIMITY_RR], PROXIMITY_RR_GPIO_Port, PROXIMITY_RR_Pin);

	// start

	Memory_Read(&sneak100.memory, MEMORY_SETTINGS_ADDRESS, &sneak100.settings, sizeof(RobotSettings_t));
	Memory_Read(&sneak100.memory, MEMORY_FIGHT_DATA_ADDRESS, &sneak100.fight_data, sizeof(RobotFightData_t));

	FiniteStateMachine_Start(&sneak100.fsm, sneak100.fight_data.core_state);
}

void SNEAK100_Core_Update() {
	if(!sneak100.update_request)
		return;

	Line_SetPolarity(&sneak100.lines[LINE_LL], sneak100.settings.dyhlo_color);
	Line_SetPolarity(&sneak100.lines[LINE_LM], sneak100.settings.dyhlo_color);
	Line_SetPolarity(&sneak100.lines[LINE_RM], sneak100.settings.dyhlo_color);
	Line_SetPolarity(&sneak100.lines[LINE_RR], sneak100.settings.dyhlo_color);

	SNEAK100_Core_ReadState();

	Motor_Update(&sneak100.motors[MOTOR_LF]);
	Motor_Update(&sneak100.motors[MOTOR_LB]);
	Motor_Update(&sneak100.motors[MOTOR_RF]);
	Motor_Update(&sneak100.motors[MOTOR_RB]);

	FiniteStateMachine_Update(&sneak100.fsm);
	FiniteStateMachine_Execute(&sneak100.fsm);

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
		sneak100.state.rc5.expired = 0;
	}
}

float SNEAK100_Core_GetTemperature() {
	return __LL_ADC_CALC_TEMPERATURE(ADC_REF_VOLTAGE*1000, adc_dma_buffer[5], LL_ADC_RESOLUTION_12B);
}

float SNEAK100_Core_GetSupplyVoltage() {
	const uint16_t raw = adc_dma_buffer[4];
	const float scale = ((float)(SUPPLY_VOLTAGE_DIVIDER_R1 + SUPPLY_VOLTAGE_DIVIDER_R2))/SUPPLY_VOLTAGE_DIVIDER_R2;
	return ADC_GET_VOLTAGE(raw)*scale;
}

