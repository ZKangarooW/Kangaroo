#include "Drv_Remote.h"

uint8_t IRSta = 0; //接受状态，[0:3]溢出计数器，[4]标记上升沿是否已经被捕获,[5]保留，[6]得到了一个按键的全部信息,[7]收到了引导码标志
uint16_t Dval; //高电平计数器的值，根据此判断高低电平的时间
uint32_t IRData = 0;  //红外接收的数据
uint8_t keyCount =0;
uint8_t Remote_Flag;
/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
float cnt;
void Check_Remote(float dT)
{
    cnt += dT;      // 每50ms进入
    if (cnt >= 0.5f) // 0.5s发现没出发输入捕获
    {
        Remote_Flag = 0;      // 将速度清零
        cnt = 0; // 计数清零
    }
}
void Remote_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(IR_IN)			//capture了上升沿
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1);   //清除捕获上升沿
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING); //开始捕获下降沿
				__HAL_TIM_SET_COUNTER(&htim15, 0);  //清空定时器值
				IRSta |= 0x10;   //[4]置1，即标志上升沿已捕获
			}
			else  //捕获下降沿
			{
				Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_1);   //下降沿计数
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);   //清除捕获下降沿
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);  //开始捕获上升沿
				if(IRSta & 0x10)  //如果完成了一次高电平捕获，接下来看是否有引导码
				{
					if(Dval>2100 && Dval<2600)  //4.5ms高电平，引导码
					{
						Remote_Flag = 1;
						cnt = 0;
							IRSta &= 0xF0;  
					}
				}	
			IRSta &=~(1<<4); //清空[4]，即高电平计数结束
			}
		}
	}
}

void Drv_Remote_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);   //开启通道4的捕获（中断方式）
  __HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);   //更新使能中断
}
