#include "Calibration.h"

void Calibration_Init(void)
{
    if(PT_VALUE_1_TEMP[0]>990 && PT_VALUE_1_TEMP[0]<1010 && PT_VALUE_1_TEMP[1]>990 && PT_VALUE_1_TEMP[1]<1010
    && PT_VALUE_1_TEMP[2]>990 && PT_VALUE_1_TEMP[2]<1010 && PT_VALUE_1_TEMP[3]>990 && PT_VALUE_1_TEMP[3]<1010 && Param.Calibration == 0) 
    {
        Calibration.Switch = 1;//如果开机按住P和Menu按键就打开校准
        Beep_Time = 1.0f;
    }
    
    if(PT_VALUE_1_TEMP[0]>990 && PT_VALUE_1_TEMP[0]<1010 && PT_VALUE_1_TEMP[1]>990 && PT_VALUE_1_TEMP[1]<1010
    && PT_VALUE_1_TEMP[2]>990 && PT_VALUE_1_TEMP[2]<1010 && PT_VALUE_1_TEMP[3]>990 && PT_VALUE_1_TEMP[3]<1010 &&HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)
    {
        Calibration.Switch = 1;//如果开机按住P和Menu按键就打开校准
        Param.Calibration = 0;
        Param.Correct[0] = 1000.0f;
        Param.Correct[1] = 1000.0f;
        Param.Correct[2] = 1000.0f;
        Param.Correct[3] = 1000.0f;
        Beep_Time = 1.0f;
    }
}

uint8_t sum_cnt[4];
#define OFFSET_AV_NUM 50//滤波50次
float sum_temp[4];
void Calibration_Temp(float dT)
{
    static uint8_t v;
    if(Calibration.Switch && Beep_Time<= 0)
    {
        sum_cnt[v]++;
        sum_temp[v] += PT_VALUE_1_TEMP[v];
        
        if(sum_cnt[v] >= OFFSET_AV_NUM)//假如大于滤波次数
        {
            Param.Correct[v] = sum_temp[v]/OFFSET_AV_NUM;
            sum_temp[v] = 0;
            sum_cnt[v] = 0;
            v++;
            if(v>3)
            {
                Param.Calibration = 1;
                Calibration.Switch = 0;
                Beep_Flash = 5;
                Save_Param_En = 1;//保存
            }
        }
    }
}

/**
 * @brief 校准任务
 * 
 */
void Calibration_Task(void *p)
{
    while(1)
    {
        Calibration_Temp(0.05f);
        vTaskDelay(50);
    }
}
