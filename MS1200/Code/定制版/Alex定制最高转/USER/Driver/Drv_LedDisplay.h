#ifndef __DRV_LEDDISPLAY_H__
#define	__DRV_LEDDISPLAY_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void UCdata_Display(uint8_t uc);//UC数据判断控制引脚 
void DIGdata_Display(uint8_t DIG);//DIG数据判断控制引脚 
void DIGdata_Set(void);//1-4DIG引脚全部拉高

#endif
