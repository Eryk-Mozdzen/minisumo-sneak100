#include "cli.h"

static QueueHandle_t commands;

static void listener(void *param) {
	(void)param;

	char tx_buffer[CLI_LINE_MAX_SIZE] = {0};
	cli_command_t cmd = {0};
	BaseType_t result;

    while(1) {

        if(xQueueReceive(commands, &cmd, portMAX_DELAY)) {

			result = pdTRUE;
			while(result) {
				result = FreeRTOS_CLIProcessCommand(cmd.buffer, tx_buffer, CLI_LINE_MAX_SIZE);

				if(cmd.callback)
					cmd.callback(tx_buffer, strlen(tx_buffer));

				memset(tx_buffer, 0, CLI_LINE_MAX_SIZE);
			}

			memset(cmd.buffer, 0, sizeof(cli_command_t));
        }
    }
}

void cli_init() {

	commands = xQueueCreate(CLI_QUEUE_SIZE, sizeof(cli_command_t));

	FreeRTOS_CLIRegisterCommand(&cli_command_motor_vel);
	FreeRTOS_CLIRegisterCommand(&cli_command_proximity_state);

	xTaskCreate(listener, "CLI listener", 1024, NULL, 4, NULL);
}

void cli_send(const cli_command_t *cmd) {
	xQueueSend(commands, cmd, 100);
}

void cli_send_isr(const cli_command_t *cmd) {
	xQueueSendFromISR(commands, cmd, NULL);
}