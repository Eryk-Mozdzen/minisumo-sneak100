/*
 * fight_events.c
 *
 *  Created on: Mar 22, 2022
 *      Author: emozdzen
 */

#include "fight_events.h"

uint8_t __Fight_Line_DetectEvent(void *data) {
	Sneak100_Core_t *core_ptr = (Sneak100_Core_t *)data;

	return (
		/*core_ptr->state.line[LINE_LL].state ||*/
		core_ptr->state.line[LINE_LM].state ||
		core_ptr->state.line[LINE_RM].state ||
		core_ptr->state.line[LINE_RR].state
	);
}

uint8_t __Fight_TurnEnd_Event(void *data) {
	return 0;
}
