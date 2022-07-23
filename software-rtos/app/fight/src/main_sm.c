#include "main_sm.h"

static rc5_message_t rc5_msg;
static FiniteStateMachine_t fsm;

static void loop(void *param) {
	(void)param;

	while(1) {
		if(rc5_get_message(&rc5_msg)) {

		}

		FiniteStateMachine_Update(&fsm);
		FiniteStateMachine_Execute(&fsm);

		vTaskDelay(100);
	}
}

void main_sm_init() {

	FiniteStateMachine_Init(&fsm, NULL);

	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_READY,		NULL, NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_PROGRAM,	NULL, NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_RUN,		NULL, NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, ROBOT_STATE_STOP,		NULL, NULL, NULL);

	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_READY,	ROBOT_STATE_PROGRAM,	0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_PROGRAM,	ROBOT_STATE_READY,		0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_READY,	ROBOT_STATE_RUN,		0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_RUN,		ROBOT_STATE_PROGRAM,	0, NULL, NULL);
	FiniteStateMachine_DefineTransition(&fsm, ROBOT_STATE_RUN,		ROBOT_STATE_STOP,		0, NULL, NULL);

	// read saved state from eeprom
	FiniteStateMachine_Start(&fsm, ROBOT_STATE_READY);

	xTaskCreate(loop, "main sm loop", 256, NULL, 4, NULL);
}