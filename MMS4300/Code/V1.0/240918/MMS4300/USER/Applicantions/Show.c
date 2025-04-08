#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{

}

uint8_t seg[62] = {0};
/**
 * @brief 位数计算
 *
 * @param *bit 输入的位数
 * @param num 与等于的数
 * @param num1 或等于的数
 */
void bit_Cal(uint8_t bit,uint8_t num,uint8_t num1)
{
    seg[bit] &= (0xFF-num);seg[bit] |= num1;
}

void Display_IC1(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字
    
    bit_Cal(0, 0xff, 0xff);
    bit_Cal(1, 0xff, 0xff);
    /**********数据发送**********/
    for(uint8_t i=0;i<31;i++)
    {
        Write_Addr_Dat_N(IC1, i*2, seg[i], 1);
    }
}

void Display_IC2(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字
    
    /**********数据发送**********/
    for(uint8_t i=0;i<31;i++)
    {
        Write_Addr_Dat_N(IC2, i*2, seg[i+31], 1);
    }
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
    Display_IC2(Work_Num);
    Display_IC1(Work_Num);
}
