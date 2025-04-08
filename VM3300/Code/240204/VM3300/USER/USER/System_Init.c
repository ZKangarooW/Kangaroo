#include "System_Init.h"

/**
 * @brief 系统驱动初始化
 *
 */
void System_Init(void)
{
    /**********系统初始化开始**********/
    sys.Init_ok = 0;

	/**********TM1650初始化************/
//	TM1650_Init();
//	TM1650_All();
	
    /**********开机蜂鸣器响***********/
    Beep_Time = 0.1f;
	
    /**********系统初始化成功**********/
    sys.Init_ok = 1;
}
