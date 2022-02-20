/*
 * cli.c
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#include "cli.h"

Sneak100_CLI_t cli_bluetooth;
Sneak100_CLI_t cli_debug;

static void __CLI_Update(Sneak100_CLI_t *);
static void __CLI_PrintPrompt(Sneak100_CLI_t *);

static void __CLI_ParseArgs(char *, size_t *, char ***);
static void __CLI_FreeArgs(size_t *, char ***);

static void __CLI_Cmd_Help(Sneak100_CLI_t *);
static void __CLI_Cmd_Reset(Sneak100_CLI_t *);
static void __CLI_Cmd_ConfigBT(Sneak100_CLI_t *);
static void __CLI_Cmd_Settings(Sneak100_CLI_t *);
static void __CLI_Cmd_Proximity(Sneak100_CLI_t *);
static void __CLI_Cmd_Line(Sneak100_CLI_t *);
static void __CLI_Cmd_Motor(Sneak100_CLI_t *);

void SNEAK100_CLI_Init() {

	cli_bluetooth = (const Sneak100_CLI_t){0};
	cli_bluetooth.buffer = &sneak100.bluetooth.buffer;

	cli_debug = (const Sneak100_CLI_t){0};
	cli_debug.buffer = (RxBufferUART_t *)malloc(sizeof(RxBufferUART_t));

	RxBufferUART_Init(cli_debug.buffer, &huart3, CLI_LINE_MAX_SIZE);

	__CLI_PrintPrompt(&cli_bluetooth);
	__CLI_PrintPrompt(&cli_debug);
}

void SNEAK100_CLI_Update() {

	//if(sneak100.state.bluetooth==BLUETOOTH_STATUS_PAIRED)
	__CLI_Update(&cli_bluetooth);

	__CLI_Update(&cli_debug);
}

void SNEAK100_CLI_UpdateRequest() {
	cli_bluetooth.update_request = 1;
	cli_debug.update_request = 1;
}

void __CLI_Update(Sneak100_CLI_t *cli) {
	if(!cli->update_request)
		return;

	// check if line is complete
	if(!RxBufferUART_ReadUntil(cli->buffer, cli->line, CLI_LINE_TERMINATOR, CLI_LINE_MAX_SIZE))
		return;

	__CLI_ParseArgs(cli->line, &cli->argc, &cli->argv);

	if(!cli->argc) {
		__CLI_PrintPrompt(cli);
		return;
	}

	if(!strcmp(cli->argv[0], "help"))			__CLI_Cmd_Help(cli);
	else if(!strcmp(cli->argv[0], "btconf"))	__CLI_Cmd_ConfigBT(cli);
	else if(!strcmp(cli->argv[0], "reset"))		__CLI_Cmd_Reset(cli);
	else if(!strcmp(cli->argv[0], "sett"))		__CLI_Cmd_Settings(cli);
	else if(!strcmp(cli->argv[0], "prox"))		__CLI_Cmd_Proximity(cli);
	else if(!strcmp(cli->argv[0], "line"))		__CLI_Cmd_Line(cli);
	else if(!strcmp(cli->argv[0], "mot"))		__CLI_Cmd_Motor(cli);
	else
		__CLI_PrintFormat(cli, "unknown command: '%s'\n", cli->argv[0]);

	__CLI_FreeArgs(&cli->argc, &cli->argv);

	__CLI_PrintPrompt(cli);

	cli->update_request = 0;
}

void __CLI_PrintPrompt(Sneak100_CLI_t *cli) {
	__CLI_PrintFormat(cli, "$ ");
}

void __CLI_PrintFormat(Sneak100_CLI_t *cli, const char *format, ...) {
	char buffer[CLI_PRINT_FORMAT_BUFFER_SIZE] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	HAL_UART_Transmit(cli->buffer->huart, (uint8_t *)buffer, strlen(buffer) + 1, HAL_MAX_DELAY);
}

void __CLI_ParseArgs(char *line, size_t *argc, char ***argv) {
	*argc = 0;
	*argv = NULL;

	char *token = strtok(line, CLI_ARG_DELIMITERS);

	while(token) {

		(*argc)++;
		*argv = (char **)realloc(*argv, *argc*sizeof(char *));
		(*argv)[*argc - 1] = (char *)malloc(strlen(token) + 1);

		strcpy((*argv)[*argc - 1], token);

		token = strtok(NULL, CLI_ARG_DELIMITERS);
	}
}

void __CLI_FreeArgs(size_t *argc, char ***argv) {
	for(size_t i=0; i<*argc; i++)
		free((*argv)[i]);
	free(*argv);

	*argc = 0;
	*argv = NULL;
}

void __CLI_Cmd_Help(Sneak100_CLI_t *cli) {
	__CLI_PrintFormat(cli, CLI_HELP_MESSAGE);
}

void __CLI_Cmd_Reset(Sneak100_CLI_t *cli) {
	NVIC_SystemReset();
}

void __CLI_Cmd_ConfigBT(Sneak100_CLI_t *cli) {
	size_t argc = cli->argc;
	char **argv = cli->argv;
	Bluetooth_Config_t config = {0};

	strcpy(config.name, BLUETOOTH_NAME);
	strcpy(config.password, BLUETOOTH_PASSWORD);
	config.baudrate = BLUETOOTH_BAUDRATE_38400;

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-n") && i+1<argc) {
			i++;
			strcpy(config.name, argv[i]);
		} else if(!strcmp(argv[i], "-p") && i+1<argc) {
			i++;
			strcpy(config.password, argv[i]);
		} else {
			__CLI_PrintFormat(cli, "invalid param: '%s'\n", argv[i]);
		}
	}

	HAL_StatusTypeDef status = Bluetooth_SetConfig(&sneak100.bluetooth, config);

	if(status!=HAL_OK)
		__CLI_PrintFormat(cli, "error code: %u\n", status);
}

void __CLI_Cmd_Settings(Sneak100_CLI_t *cli) {
	size_t argc = cli->argc;
	char **argv = cli->argv;

	Settings_Mode_t mode = SETTINGS_MODE_INVALID;
	Settings_Dyhlo_t dyhlo = SETTINGS_DYHLO_INVALID;
	Settings_Strategy_t strategy = SETTINGS_STRATEGY_INVALID;

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-m") && i+1<argc) {
			i++;

			if(!strcmp(argv[i], "module"))		mode = SETTINGS_MODE_MODULE;
			else if(!strcmp(argv[i], "button"))	mode = SETTINGS_MODE_BUTTON;
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);

		} else if(!strcmp(argv[i], "-d") && i+1<argc) {
			i++;

			if(!strcmp(argv[i], "black"))		dyhlo = SETTINGS_DYHLO_BLACK;
			else if(!strcmp(argv[i], "white"))	dyhlo = SETTINGS_DYHLO_WHITE;
			else if(!strcmp(argv[i], "auto"))	dyhlo = SETTINGS_DYHLO_AUTO;
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);

		} else if(!strcmp(argv[i], "-s") && i+1<argc) {
			i++;

			if(!strcmp(argv[i], "agressive"))		strategy = SETTINGS_STRATEGY_AGRESSIVE;
			else if(!strcmp(argv[i], "defensive"))	strategy = SETTINGS_STRATEGY_DEFENSIVE;
			else if(!strcmp(argv[i], "passive"))	strategy = SETTINGS_STRATEGY_PASSIVE;
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);

		} else {
			__CLI_PrintFormat(cli, "invalid param: '%s'\n", argv[i]);
		}

	}

	if(mode!=SETTINGS_MODE_INVALID)
		sneak100.settings.mode = mode;
	if(dyhlo!=SETTINGS_DYHLO_INVALID)
		sneak100.settings.dyhlo = dyhlo;
	if(strategy!=SETTINGS_STRATEGY_INVALID)
		sneak100.settings.strategy = strategy;

	SNEAK100_Core_WriteSettings();
}

void __CLI_Cmd_Proximity(Sneak100_CLI_t *cli) {
	size_t argc = cli->argc;
	char **argv = cli->argv;

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-i") && i+1<argc) {
			i++;

			if(!strcmp(argv[i], "ll"))			__CLI_PrintFormat(cli, "%u\n", sneak100.state.proximity[PROXIMITY_LL]);
			else if(!strcmp(argv[i], "fl"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.proximity[PROXIMITY_FL]);
			else if(!strcmp(argv[i], "fr"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.proximity[PROXIMITY_FR]);
			else if(!strcmp(argv[i], "rr"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.proximity[PROXIMITY_RR]);
			else if(!strcmp(argv[i], "all"))
				__CLI_PrintFormat(cli, "%u %u %u %u\n",
					sneak100.state.proximity[PROXIMITY_LL],
					sneak100.state.proximity[PROXIMITY_FL],
					sneak100.state.proximity[PROXIMITY_FR],
					sneak100.state.proximity[PROXIMITY_RR]
				);
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);

		} else {
			__CLI_PrintFormat(cli, "invalid param: '%s'\n", argv[i]);
		}

	}
}

void __CLI_Cmd_Line(Sneak100_CLI_t *cli) {
	size_t argc = cli->argc;
	char **argv = cli->argv;

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-i") && i+1<argc) {
			i++;

			if(!strcmp(argv[i], "ll"))			__CLI_PrintFormat(cli, "%u\n", sneak100.state.line[LINE_LL].state);
			else if(!strcmp(argv[i], "lm"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.line[LINE_LM].state);
			else if(!strcmp(argv[i], "rm"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.line[LINE_RM].state);
			else if(!strcmp(argv[i], "rr"))		__CLI_PrintFormat(cli, "%u\n", sneak100.state.line[LINE_RR].state);
			else if(!strcmp(argv[i], "all"))
				__CLI_PrintFormat(cli, "%u %u %u %u\n",
					sneak100.state.line[LINE_LL].state,
					sneak100.state.line[LINE_LM].state,
					sneak100.state.line[LINE_RM].state,
					sneak100.state.line[LINE_RR].state
				);
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);

		} else {
			__CLI_PrintFormat(cli, "invalid param: '%s'\n", argv[i]);
		}

	}
}

void __CLI_Cmd_Motor(Sneak100_CLI_t *cli) {
	size_t argc = cli->argc;
	char **argv = cli->argv;

	struct {
		uint8_t get : 1;
		uint8_t set : 1;
		uint8_t index : 1;
		uint8_t index_all : 1;
		uint8_t	velocity : 1;
		uint8_t position : 1;
		uint8_t power : 1;
	} flags = {0};

	struct {
		Motor_Enum index;
		float velocity;
		float position;
		float power;
	} data;

	for(size_t i=1; i<argc; i++) {
		if(argv[i][0]!='-')
			continue;

		if(!strcmp(argv[i], "--get")) 		flags.get = 1;
		else if(!strcmp(argv[i], "--set"))	flags.set = 1;
		else if(!strcmp(argv[i], "-v"))		flags.velocity = 1;
		else if(!strcmp(argv[i], "-p"))		flags.position = 1;
		else if(!strcmp(argv[i], "-f"))		flags.power = 1;
		else if(!strcmp(argv[i], "-i")) {
			flags.index = 1;
			i++;

			if(!strcmp(argv[i], "lf"))			data.index = MOTOR_LF;
			else if(!strcmp(argv[i], "lb"))		data.index = MOTOR_LB;
			else if(!strcmp(argv[i], "rf"))		data.index = MOTOR_RF;
			else if(!strcmp(argv[i], "rb"))		data.index = MOTOR_RB;
			else if(!strcmp(argv[i], "all"))	flags.index_all = 1;
			else
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);
		} else
			__CLI_PrintFormat(cli, "invalid param: '%s'\n", argv[i]);
	}

	if(flags.set && flags.get) {
		__CLI_PrintFormat(cli, "invalid operation\n");
		return;
	}

	if(!flags.set && !flags.get) {
		__CLI_PrintFormat(cli, "operation not specified\n");
		return;
	}

	if(!flags.index) {
		__CLI_PrintFormat(cli, "motor not specified\n");
		return;
	}

	if(flags.get) {

		if(!flags.index_all) {

			if(flags.velocity)
				__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[data.index].velocity);
			else if(flags.position)
				__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[data.index].position);
			else if(flags.power)
				__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[data.index].power);

			return;
		}

		if(flags.velocity) {
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LF].velocity);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LB].velocity);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_RF].velocity);
			__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[MOTOR_RB].velocity);
		} else if(flags.position) {
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LF].position);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LB].position);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_RF].position);
			__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[MOTOR_RB].position);
		} else if(flags.power) {
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LF].power);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_LB].power);
			__CLI_PrintFormat(cli, "%.3f ", sneak100.state.motor[MOTOR_RF].power);
			__CLI_PrintFormat(cli, "%.3f\n", sneak100.state.motor[MOTOR_RB].power);
		}

		return;
	};

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-v") && i+1<argc) {
			i++;

			if(sscanf(argv[i], "%f", &data.velocity)!=1)
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);
		} else if(!strcmp(argv[i], "-p") && i+1<argc) {
			i++;

			if(sscanf(argv[i], "%f", &data.position)!=1)
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);
		} else if(!strcmp(argv[i], "-f") && i+1<argc) {
			i++;

			if(sscanf(argv[i], "%f", &data.power)!=1)
				__CLI_PrintFormat(cli, "invalid arg: '%s'\n", argv[i]);
		}

	}

	if(!flags.index_all) {

		if(flags.velocity)
			Motor_SetVelocity(&sneak100.motors[data.index], data.velocity);
		else if(flags.position)
			Motor_SetPosition(&sneak100.motors[data.index], data.position);
		else if(flags.power)
			Motor_SetPower(&sneak100.motors[data.index], data.power);

		return;
	}

	if(flags.velocity) {
		Motor_SetVelocity(&sneak100.motors[MOTOR_LF], data.velocity);
		Motor_SetVelocity(&sneak100.motors[MOTOR_LB], data.velocity);
		Motor_SetVelocity(&sneak100.motors[MOTOR_RF], data.velocity);
		Motor_SetVelocity(&sneak100.motors[MOTOR_RB], data.velocity);
	} else if(flags.velocity) {
		Motor_SetPosition(&sneak100.motors[MOTOR_LF], data.position);
		Motor_SetPosition(&sneak100.motors[MOTOR_LB], data.position);
		Motor_SetPosition(&sneak100.motors[MOTOR_RF], data.position);
		Motor_SetPosition(&sneak100.motors[MOTOR_RB], data.position);
	} else if(flags.power) {
		Motor_SetPower(&sneak100.motors[MOTOR_LF], data.power);
		Motor_SetPower(&sneak100.motors[MOTOR_LB], data.power);
		Motor_SetPower(&sneak100.motors[MOTOR_RF], data.power);
		Motor_SetPower(&sneak100.motors[MOTOR_RB], data.power);
	}

}

