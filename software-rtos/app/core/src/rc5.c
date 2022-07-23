#include "rc5.h"

static uint8_t state;
static uint32_t counter;
static uint8_t bits_ready;
static rc5_message_t message;
static FiniteStateMachine_t fsm;

static void emit1(void *buffer) {
	(void)buffer;

	message.frame |=(1<<(13 - bits_ready));
	bits_ready++;
}

static void emit0(void *buffer) {
	(void)buffer;

	message.frame &=~(1<<(13 - bits_ready));
	bits_ready++;
}

static void reset(void *buffer) {
	(void)buffer;

	message = (const rc5_message_t){0};
	bits_ready = 0;
}

static uint8_t get_short_space(void *buffer) {
	(void)buffer;

	if(state) {
		int32_t time = counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_SHORT)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

static uint8_t get_short_pulse(void *buffer) {
	(void)buffer;

	if(!state) {
		int32_t time = counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_SHORT)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

static uint8_t get_long_space(void *buffer) {
	(void)buffer;

	if(state) {
		int32_t time = counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_LONG)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

static uint8_t get_long_pulse(void *buffer) {
	(void)buffer;

	if(!state) {
		int32_t time = counter*RC5_TIME_PRESCALER;

		if(abs(time - RC5_TIME_LONG)<=RC5_TIME_TOLERANCE)
			return 1;
	}

	return 0;
}

void rc5_init() {

	FiniteStateMachine_Init(&fsm, NULL);

	// state definition
	FiniteStateMachine_DefineState(&fsm, RC5_STATE_START1,	NULL,	NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, RC5_STATE_MID1,	&emit1, NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, RC5_STATE_START0,	NULL,	NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, RC5_STATE_MID0,	&emit0, NULL, NULL);
	FiniteStateMachine_DefineState(&fsm, RC5_STATE_RESET,	&reset, NULL, NULL);

	// transition definition from RC5 graph and reset transition
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_START1,	RC5_STATE_MID1,		0,	NULL, &get_short_space);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_MID1,	RC5_STATE_START1,	0,	NULL, &get_short_pulse);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_MID1,	RC5_STATE_MID0,		0,	NULL, &get_long_pulse);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_MID0,	RC5_STATE_MID1,		0,	NULL, &get_long_space);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_MID0,	RC5_STATE_START0,	0,	NULL, &get_short_space);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_START0,	RC5_STATE_MID0,		0,	NULL, &get_short_pulse);
	FiniteStateMachine_DefineTransition(&fsm, RC5_STATE_RESET,	RC5_STATE_MID1,		0,	NULL, NULL);

	FiniteStateMachine_Start(&fsm, RC5_STATE_RESET);

	// TIM7 for timeout interrupt
	RCC->APB1ENR |=RCC_APB1ENR_TIM7EN;
	TIM7->ARR = 65535;
	TIM7->PSC = 83;
	TIM7->DIER |=TIM_DIER_UIE;
    TIM7->CR1 |=TIM_CR1_CEN;

	NVIC_SetPriority(TIM7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(TIM7_IRQn);

	// PC13 -> receiver out
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &=~(3<<GPIO_MODER_MODE13_Pos);

	// EXTI13 -> PC13
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] |=(2<<SYSCFG_EXTICR4_EXTI13_Pos);

	EXTI->IMR |=EXTI_IMR_IM13;
	EXTI->RTSR |=EXTI_RTSR_TR13;
	EXTI->FTSR |=EXTI_FTSR_TR13;

	NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

uint8_t rc5_get_message(rc5_message_t *msg) {
	if(bits_ready!=14)
		return 0;

	*msg = message;

	FiniteStateMachine_Start(&fsm, RC5_STATE_RESET);

	return 1;
}

void TIM7_IRQHandler() {
	if(TIM7->SR & TIM_SR_UIF) {
		TIM7->SR &=~TIM_SR_UIF;

		FiniteStateMachine_Start(&fsm, RC5_STATE_RESET);

		TIM7->CR1 &=~TIM_CR1_CEN;
	}
}

void EXTI15_10_IRQHandler() {
	if(EXTI->PR & EXTI_PR_PR13) {
		EXTI->PR |=EXTI_PR_PR13;

		state = !(GPIOC->IDR & GPIO_IDR_ID13);
		counter = TIM7->CNT;

		FiniteStateMachine_Update(&fsm);

		if(bits_ready==2 && message.start!=3)
			FiniteStateMachine_Start(&fsm, RC5_STATE_RESET);
			
		TIM7->CNT = 0;
		TIM7->CR1 |=TIM_CR1_CEN;
	}
}

