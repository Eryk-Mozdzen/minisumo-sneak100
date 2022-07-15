#include "i2c1.h"

static SemaphoreHandle_t mutex;

void I2C1_Init() {
	// SDA -> PB9
	// SCL -> PB8
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER |=(2<<GPIO_MODER_MODER8_Pos) | (2<<GPIO_MODER_MODER9_Pos);
	GPIOB->OTYPER |=GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9;
    GPIOB->OSPEEDR |=(3<<GPIO_OSPEEDR_OSPEED8_Pos) | (3<<GPIO_OSPEEDR_OSPEED9_Pos);
	GPIOB->PUPDR |=(1<<GPIO_PUPDR_PUPD8_Pos) | (1<<GPIO_PUPDR_PUPD9_Pos);
    GPIOB->AFR[0] |=(4<<GPIO_AFRH_AFSEL8_Pos);
	GPIOB->AFR[1] |=(4<<GPIO_AFRH_AFSEL9_Pos);

	// I2C1
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;

	I2C1->CR1 &=~I2C_CR1_PE;
	I2C1->CR1 |=I2C_CR1_SWRST;
	I2C1->CR1 &=~I2C_CR1_SWRST;
	I2C1->CR2 |=(50<<I2C_CR2_FREQ_Pos);
	I2C1->CCR |=I2C_CCR_FS | (0x28<<I2C_CCR_CCR_Pos);
	I2C1->TRISE |=(0x0F<<I2C_TRISE_TRISE_Pos);
	I2C1->CR1 |=I2C_CR1_PE;

	mutex = xSemaphoreCreateMutex();
}

void I2C1_WriteReg(uint8_t dev_address, uint8_t reg_address, void *data_src, uint8_t data_size) {
	uint32_t reg;

	xSemaphoreTake(mutex, portMAX_DELAY);

	// start
	I2C1->CR1 &=~I2C_CR1_POS;
	I2C1->CR1 |=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
	reg = I2C1->SR1;

	// device address
	I2C1->DR = (dev_address<<1) | 0x00;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	reg = I2C1->SR1;
	reg = I2C1->SR2;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |=I2C_CR1_ACK;

	for(uint8_t i=0; i<data_size; i++) {
		// control byte
		I2C1->DR = reg_address + i;
		while(!(I2C1->SR1 & I2C_SR1_TXE));

		// data byte
		I2C1->DR = ((uint8_t *)data_src)[i];
		while(!(I2C1->SR1 & I2C_SR1_TXE));
	}

	// stop
	I2C1->CR1 |=I2C_CR1_STOP;

	xSemaphoreGive(mutex);

	(void)reg;
}

void I2C1_ReadReg(uint8_t dev_address, uint8_t reg_address, void *data_dest, uint8_t data_size) {
	uint32_t reg;

	xSemaphoreTake(mutex, portMAX_DELAY);

	// start
	I2C1->CR1 &=~I2C_CR1_POS;
	I2C1->CR1 |=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
	reg = I2C1->SR1;

	// write register address
	I2C1->DR = (dev_address<<1) | 0x00;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	reg = I2C1->SR1;
	reg = I2C1->SR2;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->DR = reg_address;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	// read register data
	I2C1->CR1 &=~I2C_CR1_POS;
	I2C1->CR1 |=I2C_CR1_ACK;
	I2C1->CR1 |=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C1->DR = (dev_address<<1) | 0x01; 
	while(!(I2C1 -> SR1 & I2C_SR1_ADDR));
	reg = I2C1->SR1; 
	reg = I2C1->SR2;
	
	I2C1->CR1 |=I2C_CR1_ACK;

	for(uint8_t i=0; i<data_size; i++) {
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		((uint8_t *)data_dest)[i] = I2C1->DR;

		if(i==data_size-1)
			I2C1->CR1 &=~I2C_CR1_ACK;
	}

	// stop
	I2C1->CR1 |=I2C_CR1_STOP;

	xSemaphoreGive(mutex);
	
	(void)reg;
}