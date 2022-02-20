/*
 * core_states.c
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#include "core_states.h"

void Core_Idle_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// do nothing
}

void Core_Ready_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// do nothing
}

void Core_Program_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// save RC5 programming data
	// blink yellow led two times
}

void Core_Run_Execute(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	// execute fight algorithm
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
