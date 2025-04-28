#include "Drv_Beep.h"

/**********全局变量**********/
float Beep_Time;//蜂鸣器响的时间
float Beep_Flash;//蜂鸣器响的次数

/*
*****************************************************************
 * 函数原型： void Drv_BUZZER_Init(void)
 * 功    能： 蜂鸣器驱动初始化
*****************************************************************
*/
void Drv_BUZZER_Init(void)
{
	/*
	(1)配置蜂鸣器时钟
	*/
	BUZ_ConfigBuzzer(BUZ_CKS_32,188);			//Fsys=48Mhz，Fbuz = Fsys/(2*16*150) =4khz
	/*
	(2)配置蜂鸣器输出IO
	*/	
	GPIO_SET_MUX_MODE(P06CFG,GPIO_P06_MUX_BUZZ);
		
	/*
	(3)关闭蜂鸣器时钟
	*/	
	BUZ_EnableBuzzer();	
}

/*
*****************************************************************
 * 函数原型： void Buzzer_Status(float dT)
 * 功    能： 蜂鸣器的状态检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Buzzer_Status(float dT)
{
    static float BT;
    if(Beep_Time <= 0 && Beep_Flash <= 0)//蜂鸣器的时间小于等于0时
    {
        Beep_OFF;//关闭蜂鸣器
        return;
    }
    if(Beep_Time)
    {
        Beep_ON;//打开蜂鸣器
        Beep_Time -= dT;//蜂鸣器响的时间--
    }
    
    if(Beep_Flash)
    {
        BT =  BT + dT;//周期++
        if(BT < 0.2)//如果小于0.2s时
        {
            Beep_ON;//蜂鸣器响
        }
        else if(BT >= 0.2 && BT < 0.3)//在0.2和0.3s之间时
        {
            Beep_OFF;//关闭蜂鸣器
        }
        else if(BT >= 0.3)//大于等于0.2s时
        {
            Beep_Flash--;//次数--
            BT = 0;//周期清零
        }
    }
}
