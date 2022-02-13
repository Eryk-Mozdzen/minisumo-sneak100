/*
 * sneak100_display_utilities.c
 *
 *  Created on: Jan 27, 2022
 *      Author: emozdzen
 */

#include "sneak100_display.h"

uint8_t __Button_L_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed);
}

uint8_t __Button_C_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed);
}

uint8_t __Button_R_ClickEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed);
}

uint8_t __GUI_Menu_Option0_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==0);
}

uint8_t __GUI_Menu_Option1_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==1);
}

uint8_t __GUI_Menu_Option2_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==2);
}

uint8_t __GUI_Menu_Option3_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==3);
}

uint8_t __GUI_Menu_Option4_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==4);
}

uint8_t __GUI_Menu_Option5_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==5);
}

uint8_t __GUI_Menu_Option6_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==6);
}

uint8_t __GUI_Menu_Option7_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==7);
}

uint8_t __GUI_Menu_Option8_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==8);
}

uint8_t __GUI_Menu_Option9_SelectEvent(void *data) {
	Sneak100_GUI_StructTypeDef *gui_ptr = (Sneak100_GUI_StructTypeDef *)data;

	return (gui_ptr->buttons[BUTTON_R].pressed && gui_ptr->buttons[BUTTON_R].changed && gui_ptr->menu_selected==9);
}
