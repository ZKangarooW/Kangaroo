#include "Calibration.h"

_Calibration_ Calibration;//校准参数

uint8_t sum_cnt;
#define OFFSET_AV_NUM 50//滤波50次
float sum_temp;
void Calibration_Temp(float dT)
{
    if(Calibration.Switch && Beep_Time <= 0)
    {
        sum_cnt++;
        sum_temp += PT_VALUE_1_TEMP;
        
        if(sum_cnt >= OFFSET_AV_NUM)//假如大于滤波次数
        {
            Param.Correct = sum_temp/OFFSET_AV_NUM;
            sum_temp = 0;
            sum_cnt = 0;
            Calibration.Switch = 0;
            Beep_Flash = 5;
            Save_Param_En = 1;//保存
        }
    }
}
