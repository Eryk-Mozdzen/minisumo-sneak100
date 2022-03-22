#ifndef __PID_H__
#define __PID_H__

typedef struct {
    float Kp, Ki, Kd;
    float integral, prev_error;

    float error, derivative, output;	// for debug
} PID_StructTypeDef;

void PID_Init(PID_StructTypeDef *, float, float, float);
void PID_Reset(PID_StructTypeDef *);
float PID_Update(PID_StructTypeDef *, float, float);

#endif
