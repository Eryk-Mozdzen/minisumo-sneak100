/*
 * cli_cmd.h
 *
 *  Created on: Feb 24, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_CMD_H_
#define INC_CLI_CMD_H_

#include "cli_def.h"
#include "cli_conf.h"

void __CLI_PrintFormat(Sneak100_CLI_t *, const char *, ...);
void __CLI_PrintPrompt(Sneak100_CLI_t *);

void __CLI_Cmd_Help(Sneak100_CLI_t *);
void __CLI_Cmd_Reset(Sneak100_CLI_t *);
void __CLI_Cmd_ConfigBT(Sneak100_CLI_t *);
void __CLI_Cmd_Settings(Sneak100_CLI_t *);
void __CLI_Cmd_Proximity(Sneak100_CLI_t *);
void __CLI_Cmd_Line(Sneak100_CLI_t *);
void __CLI_Cmd_Motor(Sneak100_CLI_t *);

#endif
