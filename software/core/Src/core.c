/*
 * sneak100_core.c
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#include "core.h"

Sneak100_Core_t core;

static uint16_t adc_dma_buffer[6] = {0};

static void SNEAK100_Core_ReadState();

static float SNEAK100_Core_GetTemperature();
static float SNEAK100_Core_GetSupplyVoltage();

void SNEAK100_Core_Init() {

	core.update_request = 0;

	// state machine init

	FiniteStateMachine_Init(&core.fsm, &core);

	FiniteStateMachine_DefineState(&core.fsm, CORE_STATE_IDLE,		&Core_Idle_Enter,		&Core_Idle_Execute,		NULL);
	FiniteStateMachine_DefineState(&core.fsm, CORE_STATE_READY,		&Core_Ready_Enter,		&Core_Ready_Execute,	NULL);
	FiniteStateMachine_DefineState(&core.fsm, CORE_STATE_PROGRAM,	&Core_Program_Enter,	&Core_Program_Execute,	NULL);
	FiniteStateMachine_DefineState(&core.fsm, CORE_STATE_RUN,		&Core_Run_Enter,		&Core_Run_Execute,		NULL);
	FiniteStateMachine_DefineState(&core.fsm, CORE_STATE_STOP,		&Core_Stop_Enter,		&Core_Stop_Execute,		NULL);

	FiniteStateMachine_DefineTransition(&core.fsm, CORE_STATE_IDLE,		CORE_STATE_READY,	0, NULL, &__Core_Program_SelectEvent);
	FiniteStateMachine_DefineTransition(&core.fsm, CORE_STATE_READY,	CORE_STATE_PROGRAM,	0, NULL, &__Core_Program_SignalEvent);
	FiniteStateMachine_DefineTransition(&core.fsm, CORE_STATE_PROGRAM,	CORE_STATE_READY,	0, NULL, &__Core_ProgramEnd_Event);
	FiniteStateMachine_DefineTransition(&core.fsm, CORE_STATE_READY,	CORE_STATE_RUN,		0, NULL, &__Core_Start_SignalEvent);
	FiniteStateMachine_DefineTransition(&core.fsm, CORE_STATE_RUN,		CORE_STATE_STOP,	0, NULL, &__Core_Stop_SignalEvent);

	// fight algorithm

	FiniteStateMachine_Init(&core.fight_fsm, &core);

	FiniteStateMachine_DefineState(&core.fight_fsm, FIGHT_STATE_START,				&Fight_Start_Enter,				NULL,								NULL);
	FiniteStateMachine_DefineState(&core.fight_fsm, FIGHT_STATE_EXPLORE,			&Fight_Explore_Enter,			&Fight_Explore_Execute,				NULL);
	FiniteStateMachine_DefineState(&core.fight_fsm, FIGHT_STATE_ANGLE_MEASUREMENT,	&Fight_AngleMeasurement_Enter,	&Fight_AngleMeasurement_Execute,	NULL);
	FiniteStateMachine_DefineState(&core.fight_fsm, FIGHT_STATE_LINE_MANEUVER,		&Fight_LineManeuver_Enter,		&Fight_LineManeuver_Execute,		NULL);

	FiniteStateMachine_DefineTransition(&core.fight_fsm, FIGHT_STATE_START,				FIGHT_STATE_EXPLORE,			0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&core.fight_fsm, FIGHT_STATE_EXPLORE,			FIGHT_STATE_ANGLE_MEASUREMENT,	0, NULL, &__Fight_DetectLineAny_Event);
	FiniteStateMachine_DefineTransition(&core.fight_fsm, FIGHT_STATE_ANGLE_MEASUREMENT,	FIGHT_STATE_LINE_MANEUVER,		0, NULL, &__Fight_AngleComplete_Event);
	FiniteStateMachine_DefineTransition(&core.fight_fsm, FIGHT_STATE_LINE_MANEUVER,		FIGHT_STATE_EXPLORE,			0, NULL, &__Fight_TurnEnd_Event);

	// hardware init

	Bluetooth_Init(&core.bluetooth, &huart2, BLUETOOTH_EN_GPIO_Port, BLUETOOTH_EN_Pin, BLUETOOTH_ST_GPIO_Port, BLUETOOTH_ST_Pin);

	Display_Init(&core.display, &hi2c1);

	Memory_Init(&core.memory, &hi2c1, 0x00);

	DecoderRC5_Init(&core.decoder_rc5, &htim7, RECEIVER_OUT_GPIO_Port, RECEIVER_OUT_Pin);

	Encoder_Init(&core.encoders[MOTOR_LF], &htim2, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&core.encoders[MOTOR_LB], &htim3, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&core.encoders[MOTOR_RF], &htim4, ENCODER_CPR*MOTOR_GEAR_RATIO);
	Encoder_Init(&core.encoders[MOTOR_RB], &htim5, ENCODER_CPR*MOTOR_GEAR_RATIO);

	Motor_Init(&core.motors[MOTOR_LF], &core.encoders[MOTOR_LF], &htim1, TIM_CHANNEL_3, TIM_CHANNEL_4, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	Motor_Init(&core.motors[MOTOR_LB], &core.encoders[MOTOR_LB], &htim1, TIM_CHANNEL_1, TIM_CHANNEL_2, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	Motor_Init(&core.motors[MOTOR_RF], &core.encoders[MOTOR_RF], &htim8, TIM_CHANNEL_3, TIM_CHANNEL_4, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);
	Motor_Init(&core.motors[MOTOR_RB], &core.encoders[MOTOR_RB], &htim8, TIM_CHANNEL_1, TIM_CHANNEL_2, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, 6);

	Line_Init(&core.lines[LINE_LL], &adc_dma_buffer[3], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&core.lines[LINE_LM], &adc_dma_buffer[2], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&core.lines[LINE_RM], &adc_dma_buffer[1], LINE_THRESHOLD, LINE_POLARITY_BLACK);
	Line_Init(&core.lines[LINE_RR], &adc_dma_buffer[0], LINE_THRESHOLD, LINE_POLARITY_BLACK);

	Proximity_Init(&core.proximity[PROXIMITY_LL], PROXIMITY_LL_GPIO_Port, PROXIMITY_LL_Pin);
	Proximity_Init(&core.proximity[PROXIMITY_FL], PROXIMITY_FL_GPIO_Port, PROXIMITY_FL_Pin);
	Proximity_Init(&core.proximity[PROXIMITY_FR], PROXIMITY_FR_GPIO_Port, PROXIMITY_FR_Pin);
	Proximity_Init(&core.proximity[PROXIMITY_RR], PROXIMITY_RR_GPIO_Port, PROXIMITY_RR_Pin);

	Button_Init(&core.buttons[BUTTON_L], USER_BUTTON_L_GPIO_Port, USER_BUTTON_L_Pin);
	Button_Init(&core.buttons[BUTTON_C], USER_BUTTON_C_GPIO_Port, USER_BUTTON_C_Pin);
	Button_Init(&core.buttons[BUTTON_R], USER_BUTTON_R_GPIO_Port, USER_BUTTON_R_Pin);

	// start

	Memory_Read(&core.memory, MEMORY_SETTINGS_ADDRESS, &core.settings, sizeof(Core_Settings_t));
	Memory_Read(&core.memory, MEMORY_FIGHT_DATA_ADDRESS, &core.fight_data, sizeof(Core_FightData_t));

	FiniteStateMachine_Start(&core.fsm, core.fight_data.core_save_state);

	core.state.temperature = SNEAK100_Core_GetTemperature();
	core.state.battery = SNEAK100_Core_GetSupplyVoltage();
}

void SNEAK100_Core_Update() {
	if(!core.update_request)
		return;

	Line_SetPolarity(&core.lines[LINE_LL], core.settings.dyhlo_color);
	Line_SetPolarity(&core.lines[LINE_LM], core.settings.dyhlo_color);
	Line_SetPolarity(&core.lines[LINE_RM], core.settings.dyhlo_color);
	Line_SetPolarity(&core.lines[LINE_RR], core.settings.dyhlo_color);

	SNEAK100_Core_ReadState();

	Motor_Update(&core.motors[MOTOR_LF]);
	Motor_Update(&core.motors[MOTOR_LB]);
	Motor_Update(&core.motors[MOTOR_RF]);
	Motor_Update(&core.motors[MOTOR_RB]);

	FiniteStateMachine_Update(&core.fsm);
	FiniteStateMachine_Execute(&core.fsm);

	if(Display_GetStatus(&core.display)!=HAL_OK)
		HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin, GPIO_PIN_SET);

	core.update_request = 0;
}

void SNEAK100_Core_UpdateRequest() {
	core.update_request = 1;
}

void SNEAK100_Core_ReadState() {

	for(uint8_t i=0; i<4; i++) {
		core.state.motor[i].position_raw = __HAL_TIM_GET_COUNTER(core.encoders[i].timer);
		core.state.motor[i].position = Encoder_GetPosition(&core.encoders[i]);
		core.state.motor[i].velocity = core.motors[i].curr_vel;
		core.state.motor[i].power = core.motors[i].output;

		core.state.line[i].value = *core.lines[i].read_src;
		core.state.line[i].threshold = core.lines[i].threshold;
		core.state.line[i].polarity = core.lines[i].polarity;
		core.state.line[i].state = Line_GetState(&core.lines[i]);

		core.state.proximity[i] = Proximity_GetState(&core.proximity[i]);
	}

	core.state.temperature = TEMPERATURE_FILTER_ALPHA*SNEAK100_Core_GetTemperature() + (1.f - TEMPERATURE_FILTER_ALPHA)*core.state.temperature;
	core.state.battery = SUPPLY_VOLTAGE_FILTER_ALPHA*SNEAK100_Core_GetSupplyVoltage() + (1.f - SUPPLY_VOLTAGE_FILTER_ALPHA)*core.state.battery;
	core.state.bluetooth = Bluetooth_GetStatus(&core.bluetooth);
	core.state.core_curr_state = core.fsm.states[core.fsm.curr_state_index].id;
	core.state.fight_curr_state = core.fight_fsm.states[core.fight_fsm.curr_state_index].id;

	RC5_Message_t message;
	if(DecoderRC5_GetMessage(&core.decoder_rc5, &message)) {
		core.state.rc5.message = message;
		core.state.rc5.expired = 0;
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

