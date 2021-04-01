#include "./pid/bsp_pid.h"
#include ".\motor_control\bsp_motor_control.h"



//定义全局变量

_pid pid;


/**
  * @brief  PID参数初始化
	*	@note 	无
  * @retval 无
  */
void PID_param_init()
{
	/*位置控制初始化参数 */
	pid.target_val=CIRCLE_PULSES;				
	pid.actual_val=0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	pid.Kp = 5.2;
	pid.Ki = 0;
	pid.Kd = 5;
	
	/* 速度控制初始化参数 */
	pid.Starget_val=100;				
	pid.Sactual_val=0.0;
	pid.Serr = 0.0;
	pid.Serr_last = 0.0;
	pid.Serr_next = 0.0;
	pid.SKp = 6;
	pid.SKi = 2.5;
	pid.SKd = 0;
	
	//控制模式
	pid.Mode = 0x55; //位置控制

#if 1
	uint32_t i;
	for(i=100000;i>0;i--)
	{
		;
	}
    //float pid_temp[3] = {pid.Kp, pid.Ki, pid.Kd};
	uint32_t pid_temp[3] = {(uint32_t)(pid.Kp*10), (uint32_t)(pid.Ki*10), (uint32_t)(pid.Kd*10)};
    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // 给通道 1 发送 P I D 值
	for(i=100000;i>0;i--)
	{
		;
	}
	uint32_t Spid_temp[3] = {(uint32_t)(pid.SKp*10), (uint32_t)(pid.SKi*10), (uint32_t)(pid.SKd*10)};
    set_computer_value(SEND_S_P_I_D_CMD, CURVES_CH1, Spid_temp, 3);     // 给通道 1 发送 P I D 值
	for(i=100000;i>0;i--)
	{
		;
	}
	set_computer_value(SEND_MODE_CMD, CURVES_CH1,&(pid.Mode), 1);     // 给通道 1 发送PID控制模式
#endif
}

/**
  * @brief  设置目标值
  * @param  val		目标值
	*	@note 	无
  * @retval 无
  */
void set_pid_target(float temp_val)
{
	if(pid.Mode==0x55)
		pid.target_val = temp_val;    // 设置位置当前的目标值
	else if(pid.Mode==0xAA)
		pid.Starget_val = temp_val;    // 设置速度当前的目标值
}

/**
  * @brief  获取目标值
  * @param  无
	*	@note 	无
  * @retval 目标值
  */
float get_pid_target(void)
{
	float tar;
	if(pid.Mode==0x55)
	{
		tar = pid.target_val;    // 设置当前的目标值
	}
	else if(pid.Mode==0xAA)
	{
		tar = pid.Starget_val;    // 设置当前的目标值
	}
	return tar;
}

/**
  * @brief  设置比例、积分、微分系数
  * @param  p：比例系数 P
  * @param  i：积分系数 i
  * @param  d：微分系数 d
	*	@note 	无
  * @retval 无
  */
void set_p_i_d(float p, float i, float d)
{
	uint32_t mode;
	mode = pid.Mode;
	if(mode==0x55) //位置控制PID参数
	{
		pid.Kp = p;    // 设置比例系数 P
		pid.Ki = i;    // 设置积分系数 I
		pid.Kd = d;    // 设置微分系数 D
	}
	else if(mode==0xAA)//速度控制PID参数
	{
		pid.SKp = p;    // 设置比例系数 P
		pid.SKi = i;    // 设置积分系数 I
		pid.SKd = d;    // 设置微分系数 D
	}
}

/**
  * @brief  设置PID控制模式
  * @param  mode：控制模式
  * @note 	无
  * @retval 无
  */
void set_control_mode(uint32_t mode)
{
	pid.Mode = mode;    // 设置控制模式
}

/**
  * @brief  位置控制PID算法实现
  * @param  actual_val:实际值
  *	@note 	无
  * @retval 通过PID计算后的输出
  */
float W_PID_realize(float actual_val)
{
	/*计算目标值与实际值的误差*/
	pid.err=pid.target_val-actual_val;
	//printf("pid.err=%f\n",pid.err);
	if (pid.err > -5 && pid.err < 5)
	{
		pid.err = 0;
	}

	/*PID算法实现*/
	pid.actual_val += pid.Kp * (pid.err - pid.err_next) + 
					pid.Ki * pid.err + 
					pid.Kd * (pid.err - 2 * pid.err_next + pid.err_last);
	/*传递误差*/
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;

	/*返回当前实际值*/
	return pid.actual_val;
}

/**
  * @brief  速度PID算法实现
  * @param  actual_val:实际值
  *	@note 	无
  * @retval 通过PID计算后的输出
  */
float S_PID_realize(float actual_val)
{
	/*计算目标值与实际值的误差*/
	pid.Serr=pid.Starget_val-actual_val;
	/*PID算法实现*/
	pid.Sactual_val += pid.SKp*(pid.Serr - pid.Serr_next) 
				 + pid.SKi*pid.Serr 
                 + pid.SKd*(pid.Serr - 2 * pid.Serr_next + pid.Serr_last);
	/*传递误差*/
	pid.Serr_last = pid.Serr_next;
	pid.Serr_next = pid.Serr;
	/*返回当前实际值*/
	return pid.Sactual_val;
}

/**
 *@brief PID算法回调函数
 *@param actual_val:实际值
 *@param (*PIDRealize)(float) 具体PID算法函数，有位置控制、和速度控制
 *@return 通过PID计算后的输出 
 */

float PID_realize(float actual_val,float (*PIDRealize)(float))
{
	return ((*PIDRealize)(actual_val));
}

