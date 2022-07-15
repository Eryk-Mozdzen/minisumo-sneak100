#include "uart2.h"

static QueueHandle_t buffer_tx;
static cli_command_t command_rx;

static void transmitter(void *param) {
	(void)param;

	uint8_t byte;

    while(1) {

		if(xQueueReceive(buffer_tx, &byte, portMAX_DELAY)) {
			USART2->DR = byte;
			USART2->CR1 |=USART_CR1_TXEIE;

			vTaskDelay(100);
		}
    }
}

void uart2_init() {
	// PA2 -> TX
    // PA3 -> RX
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER |=(2<<GPIO_MODER_MODER2_Pos) | (2<<GPIO_MODER_MODER3_Pos);
    GPIOA->OSPEEDR |=(3<<GPIO_OSPEEDR_OSPEED10_Pos) | (3<<GPIO_OSPEEDR_OSPEED11_Pos);
    GPIOA->AFR[0] |=(7<<GPIO_AFRL_AFSEL2_Pos) | (7<<GPIO_AFRL_AFSEL3_Pos);

    // UART2
    RCC->APB1ENR |=RCC_APB1ENR_USART2EN;

	USART2->CR1 |=USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE;
	USART2->BRR |=(13<<USART_BRR_DIV_Fraction_Pos) | (22<<USART_BRR_DIV_Mantissa_Pos);

	// --------------------------

	buffer_tx = xQueueCreate(UART2_TX_BUFFER_SIZE, 1);
	
	xTaskCreate(transmitter, "UART2 tx", 130, NULL, 4, NULL);

	// --------------------------

	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(USART2_IRQn);
}

void uart2_transmit(void *buffer, size_t size) {
	for(uint32_t i=0; i<size; i++)
		xQueueSend(buffer_tx, (void *)((uint32_t)buffer + i), portMAX_DELAY);
}

void USART2_IRQHandler() {
	if(USART2->SR & USART_SR_RXNE) {
		const uint8_t byte = USART2->DR;

		if(command_rx.size<CLI_LINE_MAX_SIZE && byte!='\r') {
			command_rx.buffer[command_rx.size] = byte;
			command_rx.size++;
		}

		if(byte=='\r') {
			command_rx.callback = uart2_transmit;
			cli_send_isr(&command_rx);
			memset(&command_rx, 0, sizeof(cli_command_t));
		}
	} else if(USART2->SR & USART_SR_TXE) {
		uint8_t byte;

		if(xQueueReceiveFromISR(buffer_tx, &byte, NULL))
			USART2->DR = byte;
		else
			USART2->CR1 &=~USART_CR1_TXEIE;
	}
}