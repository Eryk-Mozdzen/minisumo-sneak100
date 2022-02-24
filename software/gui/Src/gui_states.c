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
static const char *menu[] = {"view", "settings", "fight", "", "", "", "info", "credits"};
static const char *settings[] = {"mode", "dyhlo", "strat"};
static const char *padding = "                                               ";

static void GUI_DrawHeader(Sneak100_GUI_t *, const char *);
static void GUI_DrawFooter(Sneak100_GUI_t *, const char *, const char *, const char *);
static void GUI_WriteSettings(Sneak100_GUI_t *, Core_Settings_t);

void GUI_DrawHeader(Sneak100_GUI_t *gui_ptr, const char *title) {
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 0, "%s       ", title);

	const char *core_state = core_states[gui_ptr->sneak100_ptr->state.core_curr_state];
	uint8_t pad_len = 7 - strlen(core_state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 78, 0, "%*.*s%s", pad_len, pad_len, padding, core_state);

	Display_DrawLine(&gui_ptr->sneak100_ptr->display, 0, 10, 127, 10);
}

void GUI_DrawFooter(Sneak100_GUI_t *gui_ptr, const char *action_l, const char *action_c, const char *action_r) {

	// right
	uint8_t pad_len_r = 18 - strlen(action_r);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 54, "%*.*s%s", pad_len_r, pad_len_r, padding, action_r);

	// center
	uint8_t pad_len_c = (18 - strlen(action_c))/2;
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 54, "%*.*s%s", pad_len_c, pad_len_c, padding, action_c);

	// left
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 54, "%s", action_l);

	Display_DrawLine(&gui_ptr->sneak100_ptr->display, 0, 53, 127, 53);
}

void GUI_WriteSettings(Sneak100_GUI_t *gui_ptr, Core_Settings_t settings) {
	gui_ptr->sneak100_ptr->settings = settings;

	Memory_Write(&gui_ptr->sneak100_ptr->memory, MEMORY_SETTINGS_ADDRESS, &gui_ptr->sneak100_ptr->settings, sizeof(Core_Settings_t));
}

void __GUI_Fight_Enter(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	gui_ptr->sneak100_ptr->interface_flag.program_select = 1;
}

void __GUI_Menu_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Menu");
	GUI_DrawFooter(gui_ptr, "up", "down", "sel");

	uint8_t block_x[] = {0, 64};
	uint8_t block_y[] = {GUI_CONTENT_LINE_1, GUI_CONTENT_LINE_2, GUI_CONTENT_LINE_3, GUI_CONTENT_LINE_4};

	for(uint8_t i=0; i<8; i++) {
		if(i==gui_ptr->menu_selected)
			Display_SetColor(&gui_ptr->sneak100_ptr->display, Black);

		Display_DrawText(&gui_ptr->sneak100_ptr->display, block_x[i/4], block_y[i%4], "%-10s", menu[i]);
		Display_SetColor(&gui_ptr->sneak100_ptr->display, White);
	}

	if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_L]))
		gui_ptr->menu_selected +=7;
	if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_C]))
		gui_ptr->menu_selected++;

	gui_ptr->menu_selected %=8;

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Motors_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Motors");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_1, "LF:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_2, "LB:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_3, "RF:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].position);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_4, "RB:%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].position);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  GUI_CONTENT_LINE_1, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  GUI_CONTENT_LINE_2, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  GUI_CONTENT_LINE_3, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].velocity);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 56,  GUI_CONTENT_LINE_4, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].velocity);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  GUI_CONTENT_LINE_1, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LF].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  GUI_CONTENT_LINE_2, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_LB].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  GUI_CONTENT_LINE_3, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RF].power);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 92,  GUI_CONTENT_LINE_4, "%+.2f", gui_ptr->sneak100_ptr->state.motor[MOTOR_RB].power);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Line_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Line");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_1, "LL: %u", gui_ptr->sneak100_ptr->state.line[0].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_2, "LM: %u", gui_ptr->sneak100_ptr->state.line[1].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_3, "RM: %u", gui_ptr->sneak100_ptr->state.line[2].value);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_4, "RR: %u", gui_ptr->sneak100_ptr->state.line[3].value);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  GUI_CONTENT_LINE_1, "%u %c %u", gui_ptr->sneak100_ptr->state.line[0].threshold, gui_ptr->sneak100_ptr->state.line[0].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[0].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  GUI_CONTENT_LINE_2, "%u %c %u", gui_ptr->sneak100_ptr->state.line[1].threshold, gui_ptr->sneak100_ptr->state.line[1].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[1].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  GUI_CONTENT_LINE_3, "%u %c %u", gui_ptr->sneak100_ptr->state.line[2].threshold, gui_ptr->sneak100_ptr->state.line[2].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[2].state);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 64,  GUI_CONTENT_LINE_4, "%u %c %u", gui_ptr->sneak100_ptr->state.line[3].threshold, gui_ptr->sneak100_ptr->state.line[3].polarity ? 'W' : 'B', gui_ptr->sneak100_ptr->state.line[3].state);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Proximity_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Proximity");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_1, "LL: %u", gui_ptr->sneak100_ptr->state.proximity[0]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_2, "FL: %u", gui_ptr->sneak100_ptr->state.proximity[1]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_3, "FR: %u", gui_ptr->sneak100_ptr->state.proximity[2]);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_4, "RR: %u", gui_ptr->sneak100_ptr->state.proximity[3]);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Others_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Others");
	GUI_DrawFooter(gui_ptr, "next", "prev", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_1, "Temp: %.0f*C", gui_ptr->sneak100_ptr->state.temperature);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_2, "Batt: %.2fV", gui_ptr->sneak100_ptr->state.battery);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_3, "RC5:  %u 0x%02X 0x%02X",
			gui_ptr->sneak100_ptr->state.rc5.message.toggle, gui_ptr->sneak100_ptr->state.rc5.message.address, gui_ptr->sneak100_ptr->state.rc5.message.command);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_4, "BT:   %s", bluetooth_status[gui_ptr->sneak100_ptr->state.bluetooth]);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Settings_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Settings");
	GUI_DrawFooter(gui_ptr, "opt", "down", "save");

	gui_ptr->menu_selected %=3;

	uint8_t block_y[] = {GUI_CONTENT_LINE_1, GUI_CONTENT_LINE_2, GUI_CONTENT_LINE_3};
	const char *curr_sett[] = {
		mode[gui_ptr->sneak100_ptr->settings.mode],
		dyhlo[gui_ptr->sneak100_ptr->settings.dyhlo_color],
		strategy[gui_ptr->sneak100_ptr->settings.strategy]
	};

	for(uint8_t i=0; i<3; i++) {
		if(i==gui_ptr->menu_selected)
			Display_SetColor(&gui_ptr->sneak100_ptr->display, Black);

		Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, block_y[i], "%-5s: %-20s", settings[i], curr_sett[i]);
		Display_SetColor(&gui_ptr->sneak100_ptr->display, White);
	}

	if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_C])) {
		gui_ptr->menu_selected++;
		gui_ptr->menu_selected %=3;
	}

	if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_L]) && gui_ptr->menu_selected==0) {
		gui_ptr->sneak100_ptr->settings.mode++;
		gui_ptr->sneak100_ptr->settings.mode %=SETTINGS_MODE_NUM;
	} else if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_L]) && gui_ptr->menu_selected==1) {
		gui_ptr->sneak100_ptr->settings.dyhlo_color++;
		gui_ptr->sneak100_ptr->settings.dyhlo_color %=SETTINGS_DYHLO_NUM;
	} else if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_L]) && gui_ptr->menu_selected==2) {
		gui_ptr->sneak100_ptr->settings.strategy++;
		gui_ptr->sneak100_ptr->settings.strategy %=SETTINGS_STRATEGY_NUM;
	}

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Fight_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	if(gui_ptr->sneak100_ptr->settings.mode==SETTINGS_MODE_MODULE) {
		Display_Clear(&gui_ptr->sneak100_ptr->display);

		GUI_DrawHeader(gui_ptr, "Fight");
		GUI_DrawFooter(gui_ptr, "", "", "esc");

		Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, GUI_CONTENT_LINE_1, "Save:     %s", core_states[gui_ptr->sneak100_ptr->fight_data.core_save_state]);
		Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, GUI_CONTENT_LINE_2, "dyhlo ID: 0x%02X", gui_ptr->sneak100_ptr->fight_data.dyhlo_id>>1);

		Display_Update(&gui_ptr->sneak100_ptr->display);
		return;
	}

	char button_c[8] = {0};

	if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_READY) {

		if(!gui_ptr->sneak100_ptr->interface_flag.button_start)
			sprintf(button_c, "start");
		else {
			int64_t time = (int64_t)gui_ptr->sneak100_ptr->interface_flag.start_time - (int64_t)HAL_GetTick();
			float time_f = (float)time/1000.f;
			if(time_f<0.f)
				time_f = 0.f;

			sprintf(button_c, "%.2f", time_f);
		}

	} else if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_RUN)
		sprintf(button_c, "stop");

	if(Button_IsClicked(&gui_ptr->sneak100_ptr->buttons[BUTTON_C])) {
		if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_READY)
			gui_ptr->sneak100_ptr->interface_flag.button_start = 1;
		else if(gui_ptr->sneak100_ptr->state.core_curr_state==CORE_STATE_RUN)
			gui_ptr->sneak100_ptr->interface_flag.button_stop = 1;
	}

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Fight");
	GUI_DrawFooter(gui_ptr, "", button_c, "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, GUI_CONTENT_LINE_1, "Save:     %s", core_states[gui_ptr->sneak100_ptr->fight_data.core_save_state]);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Info_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	GUI_DrawHeader(gui_ptr, "Info");
	GUI_DrawFooter(gui_ptr, "", "", "esc");

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_1, "build: %s", CORE_BUILD_DATE);
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0,  GUI_CONTENT_LINE_2, "       %s", CORE_BUILD_TIME);

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Credits_Execute(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	Display_Clear(&gui_ptr->sneak100_ptr->display);

	Display_DrawBitmap(&gui_ptr->sneak100_ptr->display, 0, 0, bitmap_sneak100_128_64, 128, 64);

	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 0, "Minisumo Sneak100");
	Display_DrawText(&gui_ptr->sneak100_ptr->display, 0, 53, "by E.Mozdzen 2022");

	Display_Update(&gui_ptr->sneak100_ptr->display);
}

void __GUI_Settings_Exit(void *data) {
	Sneak100_GUI_t *gui_ptr = (Sneak100_GUI_t *)data;

	GUI_WriteSettings(gui_ptr, gui_ptr->sneak100_ptr->settings);
}
