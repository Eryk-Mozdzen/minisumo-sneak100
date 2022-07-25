#include "robot.h"

static rc5_message_t rc5_msg;
static FiniteStateMachine_t fsm;

static struct {
	uint8_t rc5_program_cmd : 1;
	uint8_t rc5_start_cmd : 1;
	uint8_t rc5_stop_cmd : 1;
	uint8_t flash_led_state : 1;
	uint8_t unused : 4;
} flags = {0};

static struct {
	robot_state_t sm_state;
	uint16_t stop_cmd;
	uint16_t start_cmd;
} eeprom_data;

static void handle_message() {
	if(rc5_msg.address==0x0B) {
		// programming command

		flags.rc5_program_cmd = 1;

		eeprom_data.stop_cmd = rc5_msg.command & 0xFE;
		eeprom_data.start_cmd = (rc5_msg.command & 0xFE) + 1;

		eeprom_write(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));

	} else if(rc5_msg.command==eeprom_data.stop_cmd) {
		// stop command

		flags.rc5_stop_cmd = 1;

	} else if(rc5_msg.command==eeprom_data.start_cmd) {
		// start command

		flags.rc5_start_cmd = 1;

	}
}

static void loop(void *param) {
	(void)param;

	static_assert(sizeof(eeprom_data)<=EEPROM_PAGE_SIZE);
	eeprom_read(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));

	switch(eeprom_data.sm_state) {
		case ROBOT_STATE_READY:
		case ROBOT_STATE_PROGRAM:
		case ROBOT_STATE_RUN:
		case ROBOT_STATE_STOP1:
		case ROBOT_STATE_STOP2: break;
		default: eeprom_data.sm_state = ROBOT_STATE_READY; break;
	}

	FiniteStateMachine_Start(&fsm, eeprom_data.sm_state);

	while(1) {
		if(rc5_get_message(&rc5_msg)) {
			handle_message();
		}

		FiniteStateMachine_Update(&fsm);
		FiniteStateMachine_Execute(&fsm);

		flags.rc5_program_cmd = 0;
		flags.rc5_stop_cmd = 0;
		flags.rc5_start_cmd = 0;

		vTaskDelay(1000/ROBOT_LOOP_FREQ);
	}
}

static uint8_t get_program(void *buffer) {
	(void)buffer;
	return flags.rc5_program_cmd;
}

static uint8_t get_start(void *buffer) {
	(void)buffer;
	return flags.rc5_start_cmd;
}

static uint8_t get_stop(void *buffer) {
	(void)buffer;
	return flags.rc5_stop_cmd;
}

static void ready_enter(void *buffer) {
	(void)buffer;

	eeprom_data.sm_state = ROBOT_STATE_READY;
	eeprom_write(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));
}

static void program_enter(void *buffer) {
	(void)buffer;

	led_set_yellow(1);
	vTaskDelay(250);
	led_set_yellow(0);
	vTaskDelay(250);

	led_set_yellow(1);
	vTaskDelay(250);
	led_set_yellow(0);
	vTaskDelay(250);
}

static void run_enter(void *buffer) {
	(void)buffer;

	led_set_yellow(1);

	eeprom_data.sm_state = ROBOT_STATE_RUN;
	eeprom_write(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));
}

static void run_execute(void *buffer) {
	(void)buffer;

	// fight algorithm
	// fight state machine update & execute
	fight_update();
}

static void stop1_enter(void *buffer) {
	(void)buffer;

	led_set_yellow(0);

	eeprom_data.sm_state = ROBOT_STATE_STOP1;
	eeprom_write(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));

	// stop motors

	vTaskDelay(1000);
}

static void stop2_enter(void *buffer) {
	(void)buffer;

	eeprom_data.sm_state = ROBOT_STATE_READY;
	eeprom_write(ROBOT_DATA_EEPROM_PAGE, ROBOT_DATA_EEPROM_OFFSET, &eeprom_data, sizeof(eeprom_data));
}

static void stop2_execute(void *buffer) {
	(void)buffer;

	led_set_yellow(flags.flash_led_state);
	
	flags.flash_led_state = !flags.flash_led_state;

	vTaskDelay(500);
}

void robot_init() {

	FiniteStateMachine_Init(&fsm, NULL);

	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_READY,		ready_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_PROGRAM,	program_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_RUN,		run_enter,		run_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_STOP1,		stop1_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_STOP2,		stop2_enter,	stop2_execute,	NULL);

	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_READY,	ROBOT_STATE_PROGRAM,	0, NULL, get_program);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_PROGRAM,	ROBOT_STATE_READY,		0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_READY,	ROBOT_STATE_RUN,		0, NULL, get_start);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_RUN,		ROBOT_STATE_PROGRAM,	0, NULL, get_program);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_RUN,		ROBOT_STATE_STOP1,		0, NULL, get_stop);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_STOP1,	ROBOT_STATE_STOP2,		0, NULL, NULL);

	xTaskCreate(loop, "robot loop", 256, NULL, 4, NULL);

	fight_init();
}