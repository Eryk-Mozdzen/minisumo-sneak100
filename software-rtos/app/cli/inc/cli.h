#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "task.h"
#include "queue.h"
#include "cli_apps.h"

#define CLI_QUEUE_SIZE		64
#define CLI_LINE_MAX_SIZE	128

typedef void (*cli_callback_t)(void *, const size_t);

typedef struct {
	char buffer[CLI_LINE_MAX_SIZE];
	size_t size;
	cli_callback_t callback;
} cli_command_t;

void cli_init();
void cli_send(const cli_command_t *);
void cli_send_isr(const cli_command_t *);

#endif