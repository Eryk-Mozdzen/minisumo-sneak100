/*
 * cli.c
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#include "cli.h"

Sneak100_CLI_t cli_bluetooth;
Sneak100_CLI_t cli_debug;

void SNEAK100_CLI_Init() {

	cli_bluetooth.buffer = &sneak100.bluetooth.buffer;
	cli_bluetooth.state = &sneak100.state;
	cli_bluetooth.settings = &sneak100.settings;

	cli_debug.buffer = (RxBufferUART_t *)malloc(sizeof(RxBufferUART_t));
	cli_debug.state = &sneak100.state;
	cli_debug.settings = &sneak100.settings;

	RxBufferUART_Init(cli_debug.buffer, &huart3, 256);

}

void SNEAK100_CLI_Update() {

}
