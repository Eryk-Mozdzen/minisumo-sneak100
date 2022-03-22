#include "pid.h"

void PID_Init(PID_StructTypeDef *pid, float Kp, float Ki, float Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    PID_Reset(pid);
}

void PID_Reset(PID_StructTypeDef *pid) {
    pid->integral = 0;
    pid->prev_error = 0;
}

float PID_Update(PID_StructTypeDef *pid, float curr_process_value, float set_value) {
    pid->error = curr_process_value - set_value;
    pid->derivative = pid->error - pid->prev_error;
    pid->integral +=pid->error;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->integral + pid->Kd * pid->derivative;

    pid->prev_error = pid->error;

    return pid->output;
}
