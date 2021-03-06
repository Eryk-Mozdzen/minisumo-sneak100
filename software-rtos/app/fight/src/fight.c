#include "fight.h"

static FiniteStateMachine_t fsm;
static arm_pid_instance_f32 fight_pid;

static uint8_t prox[4] = {0};
static uint8_t line[4] = {0};
static uint8_t last_prox[4] = {0};
static uint8_t last_line[4] = {0};

static uint32_t curr_time = 0;
static uint32_t follow_start_time = 0;

static int32_t pos[4] = {0};
static int32_t measurement_1[4] = {0};
static int32_t measurement_2[4] = {0};
static float angle_to_rot;
static int32_t turn_end[4] = {0};

static struct {
	uint8_t follow_direction : 1;		// 0 = left, 1 = right
	uint8_t turn_direction : 1;			// 0 = left, 1 = right
	uint8_t unused : 6;
} flags = {0};

// ------------------------------------------------------

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

uint8_t get_line_external(void *buffer) {
	(void)buffer;
	return (line[0] || line[3]);
}

uint8_t get_line_internal(void *buffer) {
	(void)buffer;
	return (line[1] || line[2]);
}

uint8_t get_turn_complete(void *buffer) {
	(void)buffer;

	// check if end wheel position is reached
	int32_t delta[4] = {0};
	delta[0] = abs(motors_get_position_delta(pos[0], turn_end[0]));
	delta[1] = abs(motors_get_position_delta(pos[1], turn_end[1]));
	delta[2] = abs(motors_get_position_delta(pos[2], turn_end[2]));
	delta[3] = abs(motors_get_position_delta(pos[3], turn_end[3]));

	return (delta[0]<=TURN_POS_EPSILON && delta[1]<=TURN_POS_EPSILON && delta[2]<=TURN_POS_EPSILON && delta[3]<=TURN_POS_EPSILON);
}

// -------------------------------------------------------

void follow_enter(void *buffer) {
	(void)buffer;

	follow_start_time = xTaskGetTickCount();

	motors_set_control_type(MOTORS_OPEN_LOOP);

	float pwr[4] = {0};

	if(flags.follow_direction) {
		pwr[0] = 1.f;
		pwr[1] = 0.f;
		pwr[2] = 0.f;
		pwr[3] = 1.f;
	} else {
		pwr[0] = 0.f;
		pwr[1] = 1.f;
		pwr[2] = 1.f;
		pwr[3] = 0.f;
	}
	
	motors_set_power(pwr);
	
	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "follow start %u\n", flags.follow_direction);
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void fight_enter(void *buffer) {
	(void)buffer;

	motors_set_control_type(MOTORS_OPEN_LOOP);

	arm_pid_reset_f32(&fight_pid);
}

void fight_execute(void *buffer) {
	(void)buffer;

	const float sensors_angle[4] = {-90.f, -30.f, 30.f, 90.f};
	float angle_to_enemy = 0.f;
	uint8_t active_sensors = 0;

	for(uint8_t i=0; i<4; i++) {
		if(prox[i]) {
			angle_to_enemy +=sensors_angle[i];
			active_sensors++;
		}
	}
	if(active_sensors)
		angle_to_enemy /=active_sensors;
	
	float pwr[4] = {0};

	const float delta = arm_pid_f32(&fight_pid, angle_to_enemy - 0.f);

	pwr[0] = FIGHT_PWR + delta;
	pwr[1] = FIGHT_PWR - delta;
	pwr[2] = FIGHT_PWR - delta;
	pwr[3] = FIGHT_PWR + delta;
	
	motors_set_power(pwr);

	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "fight %+.2f\t%+.2f\n", (double)angle_to_enemy, (double)delta);
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void explore_enter(void *buffer) {
	(void)buffer;

	motors_set_control_type(MOTORS_CLOSE_LOOP);

	float vel[4] = {0};

	vel[0] = EXPLORE_VEL;
	vel[1] = EXPLORE_VEL;
	vel[2] = EXPLORE_VEL;
	vel[3] = EXPLORE_VEL;
	
	motors_set_velocity(vel);

	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "explore start\n");
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void measure_enter(void *buffer) {
	(void)buffer;

	// 1st measurement
	memcpy(measurement_1, pos, 4*sizeof(int32_t));

	motors_set_control_type(MOTORS_CLOSE_LOOP);

	float vel[4] = {0};

	vel[0] = MEASURE_VEL;
	vel[1] = MEASURE_VEL;
	vel[2] = MEASURE_VEL;
	vel[3] = MEASURE_VEL;
	
	motors_set_velocity(vel);

	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "measure start\n");
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void measure_exit(void *buffer) {
	(void)buffer;

	// 2nd measurement
	memcpy(measurement_2, pos, 4*sizeof(int32_t));

	// calculate angle
	int32_t delta[4] = {0};
	delta[0] = -motors_get_position_delta(measurement_1[0], measurement_2[0]);
	delta[1] = motors_get_position_delta(measurement_1[1], measurement_2[1]);
	delta[2] = motors_get_position_delta(measurement_1[2], measurement_2[2]);
	delta[3] = -motors_get_position_delta(measurement_1[3], measurement_2[3]);

	const float delta_avg = (delta[0] + delta[1] + delta[2] + delta[3])/4.f;
	const float wheel_dist = (delta_avg/((float)MOTORS_ENCODER_CPR))*MOTORS_WHEEL_READIUS*2.f*PI;
	const float sensor_dist = flags.turn_direction ? 0.023f : 0.064f;

	const float angle_to_edge = atan2f(wheel_dist, sensor_dist);
	angle_to_rot = PI - angle_to_edge;

	float vel[4] = {0};
	
	motors_set_velocity(vel);

	#ifdef FIGHT_DEBUG
		char b[128] = {0};
		snprintf(b, 128, "measure stop %ld %ld %ld %ld\navg: %+.2f dist: %+.5fm angle: %+.2f* dir: %u\n", 
			delta[0], delta[1], delta[2], delta[3], 
			(double)delta_avg, (double)wheel_dist, (double)angle_to_edge*180./((double)PI), flags.turn_direction);
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void turn_enter(void *buffer) {
	(void)buffer;

	// calculate end wheel position
	const float arc = angle_to_rot*MOTORS_TRACK_WIDTH/2.f;	// m
	const float rot = arc/(MOTORS_WHEEL_READIUS*2.f*PI)*sqrtf(2.f);	// rotations
	const int32_t delta = rot*MOTORS_ENCODER_CPR;

	if(flags.turn_direction) {
		turn_end[0] = (pos[0] - delta + 65536)%65536;
		turn_end[1] = (pos[1] - delta + 65536)%65536;
		turn_end[2] = (pos[2] - delta + 65536)%65536;
		turn_end[3] = (pos[3] - delta + 65536)%65536;
	} else {
		turn_end[0] = (pos[0] + delta)%65536;
		turn_end[1] = (pos[1] + delta)%65536;
		turn_end[2] = (pos[2] + delta)%65536;
		turn_end[3] = (pos[3] + delta)%65536;
	}

	motors_set_control_type(MOTORS_CLOSE_LOOP);

	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "turn start delta: %lu\n", delta);
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

void turn_execute(void *buffer) {
	(void)buffer;

	int32_t delta[4] = {0};
	delta[0] = abs(motors_get_position_delta(pos[0], turn_end[0]));
	delta[1] = abs(motors_get_position_delta(pos[1], turn_end[1]));
	delta[2] = abs(motors_get_position_delta(pos[2], turn_end[2]));
	delta[3] = abs(motors_get_position_delta(pos[3], turn_end[3]));

	float vel[4] = {0};

	if(delta[0]>TURN_POS_EPSILON)
		vel[0] = (flags.turn_direction ? TURN_VEL : -TURN_VEL);

	if(delta[1]>TURN_POS_EPSILON)
		vel[1] = (flags.turn_direction ? -TURN_VEL : TURN_VEL);

	if(delta[2]>TURN_POS_EPSILON)
		vel[2] = (flags.turn_direction ? -TURN_VEL : TURN_VEL);

	if(delta[3]>TURN_POS_EPSILON)
		vel[3] = (flags.turn_direction ? TURN_VEL : -TURN_VEL);
	
	motors_set_velocity(vel);

	#ifdef FIGHT_DEBUG
		char b[32] = {0};
		snprintf(b, 32, "turn %lu %lu %lu %lu\n", delta[0], delta[1], delta[2], delta[3]);
		uart2_transmit(b, strlen(b));
		uart3_transmit(b, strlen(b));
	#endif
}

// -------------------------------------------------------

void fight_init() {
	FiniteStateMachine_Init(&fsm, NULL);

	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_FOLLOW,	follow_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_FIGHT,		fight_enter,	fight_execute,	NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_EXPLORE,	explore_enter,	NULL,			NULL);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_MEASURE,	measure_enter,	NULL,			measure_exit);
	FiniteStateMachine_DefineState(&fsm, FIGHT_STATE_TURN,		turn_enter,		turn_execute,	NULL);

	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FOLLOW,	FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_EXPLORE,	FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_MEASURE,	FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_TURN,		FIGHT_STATE_FIGHT,		0, NULL, get_enemy_spotted);

	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FIGHT,	FIGHT_STATE_FOLLOW,		0, NULL, get_enemy_lost);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FOLLOW,	FIGHT_STATE_EXPLORE,	0, NULL, get_timeout);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_FOLLOW,	FIGHT_STATE_MEASURE,	0, NULL, get_line_external);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_EXPLORE,	FIGHT_STATE_MEASURE,	0, NULL, get_line_external);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_MEASURE,	FIGHT_STATE_TURN,		0, NULL, get_line_internal);
	FiniteStateMachine_DefineTransition(&fsm, FIGHT_STATE_TURN,		FIGHT_STATE_EXPLORE,	0, NULL, get_turn_complete);

	FiniteStateMachine_Start(&fsm, FIGHT_STATE_FOLLOW);

	fight_pid.Kp = FIGHT_PID_KP;
	fight_pid.Ki = 0.f;
	fight_pid.Kd = 0.f;
	arm_pid_init_f32(&fight_pid, 1);
}

void fight_update() {

	curr_time = xTaskGetTickCount();
	proximity_get_state(prox);
	line_get_state(line);
	motors_get_position(pos);

	if(prox[0] || prox[1])
		flags.follow_direction = 0;
	else if(prox[2] || prox[3])
		flags.follow_direction = 1;

	if((line[0] || line[3]) && (!last_line[0] && !last_line[3]))
		flags.turn_direction = line[0];

	FiniteStateMachine_Update(&fsm);
	FiniteStateMachine_Execute(&fsm);

	memcpy(last_prox, prox, 4*sizeof(uint8_t));
	memcpy(last_line, line, 4*sizeof(uint8_t));
}