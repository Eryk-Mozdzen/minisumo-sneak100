#ifndef CLI_H
#define CLI_H

#include "string.h"

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "task.h"

#include "uart3.h"
#include "cli_apps.h"

void CLI_Init();

#endif