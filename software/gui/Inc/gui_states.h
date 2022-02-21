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
//#include "sprites.h"

void GUI_Render_Menu(void *);
void GUI_Render_ViewMotors(void *);
void GUI_Render_ViewLine(void *);
void GUI_Render_ViewProximity(void *);
void GUI_Render_ViewOthers(void *);
void GUI_Render_Settings(void *);
void GUI_Render_Info(void *);
void GUI_Render_Credits(void *);

#endif
