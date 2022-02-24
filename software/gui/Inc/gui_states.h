/*
 * gui_states.h
 *
 *  Created on: Feb 21, 2022
 *      Author: emozdzen
 */

#ifndef INC_GUI_STATES_H_
#define INC_GUI_STATES_H_

#include "gui_def.h"
#include "gui_conf.h"
#include "core_conf.h"
#include "sprites.h"

void __GUI_Fight_Enter(void *);

void __GUI_Menu_Execute(void *);
void __GUI_Motors_Execute(void *);
void __GUI_Line_Execute(void *);
void __GUI_Proximity_Execute(void *);
void __GUI_Others_Execute(void *);
void __GUI_Settings_Execute(void *);
void __GUI_Fight_Execute(void *);
void __GUI_Info_Execute(void *);
void __GUI_Credits_Execute(void *);

void __GUI_Settings_Exit(void *);

#endif
