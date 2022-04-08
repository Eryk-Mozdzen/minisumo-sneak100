/*
 * core_states.c
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#include "core_states.h"

static void SaveState(Sneak100_Core_t *, Core_State_t);
static void SaveDyhloID(Sneak100_Core_t *, uint8_t);

static void SaveState(Sneak100_Core_t *sneak100, Core_State_t state) {
	sneak100->fight_data.core_save_state = state;
	Memory_Write(&sneak100->memory, MEMORY_FIGHT_DATA_ADDRESS, &sneak100->fight_data, sizeof(Core_FightData_t));
}

static void SaveDyhloID(Sneak100_Core_t *sneak100, uint8_t id) {
	sneak100->fight_data.dyhlo_id = id;
	Memory_Write(&sneak100->memory, MEMORY_FIGHT_DATA_ADDRESS, &sneak100->fight_data, sizeof(Core_Settings_t));
}

// enter

void Core_Idle_Enter(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

void Core_Ready_Enter(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

void Core_Program_Enter(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	sneak100_ptr->state.rc5.expired = 1;
	sneak100_ptr->interface_flag.program_blink_counter = 0;

	uint8_t id = MODULE_RC5_CMD_MASK_DYHLO & sneak100_ptr->state.rc5.message.command;

	SaveDyhloID(sneak100_ptr, id);
}

void Core_Run_Enter(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_RUN);

	//FiniteStateMachine_Start(&sneak100_ptr->fight_fsm, FIGHT_STATE_START);
}

void Core_Stop_Enter(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	sneak100_ptr->state.rc5.expired = 1;

	SaveState(sneak100_ptr, CORE_STATE_IDLE);
}

// execute

void Core_Idle_Execute(void *data) {
	//Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// do nothing
}

void Core_Ready_Execute(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	// do nothing

	if(!sneak100_ptr->interface_flag.button_start)
		sneak100_ptr->interface_flag.start_time = HAL_GetTick() + BUTTON_START_WAIT_TIME;
}

void Core_Program_Execute(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

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
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

	// execute fight algorithm
	// according to settings

	//FiniteStateMachine_Update(&sneak100_ptr->fight_fsm);
	//FiniteStateMachine_Execute(&sneak100_ptr->fight_fsm);

	if(!sneak100_ptr->state.proximity[PROXIMITY_LL] &&
		!sneak100_ptr->state.proximity[PROXIMITY_FL] &&
		!sneak100_ptr->state.proximity[PROXIMITY_FR] &&
		!sneak100_ptr->state.proximity[PROXIMITY_RR]) {

		const float turn_power = 0.75f;
		const float turn_sign = sneak100_ptr->fight_data.flags.last_pid_error_sign ? 1.f : -1.f;

		Motor_SetPower(&sneak100_ptr->motors[MOTOR_LF],  turn_sign*turn_power*MOTOR_LF_DIR);
		Motor_SetPower(&sneak100_ptr->motors[MOTOR_LB],  turn_sign*turn_power*MOTOR_LB_DIR);
		Motor_SetPower(&sneak100_ptr->motors[MOTOR_RF], -turn_sign*turn_power*MOTOR_RF_DIR);
		Motor_SetPower(&sneak100_ptr->motors[MOTOR_RB], -turn_sign*turn_power*MOTOR_RB_DIR);

		sneak100_ptr->fight_data.pid_error = 0.f;

		return;
	}

	float sum = 0;
	sum +=sneak100_ptr->state.proximity[PROXIMITY_LL]*(-3);
	sum +=sneak100_ptr->state.proximity[PROXIMITY_FL]*(-1);
	sum +=sneak100_ptr->state.proximity[PROXIMITY_FR]*(1);
	sum +=sneak100_ptr->state.proximity[PROXIMITY_RR]*(3);

	float number = 0;
	number +=sneak100_ptr->state.proximity[PROXIMITY_LL];
	number +=sneak100_ptr->state.proximity[PROXIMITY_FL];
	number +=sneak100_ptr->state.proximity[PROXIMITY_FR];
	number +=sneak100_ptr->state.proximity[PROXIMITY_RR];

	const float value = (float)sum/number;

	const float Kp = 0.2f;
	const float setpoint = 0.f;

	const float error = (value - setpoint);
	const float output = Kp*error;

	const float power = 0.9f;

	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LF], (power + output)*MOTOR_LF_DIR);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_LB], (power + output)*MOTOR_LB_DIR);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RF], (power - output)*MOTOR_RF_DIR);
	Motor_SetPower(&sneak100_ptr->motors[MOTOR_RB], (power - output)*MOTOR_RB_DIR);

	sneak100_ptr->fight_data.pid_error = error;
	sneak100_ptr->fight_data.flags.last_pid_error_sign = (error>0.f);

}

void Core_Stop_Execute(void *data) {
	Sneak100_Core_t *sneak100_ptr = (Sneak100_Core_t *)data;

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


