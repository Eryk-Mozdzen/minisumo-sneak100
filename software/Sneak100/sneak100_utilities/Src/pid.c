#include "pid.h"

uint32_t __PID_GetTime(PID_StructTypeDef *pid) {
	return __HAL_TIM_GetCounter(pid->us_timer);
}
