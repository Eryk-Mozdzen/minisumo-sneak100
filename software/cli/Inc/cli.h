/*
 * cli.h
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "cli_conf.h"

#include "core.h"
#include "uart.h"

typedef struct {
	RxBufferUART_t *buffer;
	char line[CLI_LINE_MAX_SIZE];
	char **argv;
	size_t argc;
} Sneak100_CLI_t;

extern Sneak100_CLI_t cli_bluetooth;
extern Sneak100_CLI_t cli_debug;

void SNEAK100_CLI_Init();
void SNEAK100_CLI_Update();

#endif
