#include "pid.h"

void PID_Init(PID_StructTypeDef *pid, float Kp, float Ki, float Kd, float integral_band) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->integral_band = integral_band;

    TimeBase_Init(&pid->tbase);
    PID_Reset(pid);
}

void PID_Reset(PID_StructTypeDef *pid) {
    pid->integral = 0;
    pid->prev_process_value = 0;

    TimeBase_Start(&pid->tbase);
}

float PID_Update(PID_StructTypeDef *pid, float curr_process_value, float set_value) {
	pid->delta_time = TimeBase_GetScale(&pid->tbase) * TimeBase_Restart(&pid->tbase);

    pid->error = set_value - curr_process_value;
    pid->derivative = (curr_process_value - pid->prev_process_value)/pid->delta_time;

    if(abs(pid->error)<pid->integral_band)
    	pid->integral +=pid->error;
    else
    	pid->integral = 0;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + pid->Kd * pid->derivative;

    pid->prev_process_value = curr_process_value;

    return pid->output;
}
