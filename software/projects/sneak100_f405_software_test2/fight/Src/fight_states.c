/*
 * fight_states.c
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#include "fight_states.h"

/*	Enter	*/

void Fight_Start_Enter(void *data) {

}

void Fight_Explore_Enter(void *data) {

}

void Fight_Turn_Enter(void *data) {

}

/*	Execute	*/

void Fight_Start_Execute(void *data) {

}

void Fight_Explore_Execute(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF], 4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB], 4.f);
}

void Fight_Turn_Execute(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	Motor_SetVelocity(&core_ptr->motors[MOTOR_LF], -4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_LB], -4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RF], 4.f);
	Motor_SetVelocity(&core_ptr->motors[MOTOR_RB], 4.f);
}
