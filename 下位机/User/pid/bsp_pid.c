#include "./pid/bsp_pid.h"
#include ".\motor_control\bsp_motor_control.h"



//����ȫ�ֱ���

_pid pid;


/**
  * @brief  PID������ʼ��
	*	@note 	��
  * @retval ��
  */
void PID_param_init()
{
	/*λ�ÿ��Ƴ�ʼ������ */
	pid.target_val=CIRCLE_PULSES;				
	pid.actual_val=0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	pid.Kp = 5.2;
	pid.Ki = 0;
	pid.Kd = 5;
	
	/* �ٶȿ��Ƴ�ʼ������ */
	pid.Starget_val=100;				
	pid.Sactual_val=0.0;
	pid.Serr = 0.0;
	pid.Serr_last = 0.0;
	pid.Serr_next = 0.0;
	pid.SKp = 6;
	pid.SKi = 2.5;
	pid.SKd = 0;
	
	//����ģʽ
	pid.Mode = 0x55; //λ�ÿ���

#if 1
	uint32_t i;
	for(i=100000;i>0;i--)
	{
		;
	}
    //float pid_temp[3] = {pid.Kp, pid.Ki, pid.Kd};
	uint32_t pid_temp[3] = {(uint32_t)(pid.Kp*10), (uint32_t)(pid.Ki*10), (uint32_t)(pid.Kd*10)};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // ��ͨ�� 1 ���� P I D ֵ
	for(i=100000;i>0;i--)
	{
		;
	}
	uint32_t Spid_temp[3] = {(uint32_t)(pid.SKp*10), (uint32_t)(pid.SKi*10), (uint32_t)(pid.SKd*10)};
    set_computer_value(SEND_S_P_I_D_CMD, CURVES_CH1, Spid_temp, 3);     // ��ͨ�� 1 ���� P I D ֵ
	for(i=100000;i>0;i--)
	{
		;
	}
	set_computer_value(SEND_MODE_CMD, CURVES_CH1,&(pid.Mode), 1);     // ��ͨ�� 1 ����PID����ģʽ
#endif
}

/**
  * @brief  ����Ŀ��ֵ
  * @param  val		Ŀ��ֵ
	*	@note 	��
  * @retval ��
  */
void set_pid_target(float temp_val)
{
	if(pid.Mode==0x55)
		pid.target_val = temp_val;    // ����λ�õ�ǰ��Ŀ��ֵ
	else if(pid.Mode==0xAA)
		pid.Starget_val = temp_val;    // �����ٶȵ�ǰ��Ŀ��ֵ
}

/**
  * @brief  ��ȡĿ��ֵ
  * @param  ��
	*	@note 	��
  * @retval Ŀ��ֵ
  */
float get_pid_target(void)
{
	float tar;
	if(pid.Mode==0x55)
	{
		tar = pid.target_val;    // ���õ�ǰ��Ŀ��ֵ
	}
	else if(pid.Mode==0xAA)
	{
		tar = pid.Starget_val;    // ���õ�ǰ��Ŀ��ֵ
	}
	return tar;
}

/**
  * @brief  ���ñ��������֡�΢��ϵ��
  * @param  p������ϵ�� P
  * @param  i������ϵ�� i
  * @param  d��΢��ϵ�� d
	*	@note 	��
  * @retval ��
  */
void set_p_i_d(float p, float i, float d)
{
	uint32_t mode;
	mode = pid.Mode;
	if(mode==0x55) //λ�ÿ���PID����
	{
		pid.Kp = p;    // ���ñ���ϵ�� P
		pid.Ki = i;    // ���û���ϵ�� I
		pid.Kd = d;    // ����΢��ϵ�� D
	}
	else if(mode==0xAA)//�ٶȿ���PID����
	{
		pid.SKp = p;    // ���ñ���ϵ�� P
		pid.SKi = i;    // ���û���ϵ�� I
		pid.SKd = d;    // ����΢��ϵ�� D
	}
}

/**
  * @brief  ����PID����ģʽ
  * @param  mode������ģʽ
  * @note 	��
  * @retval ��
  */
void set_control_mode(uint32_t mode)
{
	pid.Mode = mode;    // ���ÿ���ģʽ
}

/**
  * @brief  λ�ÿ���PID�㷨ʵ��
  * @param  actual_val:ʵ��ֵ
  *	@note 	��
  * @retval ͨ��PID���������
  */
float W_PID_realize(float actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pid.err=pid.target_val-actual_val;
	//printf("pid.err=%f\n",pid.err);
	if (pid.err > -5 && pid.err < 5)
	{
		pid.err = 0;
	}

	/*PID�㷨ʵ��*/
	pid.actual_val += pid.Kp * (pid.err - pid.err_next) + 
					pid.Ki * pid.err + 
					pid.Kd * (pid.err - 2 * pid.err_next + pid.err_last);
	/*�������*/
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;

	/*���ص�ǰʵ��ֵ*/
	return pid.actual_val;
}

/**
  * @brief  �ٶ�PID�㷨ʵ��
  * @param  actual_val:ʵ��ֵ
  *	@note 	��
  * @retval ͨ��PID���������
  */
float S_PID_realize(float actual_val)
{
	/*����Ŀ��ֵ��ʵ��ֵ�����*/
	pid.Serr=pid.Starget_val-actual_val;
	/*PID�㷨ʵ��*/
	pid.Sactual_val += pid.SKp*(pid.Serr - pid.Serr_next) 
				 + pid.SKi*pid.Serr 
                 + pid.SKd*(pid.Serr - 2 * pid.Serr_next + pid.Serr_last);
	/*�������*/
	pid.Serr_last = pid.Serr_next;
	pid.Serr_next = pid.Serr;
	/*���ص�ǰʵ��ֵ*/
	return pid.Sactual_val;
}

/**
 *@brief PID�㷨�ص�����
 *@param actual_val:ʵ��ֵ
 *@param (*PIDRealize)(float) ����PID�㷨��������λ�ÿ��ơ����ٶȿ���
 *@return ͨ��PID��������� 
 */

float PID_realize(float actual_val,float (*PIDRealize)(float))
{
	return ((*PIDRealize)(actual_val));
}

