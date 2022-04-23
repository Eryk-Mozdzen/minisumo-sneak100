#include "uart3.h"

static struct {
	QueueHandle_t buffer_rx;
	QueueHandle_t buffer_tx;
} uart3;

static void transmitter(void *param) {
	(void)param;

	uint8_t byte;

    while(1) {

		if(xQueueReceive(uart3.buffer_tx, &byte, 1000)) {
			USART3->DR = byte;
			USART3->CR1 |=USART_CR1_TXEIE;

			vTaskDelay(100);
		}
    }
}

void UART3_Init() {
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

	uart3.buffer_rx = xQueueCreate(256, 1);
	uart3.buffer_tx = xQueueCreate(256, 1);
	
	xTaskCreate(transmitter, "UART3 tx", 1024, NULL, 4, NULL);

	// --------------------------

	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(USART3_IRQn);
}

uint8_t UART3_Transmit(void *buffer, uint16_t size) {
	for(uint32_t i=0; i<size; i++) {
		if(!xQueueSend(uart3.buffer_tx, (void *)((uint32_t)buffer + i), 1000))
			return 0;
	}

	return 1;
}

uint8_t UART3_Receive(void *buffer, uint16_t size) {
	for(uint32_t i=0; i<size; i++) {
		if(!xQueueReceive(uart3.buffer_rx, (void *)((uint32_t)buffer + i), 1000))
			return 0;
	}

	return 1;
}

void USART3_IRQHandler() {
	if(USART3->SR & USART_SR_RXNE) {
		uint8_t byte = USART3->DR;

		xQueueSendFromISR(uart3.buffer_rx, &byte, NULL);
	} else if(USART3->SR & USART_SR_TXE) {
		uint8_t byte;

		if(xQueueReceiveFromISR(uart3.buffer_tx, &byte, NULL))
			USART3->DR = byte;
		else
			USART3->CR1 &=~USART_CR1_TXEIE;
	}
}