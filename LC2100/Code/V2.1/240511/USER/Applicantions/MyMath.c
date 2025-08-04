#include "MyMath.h"

/*
*****************************************************************
 * 函数原型：float My_Sqrt(float number)
 * 功    能：快速计算开根号的倒数
 * 输    入：被开方数，长整型
 * 输    出：开方结果，整型
 * 参    数：float number
*****************************************************************
*/
float My_Sqrt(float number)
{
	long i;
	float x, y;
	const float f = 1.5F;
	x = number * 0.5F;
	y = number;
	i = * ( long * ) &y;
	i = 0x5f3759df - ( i >> 1 );

	y = * ( float * ) &i;
	y = y * ( f - ( x * y * y ) );
	y = y * ( f - ( x * y * y ) );
	return number * y;
}
