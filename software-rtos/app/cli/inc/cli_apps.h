#ifndef CLI_APPS_H
#define CLI_APPS_H

#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "motors.h"
#include "periph.h"

extern const CLI_Command_Definition_t cli_command_motor_pwr;
extern const CLI_Command_Definition_t cli_command_motor_vel;
extern const CLI_Command_Definition_t cli_command_motor;
extern const CLI_Command_Definition_t cli_command_prox;
extern const CLI_Command_Definition_t cli_command_line;
extern const CLI_Command_Definition_t cli_command_batt;

#endif