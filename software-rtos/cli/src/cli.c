#include "cli.h"

static void listener(void *param) {
	(void)param;

    char rx_buffer[CLI_RX_BUFFER_SIZE] = {0};
    char tx_buffer[CLI_TX_BUFFER_SIZE] = {0};
    uint8_t rx_buffer_count = 0;
    BaseType_t result;

    while(1) {

        if(UART3_Receive(&rx_buffer[rx_buffer_count], 1)) {
            rx_buffer_count++;

            if(rx_buffer[rx_buffer_count-1]=='\r' || rx_buffer_count>=CLI_RX_BUFFER_SIZE) {
                rx_buffer[rx_buffer_count-1] = '\0';

                result = pdTRUE;
                while(result) {
                    result = FreeRTOS_CLIProcessCommand(rx_buffer, tx_buffer, CLI_TX_BUFFER_SIZE);

                    UART3_Transmit(tx_buffer, strlen(tx_buffer));

                    memset(tx_buffer, 0, CLI_TX_BUFFER_SIZE);
                }

                rx_buffer_count = 0;
                memset(rx_buffer, 0, CLI_RX_BUFFER_SIZE);
            }
        }
    }
}

void CLI_Init() {

	FreeRTOS_CLIRegisterCommand(&__CLI_Command_Motor);

	xTaskCreate(listener, "CLI listener", 1024, NULL, 4, NULL);
}