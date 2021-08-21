#ifndef __PID_H__
#define __PID_H__

#include "tim.h"
#include "time_base.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    float Kp, Ki, Kd;
    float integral, prev_process_value;
    float integral_band;

    float delta_time, error, derivative, output;	// for debug

    TimeBase_StructTypeDef tbase;
} PID_StructTypeDef;

void PID_Init(PID_StructTypeDef *, TIM_HandleTypeDef *, float, float, float, float);
void PID_Reset(PID_StructTypeDef *);
float PID_Update(PID_StructTypeDef *, float, float);

#endif
