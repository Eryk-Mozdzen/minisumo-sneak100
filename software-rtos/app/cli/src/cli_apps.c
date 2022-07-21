#include "cli_apps.h"

static BaseType_t motor_vel(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;

	float vel[4] = {0};

	if(sscanf(&pcCommandString[6], "%f%f%f%f", &vel[0], &vel[1], &vel[2], &vel[3])!=4) {
		sprintf(pcWriteBuffer, "Unknown parameters\n");
		return pdFALSE;
	}

	motors_set_velocity(vel);

	return pdFALSE;
}

static BaseType_t motor(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;
	(void)pcCommandString;

	int32_t pos[4] = {0};
	float vel[4] = {0};
	float pwr[4] = {0};

	motors_get_position(pos);
	motors_get_velocity(vel);
	motors_get_power(pwr);

	sprintf(pcWriteBuffer, "%-6lu%+.2f %+d%%\n%-6lu%+.2f %+d%%\n%-6lu%+.2f %+d%%\n%-6lu%+.2f %+d%%\n", 
		pos[0], (double)vel[0], (int)(100.f*pwr[0]),
		pos[1], (double)vel[1], (int)(100.f*pwr[1]),
		pos[2], (double)vel[2], (int)(100.f*pwr[2]),
		pos[3], (double)vel[3], (int)(100.f*pwr[3])
	);

	return pdFALSE;
}

static BaseType_t prox(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;
	(void)pcCommandString;

	uint8_t prox[4] = {0};

	proximity_get_state(prox);

	sprintf(pcWriteBuffer, "%u\n%u\n%u\n%u\n", 
		prox[0], 
		prox[1], 
		prox[2], 
		prox[3]
	);

	return pdFALSE;
}

static BaseType_t line(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;
	(void)pcCommandString;

	uint16_t raw[4] = {0};
	uint8_t line[4] = {0};

	line_get_raw(raw);
	line_get_state(line);

	sprintf(pcWriteBuffer, "%-7u%u\n%-7u%u\n%-7u%u\n%-7u%u\n", 
		raw[0], line[0], 
		raw[1], line[1], 
		raw[2], line[2], 
		raw[3], line[3]
	);

	return pdFALSE;
}

static BaseType_t batt(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)xWriteBufferLen;
	(void)pcCommandString;

	const float batt = get_voltage();

	sprintf(pcWriteBuffer, "%.2f\n", (double)batt);

	return pdFALSE;
}

const CLI_Command_Definition_t cli_command_motor_vel = {
	"motor-vel",
	"motor-vel <lf> <rf> <rb> <lb>: set motor velocity in RPS\n",
	motor_vel,
	4
};

const CLI_Command_Definition_t cli_command_motor = {
	"motor",
	"motor: get motors full data\n",
	motor,
	0
};

const CLI_Command_Definition_t cli_command_prox = {
	"prox",
	"prox: get proximity full data\n",
	prox,
	0
};

const CLI_Command_Definition_t cli_command_line = {
	"line",
	"line: get line sensors full data\n",
	line,
	0
};

const CLI_Command_Definition_t cli_command_batt = {
	"batt",
	"batt: get battery voltage in volts\n",
	batt,
	0
};