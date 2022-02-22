/*
 * core_states.c
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#include "core_states.h"

static void SaveState(Sneak100_t *, CoreState_t);
static void SaveDyhloID(Sneak100_t *, uint8_t);

static void SaveState(Sneak100_t *sneak100, CoreState_t state) {
	sneak100->fight_data.core_save_state = state;
	Memory_Write(&sneak100->memory, MEMORY_FIGHT_DATA_ADDRESS, &sneak100->fight_data, sizeof(RobotFightData_t));
}

static void SaveDyhloID(Sneak100_t *sneak100, uint8_t id) {
	sneak100->fight_data.dyhlo_id = id;
	Memory_Write(&sneak100->memory, MEMORY_FIGHT_DATA_ADDRESS, &sneak100->fight_data, sizeof(RobotSettings_t));
}

// enter

void Core_Idle_Enter(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

void Core_Ready_Enter(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

void Core_Program_Enter(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	sneak100_ptr->state.rc5.expired = 1;
	sneak100_ptr->interface_flag.program_blink_counter = 0;

	uint8_t id = MODULE_RC5_CMD_MASK_DYHLO & sneak100_ptr->state.rc5.message.command;

	SaveDyhloID(sneak100_ptr, id);
}

void Core_Run_Enter(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_RUN);
}

void Core_Stop_Enter(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

// execute

void Core_Idle_Execute(void *data) {
	//Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// do nothing
}

void Core_Ready_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// do nothing

	if(!sneak100_ptr->interface_flag.button_start)
		sneak100_ptr->interface_flag.ready_button_start_click_time = HAL_GetTick();
}

void Core_Program_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// save RC5 programming data
	// blink yellow led two times

	sneak100_ptr->interface_flag.program_blink_counter +=CORE_UPDATE_PERIOD;

	if(sneak100_ptr->interface_flag.program_blink_counter<0.5f*MODULE_RC5_LED_BLINK_PERIOD)
		HAL_GPIO_WritePin(USER_LED_YELLOW_GPIO_Port, USER_LED_YELLOW_Pin, GPIO_PIN_SET);
	else if(sneak100_ptr->interface_flag.program_blink_counter<1.f*MODULE_RC5_LED_BLINK_PERIOD)
		HAL_GPIO_WritePin(USER_LED_YELLOW_GPIO_Port, USER_LED_YELLOW_Pin, GPIO_PIN_RESET);
	else if(sneak100_ptr->interface_flag.program_blink_counter<1.5f*MODULE_RC5_LED_BLINK_PERIOD)
		HAL_GPIO_WritePin(USER_LED_YELLOW_GPIO_Port, USER_LED_YELLOW_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(USER_LED_YELLOW_GPIO_Port, USER_LED_YELLOW_Pin, GPIO_PIN_RESET);
}

void Core_Run_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// execute fight algorithm
	// according to settings

	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LF], 1);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LB], 1);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RF], 1);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RB], 1);
}

void Core_Stop_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// stop motors

	Motor_SetControlMode(&sneak100_ptr->motors[MOTOR_LF], MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);
	Motor_SetControlMode(&sneak100_ptr->motors[MOTOR_LB], MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);
	Motor_SetControlMode(&sneak100_ptr->motors[MOTOR_RF], MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);
	Motor_SetControlMode(&sneak100_ptr->motors[MOTOR_RB], MOTOR_CONTROL_MODE_OPEN_LOOP_POWER);

	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LF], 0);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LB], 0);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RF], 0);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RB], 0);
}

// exit


