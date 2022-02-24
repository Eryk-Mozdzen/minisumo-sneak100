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

uint8_t __GUI_ButtonL_Click_Event(void *);
uint8_t __GUI_ButtonC_Click_Event(void *);
uint8_t __GUI_ButtonR_Click_Event(void *);

uint8_t __GUI_MenuOption0_Select_Event(void *);
uint8_t __GUI_MenuOption1_Select_Event(void *);
uint8_t __GUI_MenuOption2_Select_Event(void *);
uint8_t __GUI_MenuOption3_Select_Event(void *);
uint8_t __GUI_MenuOption4_Select_Event(void *);
uint8_t __GUI_MenuOption5_Select_Event(void *);
uint8_t __GUI_MenuOption6_Select_Event(void *);
uint8_t __GUI_MenuOption7_Select_Event(void *);

#endif
