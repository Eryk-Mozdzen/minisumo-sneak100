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

static void __CLI_Cmd_Help(Sneak100_CLI_t *, size_t, char **);
static void __CLI_Cmd_ConfigBT(Sneak100_CLI_t *, size_t, char **);

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

void __CLI_Update(Sneak100_CLI_t *cli) {

	// check if line is complete
	if(!RxBufferUART_ReadUntil(cli->buffer, cli->line, CLI_LINE_TERMINATOR, CLI_LINE_MAX_SIZE))
		return;

	__CLI_ParseArgs(cli->line, &cli->argc, &cli->argv);

	if(!cli->argc) {
		__CLI_PrintPrompt(cli);
		return;
	}

	if(!strcmp(cli->argv[0], "help"))
		__CLI_Cmd_Help(cli, cli->argc, cli->argv);
	else if(!strcmp(cli->argv[0], "btconf"))
		__CLI_Cmd_ConfigBT(cli, cli->argc, cli->argv);

	__CLI_FreeArgs(&cli->argc, &cli->argv);

	__CLI_PrintPrompt(cli);
}

static void __CLI_PrintPrompt(Sneak100_CLI_t *cli) {
	UART_printf(cli->buffer->huart, "$ ");
}

static void __CLI_ParseArgs(char *line, size_t *argc, char ***argv) {
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

static void __CLI_FreeArgs(size_t *argc, char ***argv) {
	for(size_t i=0; i<*argc; i++)
		free((*argv)[i]);
	free(*argv);

	*argc = 0;
	*argv = NULL;
}

void __CLI_Cmd_Help(Sneak100_CLI_t *cli, size_t argc, char **argv) {

	UART_printf(cli->buffer->huart, "Available commands:\n");
	UART_printf(cli->buffer->huart, "    help\n");
	UART_printf(cli->buffer->huart, "    btconf [-param arg]\n");
}

void __CLI_Cmd_ConfigBT(Sneak100_CLI_t *cli, size_t argc, char **argv) {
	Bluetooth_Config_t config = {0};

	strcpy(config.name, BLUETOOTH_NAME);
	strcpy(config.password, BLUETOOTH_PASSWORD);
	config.baudrate = BLUETOOTH_BAUDRATE_38400;

	for(size_t i=1; i<argc; i++) {
		if(!strcmp(argv[i], "-name") && i+1<argc) {
			i++;
			strcpy(config.name, argv[i]);
		} else if(!strcmp(argv[i], "-password") && i+1<argc) {
			i++;
			strcpy(config.password, argv[i]);
		}
	}

	if(Bluetooth_SetConfig(&sneak100.bluetooth, config)!=HAL_OK)
		UART_printf(cli->buffer->huart, "Error\n");
}

