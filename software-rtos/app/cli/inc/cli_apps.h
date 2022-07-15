#ifndef CLI_APPS_H
#define CLI_APPS_H

#include "string.h"

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

extern const CLI_Command_Definition_t __CLI_Command_Motor;

BaseType_t __CLI_Callback_Motor(char *, size_t, const char *);

#endif