/*
 * cli_def.h
 *
 *  Created on: Feb 24, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_DEF_H_
#define INC_CLI_DEF_H_

#include "uart.h"
#include "core.h"

#include "cli_conf.h"

typedef struct {
	RxBufferUART_t *buffer;
	char line[CLI_LINE_MAX_SIZE];
	char **argv;
	size_t argc;

	uint8_t update_request;
} Sneak100_CLI_t;

#endif
