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
	float target_val,Starget_val;     //Ŀ��ֵ
	float actual_val,Sactual_val;     //ʵ��ֵ
	float err,Serr;            //���嵱ǰƫ��ֵ
	float err_next,Serr_next;       //������һ��ƫ��ֵ
	float err_last,Serr_last;       //�������һ��ƫ��ֵ
	float Kp, Ki, Kd,SKp,SKi,SKd;     //������������֡�΢��ϵ��
	uint32_t Mode;//����ģʽ(0x55)��λ�ÿ���or�ٶȿ���(0xAA)
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
