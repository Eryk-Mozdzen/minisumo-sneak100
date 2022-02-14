/*
 * sneak100_display_utilities.h
 *
 *  Created on: Feb 13, 2022
 *      Author: emozdzen
 */

#ifndef INC_GUI_EVENTS_H_
#define INC_GUI_EVENTS_H_

#include <stdint.h>

typedef enum {
	BUTTON_L,
	BUTTON_C,
	BUTTON_R
} GUI_Button_EnumTypeDef;

typedef struct {
	uint8_t pressed;
	uint8_t changed;
} GUI_ButtonState_StructTypeDef;

uint8_t __Button_L_ClickEvent(void *);
uint8_t __Button_C_ClickEvent(void *);
uint8_t __Button_R_ClickEvent(void *);

uint8_t __GUI_Menu_Option0_SelectEvent(void *);
uint8_t __GUI_Menu_Option1_SelectEvent(void *);
uint8_t __GUI_Menu_Option2_SelectEvent(void *);
uint8_t __GUI_Menu_Option3_SelectEvent(void *);
uint8_t __GUI_Menu_Option4_SelectEvent(void *);
uint8_t __GUI_Menu_Option5_SelectEvent(void *);
uint8_t __GUI_Menu_Option6_SelectEvent(void *);
uint8_t __GUI_Menu_Option7_SelectEvent(void *);
uint8_t __GUI_Menu_Option8_SelectEvent(void *);
uint8_t __GUI_Menu_Option9_SelectEvent(void *);

#endif
