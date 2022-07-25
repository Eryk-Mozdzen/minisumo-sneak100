#include "i2c1.h"

static SemaphoreHandle_t mutex;

static uint8_t wait_for_flag_set(volatile uint32_t *reg, const uint32_t flag, const uint32_t timeout) {
	const uint32_t end = xTaskGetTickCount() + timeout;

	while(!(*reg & flag) && (xTaskGetTickCount()<end));

	return ((*reg & flag)>0);
}

void i2c1_init() {
	// SDA -> PB9
	// SCL -> PB8
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER |=(2<<GPIO_MODER_MODER8_Pos) | (2<<GPIO_MODER_MODER9_Pos);
	GPIOB->OTYPER |=GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9;
    GPIOB->OSPEEDR |=(3<<GPIO_OSPEEDR_OSPEED8_Pos) | (3<<GPIO_OSPEEDR_OSPEED9_Pos);
	GPIOB->PUPDR |=(1<<GPIO_PUPDR_PUPD8_Pos) | (1<<GPIO_PUPDR_PUPD9_Pos);
    GPIOB->AFR[1] |=(4<<GPIO_AFRH_AFSEL8_Pos) | (4<<GPIO_AFRH_AFSEL9_Pos);

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
	xSemaphoreGive(mutex);
}

uint8_t i2c1_write_8(const uint8_t dev_address, const uint8_t reg_address, const void *data_src, const uint32_t data_size, const uint32_t timeout) {
	if(!xSemaphoreTake(mutex, timeout))
		return 1;

	I2C1->CR1 &=~I2C_CR1_POS;

	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 2;
	}
		

	I2C1->DR = (dev_address<<1) | 0x00;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 3;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->DR = reg_address;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_BTF, timeout)) {
		xSemaphoreGive(mutex);
		return 4;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	for(uint32_t i=0; i<data_size; i++) {
		I2C1->DR = ((uint8_t *)data_src)[i];
		if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_TXE, timeout)) {
			xSemaphoreGive(mutex);
			return 5;
		}
		(void)I2C1->SR1;
		(void)I2C1->SR2;
	}

	I2C1->CR1 |=I2C_CR1_STOP;
	if(!wait_for_flag_set(&I2C1->SR2, I2C_SR2_BUSY, timeout)) {
		xSemaphoreGive(mutex);
		return 6;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	xSemaphoreGive(mutex);
	
	return 0;
}

uint8_t i2c1_read_8(const uint8_t dev_address, const uint8_t reg_address, void *data_dest, const uint32_t data_size, const uint32_t timeout) {
	if(!xSemaphoreTake(mutex, timeout))
		return 1;
	
	uint32_t reg;

	I2C1->CR1 &=~I2C_CR1_POS;

	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 2;
	}
	reg = I2C1->SR1;
	
	I2C1->CR1 |=I2C_CR1_ACK;

	I2C1->DR = (dev_address<<1) | 0x00;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 3;
	}
	reg = I2C1->SR1;
	reg = I2C1->SR2;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_TXE, timeout)) {
		xSemaphoreGive(mutex);
		return 4;
	}

	I2C1->DR = reg_address;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_TXE, timeout)) {
		xSemaphoreGive(mutex);
		return 5;
	}

	I2C1->CR1 &=~I2C_CR1_POS;
	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 6;
	}
	reg = I2C1->SR1;

	I2C1->DR = (dev_address<<1) | 0x01;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 7;
	}
	reg = I2C1->SR1;
	reg = I2C1->SR2;

	for(uint32_t i=0; i<data_size; i++) {

		if(i==data_size-1) {
			I2C1->CR1 &=~I2C_CR1_ACK;
			I2C1->CR1 |=I2C_CR1_STOP;
		}

		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		((uint8_t *)data_dest)[i] = I2C1->DR;
	}
	
	(void)reg;

	xSemaphoreGive(mutex);
	
	return 0;
}

uint8_t i2c1_write_16(const uint8_t dev_address, const uint16_t reg_address, const void *data_src, const uint32_t data_size, const uint32_t timeout) {
	if(!xSemaphoreTake(mutex, timeout))
		return 1;

	I2C1->CR1 &=~I2C_CR1_POS;

	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 2;
	}

	I2C1->DR = (dev_address<<1) | 0x00;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 3;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->DR = ((reg_address & 0x7F00) >> 8);
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_BTF, timeout)) {
		xSemaphoreGive(mutex);
		return 4;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->DR = (reg_address & 0x00FF);
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_BTF, timeout)) {
		xSemaphoreGive(mutex);
		return 5;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	for(uint32_t i=0; i<data_size; i++) {
		I2C1->DR = ((uint8_t *)data_src)[i];
		if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_TXE, timeout)) {
			xSemaphoreGive(mutex);
			return 6;
		}
		(void)I2C1->SR1;
		(void)I2C1->SR2;
	}

	I2C1->CR1 |=I2C_CR1_STOP;
	if(!wait_for_flag_set(&I2C1->SR2, I2C_SR2_BUSY, timeout)) {
		xSemaphoreGive(mutex);
		return 7;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	xSemaphoreGive(mutex);
	
	return 0;
}

uint8_t i2c1_read_16(const uint8_t dev_address, const uint16_t reg_address, void *data_dest, const uint32_t data_size, const uint32_t timeout) {
	if(!xSemaphoreTake(mutex, timeout))
		return 1;

	I2C1->CR1 &=~I2C_CR1_POS;

	I2C1->CR1 |=I2C_CR1_ACK;

	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 2;
	}

	I2C1->DR = (dev_address<<1) | 0x00;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 3;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->DR = ((reg_address & 0x7F00) >> 8);
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_BTF, timeout)) {
		xSemaphoreGive(mutex);
		return 4;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->DR = (reg_address & 0x00FF);
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_BTF, timeout)) {
		xSemaphoreGive(mutex);
		return 5;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	I2C1->CR1 |=I2C_CR1_START;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_SB, timeout)) {
		xSemaphoreGive(mutex);
		return 6;
	}

	I2C1->DR = (dev_address<<1) | 0x01;
	if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_ADDR, timeout)) {
		xSemaphoreGive(mutex);
		return 7;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	for(uint32_t i=0; i<data_size; i++) {
		if(!wait_for_flag_set(&I2C1->SR1, I2C_SR1_RXNE, timeout)) {
			xSemaphoreGive(mutex);
			return 8;
		}
		((uint8_t *)data_dest)[i] = I2C1->DR;
	}

	I2C1->CR1 |=I2C_CR1_STOP;
	if(!wait_for_flag_set(&I2C1->SR2, I2C_SR2_BUSY, timeout)) {
		xSemaphoreGive(mutex);
		return 9;
	}
	(void)I2C1->SR1;
	(void)I2C1->SR2;

	xSemaphoreGive(mutex);
	
	return 0;
}