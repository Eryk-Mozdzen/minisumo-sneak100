#include "uart3.h"

static QueueHandle_t buffer_tx;
static cli_command_t command_rx;

static void transmitter(void *param) {
	(void)param;

	uint8_t byte;

    while(1) {

		if(xQueueReceive(buffer_tx, &byte, portMAX_DELAY)) {
			USART3->DR = byte;
			USART3->CR1 |=USART_CR1_TXEIE;

			vTaskDelay(100);
		}
    }
}

void uart3_init() {
	// PB10 = TX
    // PB11 = RX
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER |=(2<<GPIO_MODER_MODER10_Pos) | (2<<GPIO_MODER_MODER11_Pos);
    GPIOB->OSPEEDR |=(3<<GPIO_OSPEEDR_OSPEED10_Pos) | (3<<GPIO_OSPEEDR_OSPEED11_Pos);
    GPIOB->AFR[1] |=(7<<GPIO_AFRH_AFSEL10_Pos) | (7<<GPIO_AFRH_AFSEL11_Pos);

    // UART3
    RCC->APB1ENR |=RCC_APB1ENR_USART3EN;

	USART3->CR1 |=USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE;
	USART3->BRR |=(13<<USART_BRR_DIV_Fraction_Pos) | (22<<USART_BRR_DIV_Mantissa_Pos);

	// --------------------------

	buffer_tx = xQueueCreate(UART3_TX_BUFFER_SIZE, 1);
	
	xTaskCreate(transmitter, "UART3 tx", 130, NULL, 4, NULL);

	// --------------------------

	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(USART3_IRQn);
}

void uart3_transmit(void *buffer, size_t size) {
	for(uint32_t i=0; i<size; i++)
		xQueueSend(buffer_tx, (void *)((uint32_t)buffer + i), portMAX_DELAY);
}

void USART3_IRQHandler() {
	if(USART3->SR & USART_SR_RXNE) {
		const uint8_t byte = USART3->DR;

		if(command_rx.size<CLI_LINE_MAX_SIZE && byte!='\r') {
			command_rx.buffer[command_rx.size] = byte;
			command_rx.size++;
		}

		if(byte=='\r') {
			command_rx.callback = uart3_transmit;
			cli_send_isr(&command_rx);
			memset(&command_rx, 0, sizeof(cli_command_t));
		}
	} else if(USART3->SR & USART_SR_TXE) {
		uint8_t byte;

		if(xQueueReceiveFromISR(buffer_tx, &byte, NULL))
			USART3->DR = byte;
		else
			USART3->CR1 &=~USART_CR1_TXEIE;
	}
}