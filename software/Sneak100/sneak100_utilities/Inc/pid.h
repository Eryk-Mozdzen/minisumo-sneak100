#ifndef __PID_H__
#define __PID_H__

#include "tim.h"
#include <stdint.h>

typedef struct {
	TIM_HandleTypeDef *us_timer;
} PID_StructTypeDef;

uint32_t __PID_GetTime(PID_StructTypeDef *);

#endif
