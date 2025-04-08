#include "Drv_Infrared.h"

/**********结构体************/
_Infrared_ Infrared[2];

/**********局部变量声明*******/
uint32_t Infrared_Time;//发送的时间
uint8_t Infrared_Step;//发送的步骤

/**
 * @brief 红外驱动初始化
 *
 */
void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道一
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道二
	
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);   //开启tim15通道1的捕获（中断方式）
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);   //开启tim15通道2的捕获（中断方式）
	__HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);   //更新使能中断
	
	HAL_TIM_Base_Start_IT(&htim6);//开始定时器
}

///**
// * @brief 是否有人
// *
// * @param dT 任务周期
// */
//void Check_Infrared(float dT)
//{
//    Infrared[0].Someone_Time += dT;//每100ms进入
//	Infrared[1].Someone_Time += dT;//每100ms进入
//    if (Infrared[0].Someone_Time >= 0.5f)// 0.5s发现没出发输入捕获
//    {
//        Infrared[0].Someone = 0;// 将有人清零
//        Infrared[0].Someone_Time = 0;//计数清零
//    }
//	if (Infrared[1].Someone_Time >= 0.5f)// 0.5s发现没出发输入捕获
//    {
//        Infrared[1].Someone = 0;// 将有人清零
//        Infrared[1].Someone_Time = 0;//计数清零
//    }
//}

//void Delay_us(uint32_t us_cnt)
//{
//	TIM6->CNT = us_cnt - 1;
//	TIM6->CR1 |= TIM_CR1_CEN;
//	while ((TIM6->SR & TIM_FLAG_UPDATE) != SET);
//	TIM6->SR = (uint16_t)~TIM_FLAG_UPDATE;
//	TIM6->CR1 &= ~TIM_CR1_CEN;
//}

///**
// * @brief 定时器计数中断
// *
// */
//void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == htim6.Instance) 
//	{
//        
//	}
//}





/**
 * @brief 红外检测信号变化定时器捕获
 *
 */
uint16_t val1;
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(IR1_IN)//capture了上升沿
			{
				TIM_RESET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2);//清除捕获上升沿
				TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);//开始捕获下降沿
				__HAL_TIM_SET_COUNTER(&htim15, 0);//清空定时器值
				Infrared[0].IRSta |= 0x10;//[4]置1，即标志上升沿已捕获
			}
			else  //捕获下降沿
			{
				Infrared[0].Dval = HAL_TIM_ReadCapturedValue(&htim15, TIM_CHANNEL_2);//下降沿计数
				TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//清除捕获下降沿
				TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//开始捕获上升沿
				if(Infrared[0].IRSta & 0x10)  //如果完成了一次高电平捕获，接下来看是否有引导码
				{
                    if (Infrared[0].STA_Head == 0x01) //只有接收到了引导码之后得到的才是数据
                    {
                        if (Infrared[0].Dval > NEC_ZERO_MIN && Infrared[0].Dval < NEC_ZERO_MAX)  //560为标准值,560us min=392 max=728               实际值为0.68ms
                        {
                            //红外接收到的数据：0
                            Infrared[0].RmtRec <<= 1;                 //左移一位.
                            Infrared[0].RmtRec |= 0;                  //接收到0
                        }
                        else if (Infrared[0].Dval > NEC_ONE_MIN && Infrared[0].Dval < NEC_ONE_MAX)  //1680为标准值,1680us min=1.176ms max=2.148ms    实际值为1.96ms
                        {
                            //红外接收到的数据：1
                            Infrared[0].RmtRec <<= 1;                 //左移一位.
                            Infrared[0].RmtRec |= 1;                  //接收到1
             
                        }
                        else if (300 < Infrared[0].Dval && Infrared[0].Dval < 8800)//得到按键键值增加的信息 2500为标准值2.5ms
                        {
                            Infrared[0].RecFlag = 0x01;
                            Infrared[0].STA_Head = 0x00; //准备接受下一帧数据
                        }
                    }
                    else if (Infrared[0].Dval > NEC_HEAD_MIN && Infrared[0].Dval < NEC_HEAD_MAX)       //4500为标准值4.5ms  实测5773 //4500 -6300
                    {
                        Infrared[0].STA_Head = 0x01;  //标记成功接收到了引导码
											  //跳出去，等待下一个高电平
                    }
				}	
				Infrared[0].IRSta &=~(1<<4);//清空[4]，即高电平计数结束
			}
            
            
		}
	}
}

void NEC_GetValue(uint8_t *addr, uint16_t *value)
{
	uint8_t t1, t2;
	*addr = 0;
	*value = 0;
	if (Infrared[0].RecFlag == 0x01)    //接收到一个数据
	{
		Infrared[0].RecFlag = 0x00;
		t1 = Infrared[0].RmtRec >> 24;             //得到地址码
		t2 = (Infrared[0].RmtRec >> 16) & 0xff;    //得到地址反码
		if (t1 == (uint8_t)~t2)             //检验遥控识别码(ID)及地址
		{
			*addr = t1;
			t1 = 0;
			t2 = 0;
		}
		else
		{*addr = 0; }
		t1 = (Infrared[0].RmtRec >> 8) & 0xff;  //得到数据
		t2 = Infrared[0].RmtRec & 0xff;         //得到数据反码
		if (t1 == (uint8_t)~t2)           //检验数据码及数据反码
		{*value = t1;}
		else
		{*value = 0; }
		Infrared[0].RmtRec = 0;
	}
}

