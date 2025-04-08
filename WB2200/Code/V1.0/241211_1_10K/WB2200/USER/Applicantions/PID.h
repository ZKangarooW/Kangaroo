#ifndef __PID_H__
#define	__PID_H__

#include "include.h"

/**********宏定义************/
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/

void controlLoop(void);
#endif
