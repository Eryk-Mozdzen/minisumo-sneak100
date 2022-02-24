/*
 * cli.h
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "usart.h"

#include "cli_conf.h"
#include "cli_def.h"
#include "cli_cmd.h"

extern Sneak100_CLI_t cli_bluetooth;
extern Sneak100_CLI_t cli_debug;

void SNEAK100_CLI_Init();
void SNEAK100_CLI_Update();
void SNEAK100_CLI_UpdateRequest();

#endif
