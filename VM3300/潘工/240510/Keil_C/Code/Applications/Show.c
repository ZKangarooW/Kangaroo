#include "Show.h"

/**
 * @brief 4位数码管显示
 *
 * @param Num 整数
 */
void DisplayNumber_4BitDig(uint16_t Num)
{
	uint16_t Numb;
	Numb = Num+10000;
	
	if(Num<10)
		SCD_NT_Display(0x0A,0x0A,0x0A,Num%10);
	else if(Num<100)
		SCD_NT_Display(0x0A,0x0A,Num/10%10,Num%10);
	else if(Num<1000)
		SCD_NT_Display(0x0A,Num/100%10,Num/10%10,Num%10);
	else
		SCD_NT_Display(Numb/1000%10,Num/100%10,Num/10%10,Num%10);
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
	DisplayNumber_4BitDig(Speed.Set);
}
