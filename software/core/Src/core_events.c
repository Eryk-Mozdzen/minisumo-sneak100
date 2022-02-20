/*
 * core_events.c
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#include "core_events.h"

uint8_t __Core_Program_SelectEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	return sneak100_ptr->program_select_flag;
}

uint8_t __Core_Program_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->settings.mode!=SETTINGS_MODE_MODULE)
		return 0;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	RC5_Message_t msg = sneak100_ptr->state.rc5.message;

	if(msg.address==MODULE_RC5_COMMAND_PROGRAM)
		return 1;

	return 0;
}

uint8_t __Core_Start_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	return 0;
}

uint8_t __Core_Stop_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	return 0;
}

