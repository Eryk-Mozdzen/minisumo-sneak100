/*
 * sneak100_display_utilities.h
 *
 *  Created on: Feb 13, 2022
 *      Author: emozdzen
 */

#ifndef INC_GUI_EVENTS_H_
#define INC_GUI_EVENTS_H_

#include <stdint.h>

#include "gui_def.h"

uint8_t __Button_L_ClickEvent(void *);
uint8_t __Button_C_ClickEvent(void *);
uint8_t __Button_R_ClickEvent(void *);

uint8_t __GUI_Menu_Option0_SelectEvent(void *);
uint8_t __GUI_Menu_Option1_SelectEvent(void *);
uint8_t __GUI_Menu_Option2_SelectEvent(void *);
uint8_t __GUI_Menu_Option3_SelectEvent(void *);
uint8_t __GUI_Menu_Option4_SelectEvent(void *);
uint8_t __GUI_Menu_Option5_SelectEvent(void *);

#endif
