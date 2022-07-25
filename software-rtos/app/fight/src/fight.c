#include "fight.h"

static FiniteStateMachine_t fsm;

static uint8_t prox[4] = {0};
static uint8_t line[4] = {0};
static uint8_t last_prox[4] = {0};
static uint8_t last_line[4] = {0};

static uint32_t curr_time = 0;
static uint32_t follow_start_time = 0;

static struct {
	uint8_t follow_direction : 1;		// 0 = left, 1 = right
	uint8_t turn_complete : 1;
	uint8_t unused : 6;
} flags = {0};

static struct {
	uint8_t line_internal_spotted : 1;
	uint8_t line_external_spotted : 1;
	uint8_t unused : 6;
} events = {0};

uint8_t get_enemy_spotted(void *buffer) {
	(void)buffer;
	return (prox[0] || prox[1] || prox[2] || prox[3]);
}

uint8_t get_enemy_lost(void *buffer) {
	(void)buffer;
	return !(prox[0] || prox[1] || prox[2] || prox[3]);
}

uint8_t get_timeout(void *buffer) {
	(void)buffer;
	return ((curr_time - follow_start_time)>=FOLLOW_TIMEOUT);
}

uint8_t get_line_spotted(void *buffer) {
	(void)buffer;
	return (line[0] || line[1] || line[2] || line[3]);
}

uint8_t get_turn_complete(void *buffer) {
	(void)buffer;
	return flags.turn_complete;
}

void follow_enter(void *buffer) {
	(void)buffer;

	follow_start_time = xTaskGetTickCount();
}

void follow_execute(void *buffer) {
	(void)buffer;

	float vel[4] = {0};

	if(flags.follow_direction) {
		vel[0] = MOTOR_MAX_VEL;
		vel[1] = 0.f;
		vel[2] = 0.f;
		vel[3] = MOTOR_MAX_VEL;
	} else {
		vel[0] = 0.f;
		vel[1] = MOTOR_MAX_VEL;
		vel[2] = MOTOR_MAX_VEL;
		vel[3] = 0.f;
	}
	
	motors_set_velocity(vel);
}

void fight_execute(void *buffer) {
	(void)buffer;

	float vel[4] = {0};
	
	motors_set_velocity(vel);
}

void explore_enter(void *buffer) {
	(void)buffer;

	float vel[4] = {0};

	vel[0] = EXPLORE_VEL;
	vel[1] = EXPLORE_VEL;
	vel[2] = EXPLORE_VEL;
	vel[3] = EXPLORE_VEL;
	
	motors_set_velocity(vel);
}

void turn_enter(void *buffer) {
	(void)buffer;
}

void turn_execute(void *buffer) {
	(void)buffer;
}

void fight_init() {
	FiniteStateMachine_Init(&fsm, NULL);

	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_FOLLOW,	follow_enter,	follow_execute,		NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_FIGHT,		NULL,			fight_execute,		NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_EXPLORE,	explore_enter,	NULL,				NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_TURN,		turn_enter,		turn_execute,		NULL);

	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FOLLOW,	FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FIGHT,	FIGHT_STATE_FOLLOW,		0, NULL, get_enemy_lost);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FOLLOW,	FIGHT_STATE_EXPLORE,	0, NULL, get_timeout);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_EXPLORE,	FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_EXPLORE,	FIGHT_STATE_TURN,		0, NULL, get_line_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_TURN,		FIGHT_STATE_EXPLORE,	0, NULL, get_turn_complete);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_TURN,		FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);

	FiniteStateMachine_Start(&fsm, FIGHT_STATE_FOLLOW);
}

void fight_update() {

	curr_time = xTaskGetTickCount();
	proximity_get_state(prox);
	line_get_state(line);

	if(prox[0] || prox[1])
		flags.follow_direction = 0;
	else if(prox[2] || prox[3])
		flags.follow_direction = 1;

	if((line[0] || line[3]) && (!last_line[0] && !last_line[3]))
		events.line_external_spotted = 1;

	if((line[1] || line[2]) && (!last_line[1] && !last_line[2]))
		events.line_internal_spotted = 1;

	FiniteStateMachine_Update(&fsm);
	FiniteStateMachine_Execute(&fsm);

	memset(&events, 0, sizeof(events));
	memcpy(last_prox, prox, 4*sizeof(uint8_t));
	memcpy(last_line, line, 4*sizeof(uint8_t));

	#ifdef FIGHT_DEBUG
		fight_state_t state = fight_get_state();
		char b[32] = {0};
		switch(state) {
			case FIGHT_STATE_FOLLOW: snprintf(b, 32, "follow %u\n", flags.follow_direction); break;
			case FIGHT_STATE_FIGHT: snprintf(b, 32, "fight\n"); break;
			case FIGHT_STATE_EXPLORE: snprintf(b, 32, "explore\n"); break;
			case FIGHT_STATE_TURN: snprintf(b, 32, "turn\n"); break;
		}
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

fight_state_t fight_get_state() {
	return fsm.states[fsm.curr_state_index].id;
}