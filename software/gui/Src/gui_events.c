/*
 * sneak100_display_utilities.c
 *
 *  Created on: Jan 27, 2022
 *      Author: emozdzen
 */

#include "gui_events.h"

uint8_t __GUI_ButtonL_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed);
}

uint8_t __GUI_ButtonC_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed);
}

uint8_t __GUI_ButtonR_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed);
}

uint8_t __GUI_MenuOption0_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==0);
}

uint8_t __GUI_MenuOption1_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==1);
}

uint8_t __GUI_MenuOption2_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==2);
}

uint8_t __GUI_MenuOption3_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==3);
}

uint8_t __GUI_MenuOption4_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==4);
}

uint8_t __GUI_MenuOption5_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==5);
}
