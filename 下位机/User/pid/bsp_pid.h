#ifndef __BSP_PID_H
#define	__BSP_PID_H
#include "stm32f1xx.h"
#include "./usart/bsp_debug_usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct{
	float (*PID_realize)(float);	
}pid_realize;

typedef struct
{
	float target_val,Starget_val;     //目标值
	float actual_val,Sactual_val;     //实际值
	float err,Serr;            //定义当前偏差值
	float err_next,Serr_next;       //定义下一个偏差值
	float err_last,Serr_last;       //定义最后一个偏差值
	float Kp, Ki, Kd,SKp,SKi,SKd;     //定义比例、积分、微分系数
	uint32_t Mode;//控制模式(0x55)，位置控制or速度控制(0xAA)
}_pid;

extern void PID_param_init(void);
extern void set_pid_target(float temp_val);
extern float get_pid_target(void);
extern void set_p_i_d(float p, float i, float d);
void set_control_mode(uint32_t mode);
extern float PID_realize(float actual_val,float (*PIDRealize)(float));
extern void time_period_fun(void);
extern float W_PID_realize(float actual_val);
extern float S_PID_realize(float actual_val);
#endif
