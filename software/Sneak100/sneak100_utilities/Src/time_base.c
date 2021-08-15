/*
 * time_base.c
 *
 *  Created on: Aug 15, 2021
 *      Author: ermoz
 */

#include "time_base.h"

void TimeBase_Init(TimeBase_StructTypeDef *tbase, TIM_HandleTypeDef *htim) {
	tbase->timer = htim;

	tbase->time_start = __HAL_TIM_GetCounter(tbase->timer);
}

void TimeBase_Start(TimeBase_StructTypeDef *tbase) {
	tbase->time_start = __HAL_TIM_GetCounter(tbase->timer);
}

uint32_t TimeBase_Restart(TimeBase_StructTypeDef *tbase) {
	uint32_t time_elapsed = __HAL_TIM_GetCounter(tbase->timer) - tbase->time_start;

	tbase->time_start = __HAL_TIM_GetCounter(tbase->timer);

	return time_elapsed;
}

uint32_t TimeBase_GetTimeElapsed(TimeBase_StructTypeDef *tbase) {
	return __HAL_TIM_GetCounter(tbase->timer) - tbase->time_start;
}

float TimeBase_GetScale(TimeBase_StructTypeDef *tbase) {
	uint32_t PCS = tbase->timer->Instance->PSC;
	uint32_t HCLK = HAL_RCC_GetHCLKFreq();

	return (float)(PCS+1)/HCLK;
}
