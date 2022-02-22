/*
 * core_events.c
 *
 *  Created on: Feb 20, 2022
 *      Author: emozdzen
 */

#include "core_events.h"

uint8_t __Core_Program_SelectEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	return sneak100_ptr->interface_flag.program_select;
}

uint8_t __Core_Program_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON)
		return 0;

	RC5_Message_t msg = sneak100_ptr->state.rc5.message;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	return (msg.address==MODULE_RC5_ADD_PROGRAM);
}

uint8_t __Core_ProgramEnd_Event(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON)
		return 0;

	return sneak100_ptr->interface_flag.program_blink_counter>=2*MODULE_RC5_LED_BLINK_PERIOD;
}

uint8_t __Core_Start_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON) {
		if(!sneak100_ptr->interface_flag.button_start)
			return 0;

		uint32_t time = HAL_GetTick() - sneak100_ptr->interface_flag.ready_button_start_click_time;

		return (time>=BUTTON_START_WAIT_TIME);
	}

	RC5_Message_t msg = sneak100_ptr->state.rc5.message;
	uint8_t dyhlo_id = sneak100_ptr->fight_data.dyhlo_id;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	if(msg.address!=MODULE_RC5_ADD_START_STOP)
		return 0;

	if((MODULE_RC5_CMD_MASK_DYHLO & msg.command)!=dyhlo_id)
		return 0;

	return (MODULE_RC5_CMD_MASK_START_STOP & msg.command);
}

uint8_t __Core_Stop_SignalEvent(void *data) {
	Sneak100_t *sneak100_ptr = (Sneak100_t *)data;

	if(sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON)
		return sneak100_ptr->interface_flag.button_stop;

	RC5_Message_t msg = sneak100_ptr->state.rc5.message;
	uint8_t dyhlo_id = sneak100_ptr->fight_data.dyhlo_id;

	if(sneak100_ptr->state.rc5.expired)
		return 0;

	if(msg.address!=MODULE_RC5_ADD_START_STOP)
		return 0;

	if((MODULE_RC5_CMD_MASK_DYHLO & msg.command)!=dyhlo_id)
		return 0;

	return !(MODULE_RC5_CMD_MASK_START_STOP & msg.command);
}

