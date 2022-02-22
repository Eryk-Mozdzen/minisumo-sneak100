/*
 * gui_states.c
 *
 *  Created on: Feb 21, 2022
 *      Author: emozdzen
 */

#include "gui_states.h"

static const char *mode[] = {"module", "button"};
static const char *dyhlo[] = {"black", "white", "auto"};
static const char *strategy[] = {"agressive", "defense", "passive"};
static const char *core_states[] = {"idle", "ready", "program", "run", "stop"};
static const char *bluetooth_status[] = {"waiting", "paired", "error"};
static const char *padding = "                                               ";

static void GUI_DrawHeader(Sneak100_GUI_t *, const char *);
static void GUI_DrawFooter(Sneak100_GUI_t *, const char *, const char *, const char *);

void GUI_DrawHeader(Sneak100_GUI_t *gui_ptr, const char *title) {
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 0, "%s       ", title);

	const char *core_state = core_states[gui_ptr->sneak100_ptr->state.core_curr_state];
	uint8_t pad_len = 7 - strlen(core_state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 78, 0, "%*.*s%s", pad_len, pad_len, padding, core_state);

	Display_DrawLine(&gui_ptr->sneak100_ptr->display, 0, 10, 127, 10);
}

void GUI_DrawFooter(Sneak100_GUI_t *gui_ptr, const char *action_l, const char *action_c, const char *action_r) {
	char bot_bar[32] = {0};

	sprintf(bot_bar, "%.4s              ", action_l);
	sprintf(bot_bar + 7, "%.5s       ", action_c);
	sprintf(bot_bar + 14, "%.4s", action_r);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 53, "%s", bot_bar);
	Display_DrawLine(&gui_ptr->sneak100_ptr->display, 0, 52, 127, 52);
}

void GUI_Fight_Enter(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	gui_ptr->sneak100_ptr->interface_flag.program_select = 1;
}

void GUI_Render_Menu(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_0 + 2, "view");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_1 + 2, "settings");
	//Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_2 + 2, "test");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_0,  GUI_MENU_ROW_3 + 2, "fight");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_0 + 2, "    ");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_1 + 2, "    ");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_2 + 2, "info");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, GUI_MENU_COL_1,  GUI_MENU_ROW_3 + 2, "credits");

	GUI_DrawFooter(gui_ptr, "up", "down", "sel");

	Display_InvertColors(&gui_ptr->sneak100_ptr->display, (gui_ptr->menu_selected<4) ? GUI_MENU_COL_0 : GUI_MENU_COL_1, (gui_ptr->menu_selected%4)*13, 64, 13);

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed)
		gui_ptr->menu_selected--;
	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	gui_ptr->menu_selected %=8;

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_ViewMotors(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Motors");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "LF:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_2, "LB:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_3, "RF:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_4, "RB:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].position);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  DISPLAY_LINE_1, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  DISPLAY_LINE_2, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  DISPLAY_LINE_3, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  DISPLAY_LINE_4, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].velocity);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  DISPLAY_LINE_1, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  DISPLAY_LINE_2, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  DISPLAY_LINE_3, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  DISPLAY_LINE_4, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].power);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_ViewLine(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Line");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->sneak100_ptr->state.line[0].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_2, "LM: %u", gui_ptr->sneak100_ptr->state.line[1].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_3, "RM: %u", gui_ptr->sneak100_ptr->state.line[2].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->sneak100_ptr->state.line[3].value);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  DISPLAY_LINE_1, "%u %c %u", gui_ptr->sneak100_ptr->state.line[0].threshold, gui_ptr->sneak100_ptr->state.line[0].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[0].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  DISPLAY_LINE_2, "%u %c %u", gui_ptr->sneak100_ptr->state.line[1].threshold, gui_ptr->sneak100_ptr->state.line[1].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[1].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  DISPLAY_LINE_3, "%u %c %u", gui_ptr->sneak100_ptr->state.line[2].threshold, gui_ptr->sneak100_ptr->state.line[2].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[2].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  DISPLAY_LINE_4, "%u %c %u", gui_ptr->sneak100_ptr->state.line[3].threshold, gui_ptr->sneak100_ptr->state.line[3].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[3].state);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_ViewProximity(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Proximity");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "LL: %u", gui_ptr->sneak100_ptr->state.proximity[0]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_2, "FL: %u", gui_ptr->sneak100_ptr->state.proximity[1]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_3, "FR: %u", gui_ptr->sneak100_ptr->state.proximity[2]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_4, "RR: %u", gui_ptr->sneak100_ptr->state.proximity[3]);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_ViewOthers(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Others");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "Temp: %.0f*C", gui_ptr->sneak100_ptr->state.temperature);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_2, "Batt: %.2fV", gui_ptr->sneak100_ptr->state.battery);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_3, "RC5:  %u 0x%02X 0x%02X",
			gui_ptr->sneak100_ptr->state.rc5.message.toggle, gui_ptr->sneak100_ptr->state.rc5.message.address, gui_ptr->sneak100_ptr->state.rc5.message.command);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_4, "BT:   %s", bluetooth_status[gui_ptr->sneak100_ptr->state.bluetooth]);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_Settings(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Settings");
	GUI_DrawFooter(gui_ptr, "opt", "down", "save");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "mode : %s", mode[gui_ptr->sneak100_ptr->settings.mode]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_2, "dyhlo: %s", dyhlo[gui_ptr->sneak100_ptr->settings.dyhlo_color]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_3, "strat: %s", strategy[gui_ptr->sneak100_ptr->settings.strategy]);

	Display_InvertColors(&gui_ptr->sneak100_ptr->display, 0, DISPLAY_LINE_1 + (DISPLAY_LINE_2 - DISPLAY_LINE_1)*gui_ptr->menu_selected - 1, 128, DISPLAY_LINE_2 - DISPLAY_LINE_1 + 1);

	if(gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed)
		gui_ptr->menu_selected++;

	if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==0) {
		gui_ptr->sneak100_ptr->settings.mode++;
		gui_ptr->sneak100_ptr->settings.mode %=SETTINGS_MODE_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==1) {
		gui_ptr->sneak100_ptr->settings.dyhlo_color++;
		gui_ptr->sneak100_ptr->settings.dyhlo_color %=SETTINGS_DYHLO_NUM;
	} else if(gui_ptr->buttons[BUTTON_L].pressed && gui_ptr->buttons[BUTTON_L].changed && gui_ptr->menu_selected==2) {
		gui_ptr->sneak100_ptr->settings.strategy++;
		gui_ptr->sneak100_ptr->settings.strategy %=SETTINGS_STRATEGY_NUM;
	}

	gui_ptr->menu_selected %=3;

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_Fight(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Fight");

	if(gui_ptr->sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON) {
		if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_READY) {


			GUI_DrawFooter(gui_ptr, "", "start", "esc");

		} else if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_RUN)
			GUI_DrawFooter(gui_ptr, "", "stop", "esc");
		else
			GUI_DrawFooter(gui_ptr, "", "", "esc");;
	} else
		GUI_DrawFooter(gui_ptr, "", "", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, DISPLAY_LINE_1, "Save:     %s", core_states[gui_ptr->sneak100_ptr->fight_data.core_save_state]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, DISPLAY_LINE_2, "dyhlo ID: 0x%02X", gui_ptr->sneak100_ptr->fight_data.dyhlo_id>>1);

	if(gui_ptr->sneak100_ptr->settings.mode==SETTINGS_MODE_BUTTON && gui_ptr->buttons[BUTTON_C].pressed && gui_ptr->buttons[BUTTON_C].changed) {
		if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_READY) {

			gui_ptr->sneak100_ptr->interface_flag.ready_button_start_click_time = HAL_GetTick();



			//gui_ptr->sneak100_ptr->interface_flag.button_start = 1;

		} else if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_RUN) {
			gui_ptr->sneak100_ptr->interface_flag.button_stop = 1;
		}
	}

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_Info(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Info");
	GUI_DrawFooter(gui_ptr, "", "", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  DISPLAY_LINE_1, "build: %s", __DATE__);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void GUI_Render_Credits(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	Display_DrawBitmap(&gui_ptr->sneak100_ptr->display, 0, 0, bitmap_sneak100_128_64, 128, 64);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 0, "Minisumo Sneak100");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 53, "by E.Mozdzen 2022");

	Display_Update(&gui_ptr->sneak100_ptr->display);
}
