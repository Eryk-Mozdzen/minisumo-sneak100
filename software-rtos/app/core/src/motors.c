#include "motors.h"

static arm_pid_instance_f32 pid[4] = {0};
static float vel_setpoint[4] = {0};
static float vel_curr[4] = {0};
static float pwr_ctrl[4] = {0};
static motors_control_type_t control = MOTORS_CLOSE_LOOP;

static float calculate_vel(const int32_t pos_curr, const int32_t pos_last) {
	const int32_t delta = motors_get_position_delta(pos_last, pos_curr);

	return (float)delta*MOTORS_PID_FREQ/MOTORS_ENCODER_CPR;
}

static void update(void *param) {
	(void)param;

	int32_t pos_last[4] = {0};
	int32_t pos_curr[4] = {0};

	motors_set_power(pwr_ctrl);

	while(1) {
		motors_get_position(pos_curr);

		vel_curr[0] = calculate_vel(pos_curr[0], pos_last[0]);
		vel_curr[1] = calculate_vel(pos_curr[1], pos_last[1]);
		vel_curr[2] = calculate_vel(pos_curr[2], pos_last[2]);
		vel_curr[3] = calculate_vel(pos_curr[3], pos_last[3]);

		if(control==MOTORS_CLOSE_LOOP) {
			pwr_ctrl[0] = -arm_pid_f32(&pid[0], vel_curr[0] - vel_setpoint[0]);
			pwr_ctrl[1] = -arm_pid_f32(&pid[1], vel_curr[1] - vel_setpoint[1]);
			pwr_ctrl[2] = -arm_pid_f32(&pid[2], vel_curr[2] - vel_setpoint[2]);
			pwr_ctrl[3] = -arm_pid_f32(&pid[3], vel_curr[3] - vel_setpoint[3]);

			motors_set_power(pwr_ctrl);
		}

		memcpy(pos_last, pos_curr, 4*sizeof(int32_t));

		vTaskDelay(1000/MOTORS_PID_FREQ);
	}
}

void motors_init() {

	for(uint8_t i=0; i<4; i++) {
		pid[i].Kp = MOTORS_PID_KP;
		pid[i].Ki = MOTORS_PID_KI;
		pid[i].Kd = MOTORS_PID_KD;
		arm_pid_init_f32(&pid[i], 1);
	}

	xTaskCreate(update, "pid update", 1024, NULL, 4, NULL);

	// PC6 -> RB IN1
    // PC7 -> RB IN2
	// PC8 -> RF IN1
    // PC9 -> RF IN2
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER |=(2<<GPIO_MODER_MODE6_Pos) | (2<<GPIO_MODER_MODE7_Pos) | (2<<GPIO_MODER_MODE8_Pos) | (2<<GPIO_MODER_MODE9_Pos);
    GPIOC->AFR[0] |=(3<<GPIO_AFRL_AFSEL6_Pos) | (3<<GPIO_AFRL_AFSEL7_Pos);
	GPIOC->AFR[1] |=(3<<GPIO_AFRH_AFSEL8_Pos) | (3<<GPIO_AFRH_AFSEL9_Pos);

    // TIM8 CH1 -> RB IN1
    // TIM8 CH2 -> RB IN2
	// TIM8 CH3 -> RF IN1
    // TIM8 CH4 -> RF IN2
    RCC->APB2ENR |=RCC_APB2ENR_TIM8EN;
    TIM8->ARR = 1000;
    TIM8->CCMR1 |=(6<<TIM_CCMR1_OC1M_Pos) | (6<<TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
	TIM8->CCMR2 |=(6<<TIM_CCMR2_OC3M_Pos) | (6<<TIM_CCMR2_OC4M_Pos) | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;
    TIM8->CCER |=TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
    TIM8->BDTR |=TIM_BDTR_MOE;
    TIM8->CR1 |=TIM_CR1_CEN;

	// PA10 -> LF IN1
    // PA11 -> LF IN2
	// PA8  -> LB IN1
    // PA9  -> LB IN2
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |=(2<<GPIO_MODER_MODE8_Pos) | (2<<GPIO_MODER_MODE9_Pos) | (2<<GPIO_MODER_MODE10_Pos) | (2<<GPIO_MODER_MODE11_Pos);
	GPIOA->AFR[1] |=(1<<GPIO_AFRH_AFSEL8_Pos) | (1<<GPIO_AFRH_AFSEL9_Pos) | (1<<GPIO_AFRH_AFSEL10_Pos) | (1<<GPIO_AFRH_AFSEL11_Pos);

    // TIM1 CH1 -> LB IN1
    // TIM1 CH2 -> LB IN2
	// TIM1 CH3 -> LF IN1
    // TIM1 CH4 -> LF IN2
    RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;
    TIM1->ARR = 1000;
    TIM1->CCMR1 |=(6<<TIM_CCMR1_OC1M_Pos) | (6<<TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
	TIM1->CCMR2 |=(6<<TIM_CCMR2_OC3M_Pos) | (6<<TIM_CCMR2_OC4M_Pos) | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;
    TIM1->CCER |=TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
    TIM1->BDTR |=TIM_BDTR_MOE;
    TIM1->CR1 |=TIM_CR1_CEN;

	// PA15 -> LF A
    // PB3  -> LF B
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |=(2<<GPIO_MODER_MODE15_Pos);
    GPIOA->AFR[1] |=(1<<GPIO_AFRH_AFSEL15_Pos);

	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |=(2<<GPIO_MODER_MODE3_Pos);
    GPIOB->AFR[0] |=(1<<GPIO_AFRL_AFSEL3_Pos);

    // TIM2 CH1 -> LF A
    // TIM2 CH2 -> LF B
    RCC->APB1ENR |=RCC_APB1ENR_TIM2EN;
    TIM2->ARR = 65535;
    TIM2->CCMR1 |=(1<<TIM_CCMR1_CC1S_Pos) | (1<<TIM_CCMR1_CC2S_Pos);
    TIM2->SMCR |=(3<<TIM_SMCR_SMS_Pos);
    TIM2->CR1 |=TIM_CR1_CEN;

	// PA0 -> RF A
    // PA1 -> RF B
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |=(2<<GPIO_MODER_MODE6_Pos) | (2<<GPIO_MODER_MODE7_Pos);
    GPIOB->AFR[0] |=(2<<GPIO_AFRL_AFSEL6_Pos) | (2<<GPIO_AFRL_AFSEL7_Pos);

    // TIM4 CH1 -> RF A
    // TIM4 CH2 -> RF B
    RCC->APB1ENR |=RCC_APB1ENR_TIM4EN;
    TIM4->ARR = 65535;
    TIM4->CCMR1 |=(1<<TIM_CCMR1_CC1S_Pos) | (1<<TIM_CCMR1_CC2S_Pos);
    TIM4->SMCR |=(3<<TIM_SMCR_SMS_Pos);
    TIM4->CR1 |=TIM_CR1_CEN;

	// PA0 -> RB A
    // PA1 -> RB B
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |=(2<<GPIO_MODER_MODE0_Pos) | (2<<GPIO_MODER_MODE1_Pos);
    GPIOA->AFR[0] |=(2<<GPIO_AFRL_AFSEL0_Pos) | (2<<GPIO_AFRL_AFSEL1_Pos);

    // TIM5 CH1 -> RB A
    // TIM5 CH2 -> RB B
    RCC->APB1ENR |=RCC_APB1ENR_TIM5EN;
    TIM5->ARR = 65535;
    TIM5->CCMR1 |=(1<<TIM_CCMR1_CC1S_Pos) | (1<<TIM_CCMR1_CC2S_Pos);
    TIM5->SMCR |=(3<<TIM_SMCR_SMS_Pos);
    TIM5->CR1 |=TIM_CR1_CEN;

	// PB4 -> LB A
    // PB5 -> LB B
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |=(2<<GPIO_MODER_MODE4_Pos) | (2<<GPIO_MODER_MODE5_Pos);
    GPIOB->AFR[0] |=(2<<GPIO_AFRL_AFSEL4_Pos) | (2<<GPIO_AFRL_AFSEL5_Pos);

    // TIM3 CH1 -> LB A
    // TIM3 CH2 -> LB B
    RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
    TIM3->ARR = 65535;
    TIM3->CCMR1 |=(1<<TIM_CCMR1_CC1S_Pos) | (1<<TIM_CCMR1_CC2S_Pos);
    TIM3->SMCR |=(3<<TIM_SMCR_SMS_Pos);
    TIM3->CR1 |=TIM_CR1_CEN;
}

void motors_set_control_type(motors_control_type_t c) {
	control = c;

	arm_pid_reset_f32(&pid[0]);
	arm_pid_reset_f32(&pid[1]);
	arm_pid_reset_f32(&pid[2]);
	arm_pid_reset_f32(&pid[3]);
}

void motors_set_power(float *power) {

	for(uint8_t i=0; i<4; i++) {
		if(power[i]>1.f) {
			power[i] = 1.f;
		} else if(power[i]<-1.f) {
			power[i] = -1.f;
		}
	}
	
	memcpy(pwr_ctrl, power, 4*sizeof(float));

	if(power[0]>0.f) {
        TIM1->CCR3 = 0;
        TIM1->CCR4 = power[0]*TIM1->ARR;
    } else {
        TIM1->CCR3 = -power[0]*TIM1->ARR;
        TIM1->CCR4 = 0;
    }

	if(power[1]>0.f) {
        TIM8->CCR3 = 0;
        TIM8->CCR4 = power[1]*TIM8->ARR;
    } else {
        TIM8->CCR3 = -power[1]*TIM8->ARR;
        TIM8->CCR4 = 0;
    }

	if(power[2]>0.f) {
        TIM8->CCR1 = 0;
        TIM8->CCR2 = power[2]*TIM8->ARR;
    } else {
        TIM8->CCR1 = -power[2]*TIM8->ARR;
        TIM8->CCR2 = 0;
    }

	if(power[3]>0.f) {
        TIM1->CCR1 = 0;
        TIM1->CCR2 = power[3]*TIM1->ARR;
    } else {
        TIM1->CCR1 = -power[3]*TIM1->ARR;
        TIM1->CCR2 = 0;
    }
}

void motors_set_velocity(float *vel_sp) {
	vel_setpoint[0] = -vel_sp[0];
	vel_setpoint[1] = vel_sp[1];
	vel_setpoint[2] = vel_sp[2];
	vel_setpoint[3] = -vel_sp[3];
}

void motors_get_position(int32_t *pos_dest) {
	pos_dest[0] = TIM2->CNT;
	pos_dest[1] = TIM4->CNT;
	pos_dest[2] = TIM5->CNT;
	pos_dest[3] = TIM3->CNT;
}

void motors_get_velocity(float *vel_dest) {
	memcpy(vel_dest, vel_curr, 4*sizeof(float));
}

void motors_get_power(float *pwr_dest) {
	memcpy(pwr_dest, pwr_ctrl, 4*sizeof(float));
}

int32_t motors_get_position_delta(int32_t pos1, int32_t pos2) {
	int32_t delta = pos2 - pos1;

    if(delta>32768) {
		delta -=65536;
    } else if(delta<-32768) {
        delta +=65536;
	}

	return delta;
}