#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param; // 原始数据

/**********全局变量声明******/
uint8_t Save_Param_En; // 保存标志位

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC5

/**
 * @brief 初始化硬件中的参数
 *
 */
void Param_Reset(void)
{
    Param.Flash_Check_Start = FLASH_CHECK_START;

    for (uint8_t i = 0; i <= 9; i++)
    {
        Param.P_Param[i][0] = 370;  // 温度
        Param.P_Param[i][1] = 1500; // 速度
        Param.P_Param[i][2] = 1800;// 时间
    }
    
    Param.type =1;//0是加热制冷，1是单加热
    
    if(Param.type)//单加热
    {
        Param.P_Param[1][0] = 370;  // 温度
        Param.P_Param[2][0] = 500;  // 温度
        Param.P_Param[3][0] = 750;  // 温度
        Param.P_Param[4][0] = 900;  // 温度
        Param.P_Param[5][0] = 1000;  // 温度
        Param.P_Param[1][1] = 0;  // 速度
        Param.P_Param[2][1] = 100; 
        Param.P_Param[3][1] = 1500;
        Param.P_Param[4][1] = 1500;
        Param.P_Param[5][1] = 1500;
    }
    else
    {
        Param.P_Param[1][0] = 160;  // 温度
        Param.P_Param[2][0] = 370;  // 温度
        Param.P_Param[3][0] = 500;  // 温度
        Param.P_Param[4][0] = 750;  // 温度
        Param.P_Param[5][0] = 900;  // 温度
        Param.P_Param[6][0] = 1000;  // 温度
        Param.P_Param[1][1] = 0;  // 速度
        Param.P_Param[2][1] = 100; 
        Param.P_Param[3][1] = 1500;
        Param.P_Param[4][1] = 1500;
        Param.P_Param[5][1] = 1500;
        Param.P_Param[6][1] = 1500;
    }
    
    Param.Calibration = 750;
    

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
        Temp.Set = Param.P_Param[PMode.Option][0];   // 将Flash中的温度赋值
        Speed.Set = Param.P_Param[PMode.Option][1];   // 将Flash中的速度赋值
        Time.Set = Param.P_Param[PMode.Option][2];    // 将Flash中的时间赋值
        Calibration.Deviation = Param.Calibration;//温度校准值
//        Calibration.Switch = 1;//如果开机按住P和Menu按键就打开校准
        SetOK_Flag = 1;
        Save_Param_En = 1;
    }
    else
    {
        Temp.Set = Param.P_Param[PMode.Option][0];  // 将Flash中的温度赋值
        Speed.Set = Param.P_Param[PMode.Option][1]; // 将Flash中的速度赋值
        Time.Set = Param.P_Param[PMode.Option][2];  // 将Flash中的时间赋值
        Calibration.Deviation = Param.Calibration;//温度校准值
        SetOK_Flag = 1;
    }
    
//    if(!Key3 && !Key4)
//	{
//		Param.type++;
//		if(Param.type > 1)
//			Param.type = 0;
//    }
    if(Param.type)//单加热
    {
        Temp.MIN = -1;
    }
    else
    {
         Temp.MIN = -51;
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
