#include "Drv_Infrared.h"

/**********结构体************/
_Infrared_ Infrared[2];

/**
 * @brief 红外驱动初始化
 *
 */
void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道一 PA6左手边
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道二 PA7右手边
	
    
    HAL_TIM_Base_Start_IT(&htim15);
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);//开启tim15通道1的捕获（中断方式）PA2右手边
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);//开启tim15通道2的捕获（中断方式）PA3左手边
}

/**
 * @brief 定时器更新（溢出）中断回调函数
 *
 */
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM15)
    {
//        if(Infrared[0].IRSta&0x80)//上次有数据被接收到了
//        {	
//            Infrared[0].IRSta&=~0X10;//取消上升沿已经被捕获标记
//            if((Infrared[0].IRSta&0X0F)==0X00)
//            {
//                Infrared[0].IRSta|=1<<6;//标记已经完成一次按键的键值信息采集
//            }
//            if((Infrared[0].IRSta&0X0F)<14)
//            {
//                Infrared[0].IRSta++;
//            }
//			else
//			{
//				Infrared[0].IRSta &= ~(1<<7);//清空引导标识
//				Infrared[0].IRSta &= 0XF0;	//清空计数器	
//			}						 	   	
//		}	
        if(Infrared[1].IRSta&0x80)//上次有数据被接收到了
        {	
            Infrared[1].IRSta&=~0X10;//取消上升沿已经被捕获标记
            if((Infrared[1].IRSta&0X0F)==0X00)
            {
                Infrared[1].IRSta|=1<<6;//标记已经完成一次按键的键值信息采集
            }
            if((Infrared[1].IRSta&0X0F)<14)
            {
                Infrared[1].IRSta++;
            }
			else
			{
				Infrared[1].IRSta &= ~(1<<7);//清空引导标识
				Infrared[1].IRSta &= 0XF0;	//清空计数器	
			}						 	   	
		}	
    }
}

/**
 * @brief 红外检测信号变化定时器捕获
 *
 */
uint8_t cntt;
uint16_t data1[100];
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
//		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//		{
//			if(IR2_IN)//上升沿捕获
//            {
//                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//一定要先清除原来的设置！！
//                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//CC1P=1 设置为下降沿捕获
//                __HAL_TIM_SET_COUNTER(&htim15,0);//清空定时器值   	  
//                Infrared[0].IRSta|=0X10;//标记上升沿已经被捕获
//            }
//            else//下降沿捕获
//            {
//                Infrared[0].Dval=HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);//读取CCR1也可以清CC1IF标志位
//                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1);//一定要先清除原来的设置！！
//                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
//                if(Infrared[0].IRSta&0X10)//完成一次高电平捕获 
//                {
//                    if(Infrared[0].IRSta&0X80)//接收到了引导码
//                    {
//                        if(Infrared[0].Dval > NEC_ZERO_MIN && Infrared[0].Dval < NEC_ZERO_MAX)//560为标准值,560us
//                        {
//                            Infrared[0].IRRec >>= 1;/* 右移一位. */
//                            Infrared[0].IRRec &= ~0x80000000;/* 接收到0 */                                
//                        }
//                        else if(Infrared[0].Dval > NEC_ONE_MIN && Infrared[0].Dval < NEC_ONE_MAX)	//1680为标准值,1680us
//                        {
//                            Infrared[0].IRRec >>= 1;/* 右移一位 */
//                            Infrared[0].IRRec |= 0x80000000;/* 接收到1 */  
//                        }
//                        else if(Infrared[0].Dval > NEC_CONTINUE_MIN && Infrared[0].Dval < NEC_CONTINUE_MAX )	//得到按键键值增加的信息 2500为标准值2.5ms
//                        {
//                            Infrared[0].IRCnt++;//按键次数增加1次
//                            Infrared[0].IRSta&=0XF0;//清空计时器                                 
//                        }
//                    }
//                    else if(Infrared[0].Dval > NEC_HEAD_MIN && Infrared[0].Dval < NEC_HEAD_MAX)//4500为标准值4.5ms
//                    {
//                        Infrared[0].IRSta|=1<<7;//标记成功接收到了引导码
//                        Infrared[0].IRCnt=0;//清除按键次数计数器  
//                    }						 
//                }
//                Infrared[0].IRSta&=~(1<<4);
//            }				 		     	    
//		}
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(IR1_IN)//上升沿捕获
            {
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//一定要先清除原来的设置！！
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);//CC1P=1 设置为下降沿捕获
                __HAL_TIM_SET_COUNTER(&htim15,0);//清空定时器值   	  
                Infrared[1].IRSta|=0X10;//标记上升沿已经被捕获
            }
            else//下降沿捕获
            {
                Infrared[1].Dval=HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);//读取CCR1也可以清CC1IF标志位
                TIM_RESET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2);//一定要先清除原来的设置！！
                TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
                if(Infrared[1].IRSta&0X10)//完成一次高电平捕获 
                {
                    if(Infrared[1].IRSta&0X80)//接收到了引导码
                    {
                        if(Infrared[1].Dval > NEC_ZERO_MIN && Infrared[1].Dval < NEC_ZERO_MAX)//560为标准值,560us
                        {
                            Infrared[1].IRRec >>= 1;/* 右移一位. */
                            Infrared[1].IRRec &= ~0x80000000;/* 接收到0 */  
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;                               
                        }
                        else if(Infrared[1].Dval > NEC_ONE_MIN && Infrared[1].Dval < NEC_ONE_MAX)	//1680为标准值,1680us
                        {
                            Infrared[1].IRRec >>= 1;/* 右移一位 */
                            Infrared[1].IRRec |= 0x80000000;/* 接收到1 */
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;   
                        }
                        else if(Infrared[1].Dval > NEC_CONTINUE_MIN && Infrared[1].Dval < NEC_CONTINUE_MAX )	//得到按键键值增加的信息 2500为标准值2.5ms
                        {
                            Infrared[1].IRCnt++;//按键次数增加1次
                            Infrared[1].IRSta&=0XF0;//清空计时器    
                            data1[cntt] = Infrared[1].Dval;
                            cntt++;                               
                        }
                    }
                    else if(Infrared[1].Dval > NEC_HEAD_MIN && Infrared[1].Dval < NEC_HEAD_MAX)//4500为标准值4.5ms
                    {
                        Infrared[1].IRSta|=1<<7;//标记成功接收到了引导码
                        Infrared[1].IRCnt=0;//清除按键次数计数器
                         cntt = 0;
                        data1[cntt] = Infrared[1].Dval;
                            cntt++;   
                    }						 
                }
                Infrared[1].IRSta&=~(1<<4);
            }				 		     	    
		}
	}
}

//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
uint8_t Remote_Scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2;
	if(Infrared[1].IRSta&(1 << 6))//得到一个按键的所有信息了
	{ 
        t1 = Infrared[1].IRRec;/* 得到地址码 */
        t2 = (Infrared[1].IRRec >> 8) & 0xff;/* 得到地址反码 */
        if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID)   
        {   
            /* 检验遥控识别码(ID)及地址 */
            t1 = (Infrared[1].IRRec >> 16) & 0xff;
            t2 = (Infrared[1].IRRec >> 24) & 0xff;
            if (t1 == (uint8_t)~t2)
            {
                sta = t1;/* 键值正确 */
            }
        }

        if ((sta == 0) || ((Infrared[1].IRSta & 0X80) == 0)) 
        {   /* 按键数据错误/遥控已经没有按下了 */
            Infrared[1].IRSta &= ~(1 << 6);/* 清除接收到有效按键标识 */
            Infrared[1].IRCnt = 0;/* 清除按键次数计数器 */
        }
	}  
    return sta;
}
uint8_t  key;
uint8_t calaa;
uint8_t falg_ren;
void NEC_GetValue(float dT,uint8_t *addr, uint16_t *value)
{
    static float T;
    key=Remote_Scan();	
    if(key)
    {
        if(key == 0x98)
        {
            falg_ren = 1;
        }
    }
    
    
    if(falg_ren  == 1)
    {
        T += dT;
        if(key == 0x98)
        {
            calaa = 100;
            T = 0;
        }
        if(T >= 3.0f)
        { 
            calaa = 0;
            falg_ren = 0;
            T = 0;
        }
    }
//	uint8_t t1, t2;
//	*addr = 0;
//	*value = 0;
//	if (Infrared[0].RecFlag == 0x01)    //接收到一个数据
//	{
//		Infrared[0].RecFlag = 0x00;
//		t1 = Infrared[0].RmtRec >> 24;             //得到地址码
//		t2 = (Infrared[0].RmtRec >> 16) & 0xff;    //得到地址反码
//		if (t1 == (uint8_t)~t2)             //检验遥控识别码(ID)及地址
//		{
//			*addr = t1;
//			t1 = 0;
//			t2 = 0;
//		}
//		else
//		{*addr = 0; }
//		t1 = (Infrared[0].RmtRec >> 8) & 0xff;  //得到数据
//		t2 = Infrared[0].RmtRec & 0xff;         //得到数据反码
//		if (t1 == (uint8_t)~t2)           //检验数据码及数据反码
//		{*value = t1;}
//		else
//		{*value = 0; }
//		Infrared[0].RmtRec = 0;
//	}
}

//一个逻辑0的传输需要 1.125ms（560us载波+560us空闲）。
static void NEC_Send_0(void)
{
	Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(560);
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(560);
}
//一个逻辑1传输需要2.25ms（560us载波+1680us空闲）
static void NEC_Send_1(void)
{
	Infrared_Send1 = 52;
    Infrared_Send2 = 52;
	Delay_us(560);
	Infrared_Send1 = 0;
    Infrared_Send2 = 0;
	Delay_us(1680);
 
}
//NEC协议格式：//引导码：发送一个9ms载波的引导码，之后是4.5ms的空闲，
static void NEC_Send_Head(void)
{
    Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(9000);        //  实际10.56ms    10us实际13us
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(4500);          // 实际接收时间在5.24ms
 
}
//结束码(自己加的)
static void NEC_Send_Tail(void)
{
 
	Infrared_Send1 = 52;
//    Infrared_Send2 = 52;
	Delay_us(200);
	Infrared_Send1 = 0;
//    Infrared_Send2 = 0;
	Delay_us(3000);    //   2.5<3ms<3.3ms
 
}

//发送一字节数据
static void NEC_Send_BYTE(uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (value & 0x80)
		{
			NEC_Send_1();
		}
		else
		{
			NEC_Send_0();
		}
		value <<= 1;
	}
}


static void NEC_Send_Repeat(uint8_t count)
{
	uint8_t i = 0;
 
	if (count == 0)          //如果没有重复码就直接设置无载波，发射管进行空闲状态
	{
		NEC_Send_Tail();
	}
	else
	{
		for (i = 0; i < count; i++)
		{
			CARRIER_38KHz();
			Delay_us(9000);
			NO_CARRIER();
			Delay_us(2250);
		}
 
	}
}


//后发送16位地址码（18ms36ms）、8位数据码（9ms18ms）以及8为数据反码。
//（第二个108ms）如果接下来发射重复的数据，可以先发送9ms载波，空闲2.5ms,
//再发射0.56ms载波即可，注意每次发射的间隔时间。
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt)
{
	NEC_Send_Head();                //发送起始码
	NEC_Send_BYTE(addr);            //发送地址码H
	NEC_Send_BYTE(~addr);           //发送地址码L
	NEC_Send_BYTE(value);           //发送命令码H
	NEC_Send_BYTE(~value);          //发送命令码L
	NEC_Send_Repeat(cnt);           //发送重复码
    Delay_us(3000);
//    Infrared_Send1 = 52;
//     Infrared_Send2 = 52;
//    Delay_us(9000);
//    Infrared_Send1 = 0;
//    Delay_us(2250);
//    Infrared_Send1 = 52;
//    Delay_us(100);
//    Infrared_Send1 = 0;
//    Delay_us(90000);
    
}

void Check_Infrared(float dT)
{
    uint16_t data[1];
    uint8_t addr[1];
    NEC_GetValue(dT,addr, data);
}
