/*
 * sneak100_display_utilities.c
 *
 *  Created on: Jan 27, 2022
 *      Author: emozdzen
 */

#include "gui_events.h"

uint8_t __GUI_ButtonL_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_L]);
}

uint8_t __GUI_ButtonC_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_C]);
}

uint8_t __GUI_ButtonR_Click_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]);
}

uint8_t __GUI_MenuOption0_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==0);
}

uint8_t __GUI_MenuOption1_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==1);
}

uint8_t __GUI_MenuOption2_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==2);
}

uint8_t __GUI_MenuOption3_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==3);
}

uint8_t __GUI_MenuOption4_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==4);
}

uint8_t __GUI_MenuOption5_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==5);
}

uint8_t __GUI_MenuOption6_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==6);
}

uint8_t __GUI_MenuOption7_Select_Event(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	return (Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_R]) && gui_ptr->menu_selected==7);
}
