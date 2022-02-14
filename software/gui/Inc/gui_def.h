/*
 * gui_def.h
 *
 *  Created on: Feb 14, 2022
 *      Author: emozdzen
 */

#ifndef INC_GUI_DEF_H_
#define INC_GUI_DEF_H_

typedef enum {
	GUI_STATE_MENU,

	GUI_STATE_VIEW_MOTORS,
	GUI_STATE_VIEW_LINE,
	GUI_STATE_VIEW_PROXIMITY,
	GUI_STATE_VIEW_OTHERS,

	GUI_STATE_SETTINGS,
	GUI_STATE_TEST,
	GUI_STATE_FIGHT,

	GUI_STATE_INFO,
	GUI_STATE_CREDITS
} GUI_States_t;

#endif /* INC_GUI_DEF_H_ */
