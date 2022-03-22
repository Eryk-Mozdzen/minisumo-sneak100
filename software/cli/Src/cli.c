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

static void __CLI_ParseArgs(char *, size_t *, char ***);
static void __CLI_FreeArgs(size_t *, char ***);

void SNEAK100_CLI_Init() {

	cli_bluetooth = (const Sneak100_CLI_t){0};
	cli_bluetooth.buffer = &core.bluetooth.buffer;

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

