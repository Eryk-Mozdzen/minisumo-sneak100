/*
 * cli.h
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "core.h"
#include "uart.h"

typedef struct {
	RxBufferUART_t *buffer;

	RobotState_t *state;
	RobotSettings_t *settings;
} Sneak100_CLI_t;

extern Sneak100_CLI_t cli_bluetooth;
extern Sneak100_CLI_t cli_debug;

void SNEAK100_CLI_Init();
void SNEAK100_CLI_Update();

#endif
