#include "gui.h"

static FiniteStateMachine_t fsm;
static uint8_t button_last[3] = {0};

static void update(void *param) {
	(void)param;

	display_init();

	FiniteStateMachine_Start(&fsm, GUI_STATE_MENU);

	while(1) {

		FiniteStateMachine_Execute(&fsm);
		FiniteStateMachine_Update(&fsm);

		vTaskDelay(1000/GUI_UPDATE_FREQ);
	}
}

static uint8_t button_l_click(void *buffer) {
	(void)buffer;
	const uint8_t curr = !(GPIOC->IDR & GPIO_IDR_ID12);
	const uint8_t prev = button_last[0];
	button_last[0] = curr;
	return (curr!=prev && curr);
}

static uint8_t button_c_click(void *buffer) {
	(void)buffer;
	const uint8_t curr = !(GPIOC->IDR & GPIO_IDR_ID11);
	const uint8_t prev = button_last[1];
	button_last[1] = curr;
	return (curr!=prev && curr);
}

static uint8_t button_r_click(void *buffer) {
	(void)buffer;
	const uint8_t curr = !(GPIOC->IDR & GPIO_IDR_ID10);
	const uint8_t prev = button_last[2];
	button_last[2] = curr;
	return (curr!=prev && curr);
}

static void menu_enter(void *buffer) {
	(void)buffer;

	display_fill(DISPLAY_COLOR_BLACK);

	display_bitmap(128/6 - 32/2, 8, DISPLAY_COLOR_WHITE, bitmap_minecraft_night_vision_32_32, 32, 32);
	display_bitmap(128/2 - 32/2, 8, DISPLAY_COLOR_WHITE, bitmap_minecraft_sword_32_32, 32, 32);
	display_bitmap(5*128/6 - 32/2, 8, DISPLAY_COLOR_WHITE, bitmap_minecraft_book_32_32, 32, 32);

	display_printf(10, 50, DISPLAY_COLOR_WHITE, display_font_6x8, "view");
	display_printf(42 + 6, 50, DISPLAY_COLOR_WHITE, display_font_6x8, "fight");
	display_printf(85 + 6, 50, DISPLAY_COLOR_WHITE, display_font_6x8, "glory");

	display_render();
}

static void menu_exit_view(void *buffer) {
	(void)buffer;

	display_inverse(0, 0, 43, 64);
	
	display_render();
	vTaskDelay(100);
}

static void menu_exit_fight(void *buffer) {
	(void)buffer;

	display_inverse(42, 0, 43, 64);

	display_render();
	vTaskDelay(100);
}

static void menu_exit_credits(void *buffer) {
	(void)buffer;

	display_inverse(86, 0, 43, 64);

	display_render();
	vTaskDelay(100);
}

static void motors_execute(void *buffer) {
	(void)buffer;

	int32_t pos[4] = {0};
	motors_get_position(pos);

	float vel[4] = {0};
	motors_get_velocity(vel);

	float pwr[4] = {0};
	motors_get_power(pwr);

	display_fill(DISPLAY_COLOR_BLACK);

	display_printf(48, 1, DISPLAY_COLOR_WHITE, display_font_6x8, "motors");
	display_inverse(0, 0, 128, 10);

	display_printf(0, 15, DISPLAY_COLOR_WHITE, display_font_6x8, "FL: %-5lu %+.2f %+4d%%", pos[0], (double)vel[0], (int16_t)(100.f*pwr[0]));
	display_printf(0, 25, DISPLAY_COLOR_WHITE, display_font_6x8, "FR: %-5lu %+.2f %+4d%%", pos[1], (double)vel[1], (int16_t)(100.f*pwr[1]));
	display_printf(0, 35, DISPLAY_COLOR_WHITE, display_font_6x8, "BR: %-5lu %+.2f %+4d%%", pos[2], (double)vel[2], (int16_t)(100.f*pwr[2]));
	display_printf(0, 45, DISPLAY_COLOR_WHITE, display_font_6x8, "BL: %-5lu %+.2f %+4d%%", pos[3], (double)vel[3], (int16_t)(100.f*pwr[3]));

	display_render();
}

static void line_execute(void *buffer) {
	(void)buffer;

	uint8_t line[4] = {0};
	line_get_state(line);

	uint16_t raw[4] = {0};
	line_get_raw(raw);

	display_fill(DISPLAY_COLOR_BLACK);

	display_printf(52, 1, DISPLAY_COLOR_WHITE, display_font_6x8, "line");
	display_inverse(0, 0, 128, 10);

	display_printf(0, 15, DISPLAY_COLOR_WHITE, display_font_6x8, "LL: %-6u %u", raw[0], line[0]);
	display_printf(0, 25, DISPLAY_COLOR_WHITE, display_font_6x8, "LM: %-6u %u", raw[1], line[1]);
	display_printf(0, 35, DISPLAY_COLOR_WHITE, display_font_6x8, "RM: %-6u %u", raw[2], line[2]);
	display_printf(0, 45, DISPLAY_COLOR_WHITE, display_font_6x8, "RR: %-6u %u", raw[3], line[3]);

	display_render();
}

static void prox_execute(void *buffer) {
	(void)buffer;

	uint8_t prox[4] = {0};
	proximity_get_state(prox);

	display_fill(DISPLAY_COLOR_BLACK);

	display_printf(40, 1, DISPLAY_COLOR_WHITE, display_font_6x8, "proximity");
	display_inverse(0, 0, 128, 10);

	display_printf(0, 15, DISPLAY_COLOR_WHITE, display_font_6x8, "LL: %u", prox[0]);
	display_printf(0, 25, DISPLAY_COLOR_WHITE, display_font_6x8, "LF: %u", prox[1]);
	display_printf(0, 35, DISPLAY_COLOR_WHITE, display_font_6x8, "RF: %u", prox[2]);
	display_printf(0, 45, DISPLAY_COLOR_WHITE, display_font_6x8, "RR: %u", prox[3]);

	display_render();
}

static void other_execute(void *buffer) {
	(void)buffer;

	const float temp = get_temperature();
	const float batt = get_voltage();

	display_fill(DISPLAY_COLOR_BLACK);

	display_printf(52, 1, DISPLAY_COLOR_WHITE, display_font_6x8, "other");
	display_inverse(0, 0, 128, 10);

	display_printf(0, 15, DISPLAY_COLOR_WHITE, display_font_6x8, "temp: %u  *C", (int8_t)temp);
	display_printf(0, 25, DISPLAY_COLOR_WHITE, display_font_6x8, "batt: %.2f V", (double)batt);
	//display_printf(0, 35, DISPLAY_COLOR_WHITE, display_font_6x8, "RC5: ");
	//display_printf(0, 45, DISPLAY_COLOR_WHITE, display_font_6x8, "");

	display_render();
}

static void robot_enter(void *buffer) {
	(void)buffer;

	display_bitmap(0, 0, DISPLAY_COLOR_WHITE, bitmap_sneak100_128_64, 128, 64);

	display_printf(12, 0, DISPLAY_COLOR_WHITE, display_font_6x8, "minisumo Sneak100");
	display_printf(18, 56, DISPLAY_COLOR_WHITE, display_font_6x8, "by Eryk Mozdzen");

	display_render();
}

static void konar_enter(void *buffer) {
	(void)buffer;

	display_bitmap(0, 0, DISPLAY_COLOR_WHITE, bitmap_konar_vertical_128_64, 128, 64);
	//display_bitmap(0, 0, DISPLAY_COLOR_WHITE, bitmap_konar_horizontal_128_64, 128, 64);

	display_render();
}

void gui_init() {

	// button R -> PC10
	// button C -> PC11
	// button L -> PC12
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &=~((3<<GPIO_MODER_MODE10_Pos) | (3<<GPIO_MODER_MODE11_Pos) | (3<<GPIO_MODER_MODE12_Pos));

	FiniteStateMachine_Init(&fsm, NULL);

	FiniteStateMachine_DefineState(&fsm, GUI_STATE_MENU,	menu_enter,		NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_MOTORS,	NULL,			motors_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_LINE,	NULL,			line_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_PROX,	NULL,			prox_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_OTHER,	NULL,			other_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_FIGHT,	NULL,			NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_ROBOT,	robot_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, GUI_STATE_KONAR,	konar_enter,	NULL,			NULL);

	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MENU,	GUI_STATE_MOTORS,	0, menu_exit_view,		button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MENU,	GUI_STATE_FIGHT,	0, menu_exit_fight,		button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MENU,	GUI_STATE_ROBOT,	0, menu_exit_credits,	button_r_click);

	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MOTORS,	GUI_STATE_LINE,		0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_LINE,	GUI_STATE_PROX,		0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_PROX,	GUI_STATE_OTHER,	0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_OTHER,	GUI_STATE_MOTORS,	0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MOTORS,	GUI_STATE_OTHER,	0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_OTHER,	GUI_STATE_PROX,		0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_PROX,	GUI_STATE_LINE,		0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_LINE,	GUI_STATE_MOTORS,	0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_MOTORS,	GUI_STATE_MENU,		0, NULL, button_r_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_LINE,	GUI_STATE_MENU,		0, NULL, button_r_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_PROX,	GUI_STATE_MENU,		0, NULL, button_r_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_OTHER,	GUI_STATE_MENU,		0, NULL, button_r_click);

	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_FIGHT, 	GUI_STATE_MENU,		0, NULL, button_r_click);

	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_ROBOT, 	GUI_STATE_KONAR,	0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_KONAR, 	GUI_STATE_ROBOT,	0, NULL, button_l_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_KONAR, 	GUI_STATE_ROBOT,	0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_ROBOT, 	GUI_STATE_KONAR,	0, NULL, button_c_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_ROBOT, 	GUI_STATE_MENU,		0, NULL, button_r_click);
	FiniteStateMachine_DefineTransition(&fsm, GUI_STATE_KONAR, 	GUI_STATE_MENU,		0, NULL, button_r_click);

	xTaskCreate(update, "GUI update", 1024, NULL, 4, NULL);
}