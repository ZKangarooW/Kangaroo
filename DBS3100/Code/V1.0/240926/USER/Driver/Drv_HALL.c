#include "Drv_HALL.h"

/**********全局变量声明*******/
uint8_t HALL1, HALL2; // 霍尔1和霍尔2的值

/**
* @brief 霍尔初始化。不然开机就是低模快，感应到高模块就变成800
 *
 */
void Drv_HALL_Init(void)
{
    HALL1 = Read_HALL1;
    HALL2 = Read_HALL2;
}

/**
 * @brief 霍尔检测,上电为1，磁铁接触为0
 *
 * @param dT 任务周期
 */
void Check_HALL(float dT)
{
    HALL1 = Read_HALL1;
    HALL2 = Read_HALL2;
}

/**
 * @brief 检测模块是否存在（预防启动的时候拿下模块）
 *
 * @param dT 任务周期
 */
void Check_Base(float dT)
{
//    if (sys.Run_Status == 1)
//    {
//        if (HALL1 && HALL2)
//        {
//            Temp.Base_Err = 1; // 模块没放，触发报警
//            Beep_Flash = 3;
//            sys.Run_Status = 2;
//            sys.SetMode_Option = 0;
//            Speed.ADDMode = 2;
//            SetOK_Flag = 1;
//            WIND_OFF;
//        }
//    }
}
