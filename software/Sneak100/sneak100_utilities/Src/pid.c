#include "pid.h"

void PID_Init(PID_StructTypeDef *pid, TIM_HandleTypeDef *htim, float Kp, float Ki, float Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    TimeBase_Init(&pid->tbase, htim);
    PID_Reset(pid);
}

void PID_Reset(PID_StructTypeDef *pid) {
    pid->intgral = 0;
    pid->prev_process_value = 0;

    TimeBase_Start(&pid->tbase);
}

float PID_Update(PID_StructTypeDef *pid, float curr_process_value, float set_value) {
	pid->delta_time = TimeBase_GetScale(&pid->tbase) * TimeBase_Restart(&pid->tbase);

    pid->error = curr_process_value - set_value;
    pid->derivative = (curr_process_value - pid->prev_process_value)/pid->delta_time;
    pid->intgral +=pid->error;

    return pid->Kp * pid->error + pid->Ki * pid->intgral + pid->Kd * pid->derivative;
}
