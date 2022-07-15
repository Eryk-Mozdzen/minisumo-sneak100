#include "cli_apps.h"

static BaseType_t motor_vel_callback(char *, size_t, const char *);

const CLI_Command_Definition_t cli_command_motor_vel = {
	"motor",
	"motor <lf> <rf> <rb> <lb>: set motor velocity in RPS\n",
	motor_vel_callback,
	4
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