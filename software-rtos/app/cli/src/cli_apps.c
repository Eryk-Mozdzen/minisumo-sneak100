#include "cli_apps.h"

static BaseType_t motor_vel_callback(char *, size_t, const char *);
static BaseType_t proximity_state_callback(char *, size_t, const char *);

const CLI_Command_Definition_t cli_command_motor_vel = {
	"motor",
	"motor <lf> <rf> <rb> <lb>: set motor velocity in RPS\n",
	motor_vel_callback,
	4
};

const CLI_Command_Definition_t cli_command_proximity_state = {
	"prox",
	"prox: get proximity sensors state\n",
	proximity_state_callback,
	0
};

BaseType_t motor_vel_callback(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;

	float vel[4] = {0};

	if(sscanf(&pcCommandString[6], "%f%f%f%f", &vel[0], &vel[1], &vel[2], &vel[3])!=4) {
		sprintf(pcWriteBuffer, "Unknown parameters\n");
		return pdFALSE;
	}

	motors_set_velocity(vel);

	return pdFALSE;
}

BaseType_t proximity_state_callback(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;
	(void)pcCommandString;

	uint8_t prox[4] = {0};

	proximity_get_state(prox);

	sprintf(pcWriteBuffer, "%u%u%u%u\n", prox[0], prox[1], prox[2], prox[3]);

	return pdFALSE;
}