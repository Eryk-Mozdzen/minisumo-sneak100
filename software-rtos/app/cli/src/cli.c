#include "cli.h"

static void listener(void *param) {
	(void)param;

    char rx_buffer[UART3_RX_BUFFER_SIZE] = {0};
    char tx_buffer[UART3_TX_BUFFER_SIZE] = {0};
    uint8_t rx_buffer_count = 0;
    BaseType_t result;

    while(1) {

        if(uart3_receive(&rx_buffer[rx_buffer_count])) {
            rx_buffer_count++;

            if(rx_buffer[rx_buffer_count-1]=='\r' || rx_buffer_count>=UART3_RX_BUFFER_SIZE) {
                rx_buffer[rx_buffer_count-1] = '\0';

                result = pdTRUE;
                while(result) {
                    result = FreeRTOS_CLIProcessCommand(rx_buffer, tx_buffer, UART3_TX_BUFFER_SIZE);

                    uart3_transmit(tx_buffer, strlen(tx_buffer));

                    memset(tx_buffer, 0, UART3_TX_BUFFER_SIZE);
                }

                rx_buffer_count = 0;
                memset(rx_buffer, 0, UART3_RX_BUFFER_SIZE);
            }
        }
    }
}

void cli_init() {

	FreeRTOS_CLIRegisterCommand(&__CLI_Command_Motor);

	xTaskCreate(listener, "CLI listener", 1024, NULL, 4, NULL);
}