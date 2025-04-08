#include "Drv_Beep.h"

/**********全局变量**********/
float Beep_Time;  // 蜂鸣器响的时间
float Beep_Flash; // 蜂鸣器响的次数

/**
 * @brief 蜂鸣器的状态检测
 *
 * @param dT 任务周期
 */
void Buzzer_Status(float dT)
{
    static float BT;
    if (Beep_Time <= 0 && Beep_Flash <= 0) // 蜂鸣器的时间小于等于0时
    {
        Beep_OFF; // 关闭蜂鸣器
        return;
    }
    if (Beep_Time)
    {
        Beep_ON;         // 打开蜂鸣器
        Beep_Time -= dT; // 蜂鸣器响的时间--
    }
    if (Beep_Flash)
    {
        BT = BT + dT; // 周期++
        if (BT < 0.2) // 如果小于0.2s时
        {
            Beep_ON; // 蜂鸣器响
        }
        else if (BT >= 0.2 && BT < 0.3) // 在0.2和0.3s之间时
        {
            Beep_OFF; // 关闭蜂鸣器
        }
        else if (BT >= 0.3) // 大于等于0.3时
        {
            Beep_Flash--; // 次数--
            BT = 0;       // 周期清零
        }
    }
}
