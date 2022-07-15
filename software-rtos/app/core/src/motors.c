#include "motors.h"

static arm_pid_instance_f32 pid[4] = {0};
static float vel_setpoint[4] = {0};

static void update(void *param) {
	(void)param;

	float pos_last[4] = {0};
	float pos_curr[4] = {0};
	float vel_curr[4] = {0};
	float pwr_ctrl[4] = {0};

	while(1) {
		motors_get_position(pos_curr);

		vel_curr[0] = (pos_curr[0] - pos_last[0])*MOTORS_PID_FREQ;
		vel_curr[1] = (pos_curr[1] - pos_last[1])*MOTORS_PID_FREQ;
		vel_curr[2] = (pos_curr[2] - pos_last[2])*MOTORS_PID_FREQ;
		vel_curr[3] = (pos_curr[3] - pos_last[3])*MOTORS_PID_FREQ;

		pwr_ctrl[0] = arm_pid_f32(&pid[0], vel_curr[0] - vel_setpoint[0]);
		pwr_ctrl[1] = arm_pid_f32(&pid[1], vel_curr[1] - vel_setpoint[1]);
		pwr_ctrl[2] = arm_pid_f32(&pid[2], vel_curr[2] - vel_setpoint[2]);
		pwr_ctrl[3] = arm_pid_f32(&pid[3], vel_curr[3] - vel_setpoint[3]);

		motors_set_power(pwr_ctrl);

		memcpy(pos_last, pos_curr, 4*sizeof(float));

		vTaskDelay(1000/MOTORS_PID_FREQ);
	}
}

void motors_init() {

	for(uint8_t i=0; i<4; i++) {
		pid[i].Kp = MOTORS_PID_KP;
		pid[i].Ki = MOTORS_PID_KI;
		pid[i].Kd = MOTORS_PID_KD;
		arm_pid_init_f32(&pid[i], 1);
	}

	xTaskCreate(update, "pid update", 1024, NULL, 4, NULL);
}

void motors_set_power(float *power) {

	for(uint8_t i=0; i<4; i++) {
		if(power[i>1.f])
			power[i] = 1.f;
		else if(power[i]<-1.f)
			power[i] = -1.f;
	}

	// set fill
}

void motors_set_velocity(float *vel_sp) {
	memcpy(vel_setpoint, vel_sp, 4*sizeof(float));
}

void motors_get_position(float *pos_dest) {
	pos_dest[0] = 0.f;
	pos_dest[1] = 0.f;
	pos_dest[2] = 0.f;
	pos_dest[3] = 0.f;
}