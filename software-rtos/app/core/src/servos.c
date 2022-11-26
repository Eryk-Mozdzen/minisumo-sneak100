#include "servos.h"
#include "stm32f4xx.h"

void servos_init() {
	// TIM9 CH1 -> PA2 -> left servo
    // TIM9 CH2 -> PA3 -> right servo
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER |=(2<<GPIO_MODER_MODER2_Pos) | (2<<GPIO_MODER_MODER3_Pos);
    GPIOA->OSPEEDR |=(3<<GPIO_OSPEEDR_OSPEED10_Pos) | (3<<GPIO_OSPEEDR_OSPEED11_Pos);
    GPIOA->AFR[0] |=(3<<GPIO_AFRL_AFSEL2_Pos) | (3<<GPIO_AFRL_AFSEL3_Pos);

	// TIM9
	RCC->APB2ENR |=RCC_APB2ENR_TIM9EN;

	TIM9->PSC = 168 - 1;
	TIM9->ARR = 20000;
    TIM9->CCMR1 |=(6<<TIM_CCMR1_OC1M_Pos) | (6<<TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    TIM9->CCER |=TIM_CCER_CC1E | TIM_CCER_CC2E;
    TIM9->BDTR |=TIM_BDTR_MOE;
    TIM9->CR1 |=TIM_CR1_CEN;
}

void servos_set_signal_us(uint16_t *timings) {
	TIM9->CCR1 = timings[0];
	TIM9->CCR2 = timings[1];
}

void servos_set_state(uint8_t *states) {
	TIM9->CCR1 = states[0] ? 2000 : 1000;
	TIM9->CCR2 = states[1] ? 2000 : 1000;
}
