#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param; // 原始数据

/**********全局变量声明******/
uint8_t Save_Param_En; // 保存标志位

/**
 * @brief 初始化硬件中的参数
 *
 */
void Param_Reset(void)
{
    Param.Flash_Check_Start = FLASH_CHECK_START;

    Param.Speed = 3000; // 速度
    Param.Temp = 370;   // 温度
    Param.Time = 5;     // 时间

    Param.Flash_Check_End = FLASH_CHECK_END;
}

/**
 * @brief 保存硬件中的参数
 *
 */
void Param_Save(void)
{
    Flash_Write((uint8_t *)(&Param), sizeof(Param));
}

/**
 * @brief 读取硬件中的参数，判断是否更新
 *
 */
void Param_Read(void)
{
    Flash_Read((uint8_t *)(&Param), sizeof(Param));

    // 板子从未初始化
    if (Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END)
    {
        Param_Reset();
        Speed.Set = Param.Speed; // 将Flash中的速度赋值
        Temp.Set = Param.Temp;   // 将Flash中的温度赋值
        Time.Set = Param.Time;   // 将Flash中的时间赋值
        SetOK_Flag = 1;
        Save_Param_En = 1;
    }
    else
    {
        Speed.Set = Param.Speed; // 将Flash中的速度赋值
        Temp.Set = Param.Temp;   // 将Flash中的温度赋值
        Time.Set = Param.Time;   // 将Flash中的时间赋值
        SetOK_Flag = 1;
    }

    // 保存参数
    if (Save_Param_En)
    {
        Save_Param_En = 0;
        Param_Save();
    }
}

/**
 * @brief 保存标志位置1，0.5s后保存
 *
 * @param dT 任务周期
 */
void Param_Save_Overtime(float dT)
{
    static float time;
    if (Save_Param_En)
    {
        time += dT;

        if (time >= 0.5f)
        {
            Param_Save();
            Save_Param_En = 0;
        }
    }
    else
        time = 0;
}
