#include "Drv_Sleep.h"

/**********全局变量**********/

/*
*****************************************************************
 * 函数原型：void Drv_Sleep_Init(void)
 * 功    能：Sleep驱动初始化
*****************************************************************
*/
void Drv_Sleep_Init(void)
{
    /*
	(1)设置EXTINT功能
	*/
	EXTINT_ConfigInt(EXTINT1, EXTINT_TRIG_FALLING);		//INT1 下降沿触发中断
	/*
	(2)设置EXTINT IO口
	*/	
    GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_7);
	GPIO_ENABLE_UP(P0UP, GPIO_PIN_7);				//开启P07上拉
	GPIO_SET_PS_MODE(PS_INT1, GPIO_P07_MUX_INT1);			//复用为INT1 输入功能
	/*
	(3)设置EXTINT中断
	*/		
	EXTINT_EnableInt(EXTINT1);
	IRQ_SET_PRIORITY(IRQ_INT1, IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();							 //开启总中断
    SYS_EnableWakeUp();//congfig可以设置休眠唤醒等待时间(WAKEUP_WAITTIME)
}


/*
*****************************************************************
 * 函数原型：void Check_Sleep(float dT)
 * 功    能：检测时间，进入休眠模式
*****************************************************************
*/
void Check_Sleep(float dT)
{
    static float T;
    if(sys.Run_Status)
    {
        T = 0;
    }
    else
    {
        T += dT;
        if(T>10.0f)
        {
            T = 0;
            LED1_OFF;//关闭灯
            LED2_OFF;//关闭灯
            SYS_EnterStop();
        }
    }
}
