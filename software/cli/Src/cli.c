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

static void __CLI_ParseArgs(char *, size_t *, char [][CLI_ARG_MAX_SIZE]);

static void __CLI_Cmd_Help(Sneak100_CLI_t *, uint8_t, char [][CLI_ARG_MAX_SIZE]);

void SNEAK100_CLI_Init() {

	cli_bluetooth = (const Sneak100_CLI_t){0};
	cli_bluetooth.buffer = &sneak100.bluetooth.buffer;
	cli_bluetooth.state = &sneak100.state;
	cli_bluetooth.settings = &sneak100.settings;

	cli_debug = (const Sneak100_CLI_t){0};
	cli_debug.buffer = (RxBufferUART_t *)malloc(sizeof(RxBufferUART_t));
	cli_debug.state = &sneak100.state;
	cli_debug.settings = &sneak100.settings;

	RxBufferUART_Init(cli_debug.buffer, &huart3, CLI_LINE_MAX_SIZE);

	__CLI_PrintPrompt(&cli_bluetooth);
	__CLI_PrintPrompt(&cli_debug);
}

void SNEAK100_CLI_Update() {

	if(cli_bluetooth.state->bluetooth==BLUETOOTH_STATUS_PAIRED)
		__CLI_Update(&cli_bluetooth);

	__CLI_Update(&cli_debug);

}

static void __CLI_PrintPrompt(Sneak100_CLI_t *cli) {
	UART_printf(cli->buffer->huart, "$ ");
}

void __CLI_Update(Sneak100_CLI_t *cli) {

	// check if line is complete
	if(!RxBufferUART_ReadUntil(cli->buffer, cli->line, CLI_LINE_TERMINATOR, CLI_LINE_MAX_SIZE))
		return;

	__CLI_ParseArgs(cli->line, &cli->argc, cli->argv);

	memset(cli->line, 0, CLI_LINE_MAX_SIZE);

	if(!cli->argc) {
		__CLI_PrintPrompt(cli);
		return;
	}

	if(!strcmp(cli->argv[0], "help"))
		__CLI_Cmd_Help(cli, cli->argc, cli->argv);

	__CLI_PrintPrompt(cli);
}

static void __CLI_ParseArgs(char *line, size_t *argc, char argv[][CLI_ARG_MAX_SIZE]) {
	*argc = 0;
	char *token = strtok(line, CLI_ARG_DELIMITERS);

	while(token) {
		if(*argc>=CLI_ARG_MAX_NUM)
			return;

		strcpy(argv[*argc], token);
		(*argc)++;

		token = strtok(NULL, CLI_ARG_DELIMITERS);
	}
}

void __CLI_Cmd_Help(Sneak100_CLI_t *cli, uint8_t argc, char argv[][CLI_ARG_MAX_SIZE]) {

	UART_printf(cli->buffer->huart, "Available commands:\n");
	UART_printf(cli->buffer->huart, "    help\n");
}
