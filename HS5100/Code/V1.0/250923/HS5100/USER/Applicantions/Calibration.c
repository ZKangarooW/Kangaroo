#include "Calibration.h"

/**********结构体************/
_Calibration_ Calibration;//校准参数

/*
*****************************************************************
 * 函数原型：void Calibration_Init(void)
 * 功    能：开机进入校准的办法
*/
void Calibration_Init(void)
{
    // 条件1: 如果插入1kΩ探头(980-1020Ω范围内)且未校准过
    if(PT_VALUE_2_TEMP > 980 && PT_VALUE_2_TEMP < 1020 && Param.Calibration == 0)
    {
        Calibration.Switch = 1;    // 开启校准模式
        Beep_Time = 1.0f;          // 蜂鸣器提示1秒
    }
}

uint8_t sum_cnt[2];                // 采样计数数组 [0:1kΩ计数, 1:2kΩ计数]
#define OFFSET_AV_NUM 50           // 滑动平均滤波次数
float sum_temp[2];                 // 采样累加和数组 [0:1kΩ累加和, 1:2kΩ累加和]
/*
*****************************************************************
 * 函数名称：Calibration_Temp
 * 功能描述：温度校准处理函数
 * 输入参数：dT - 时间增量(秒)
 * 调用说明：需要在主循环中定期调用
*****************************************************************
*/
void Calibration_Temp(float dT)
{
    static uint8_t step;           // 校准步骤 (0:1kΩ校准, 1:2kΩ校准)
    
    // 检查是否处于校准模式且蜂鸣器提示已结束
    if(Calibration.Switch && Beep_Time <= 0)
    {
        // 步骤0: 1kΩ电阻校准
        if(step == 0 && PT_VALUE_2_TEMP > 980 && PT_VALUE_2_TEMP < 1020)
        {
            sum_cnt[step]++;                           // 增加采样计数
            sum_temp[step] += PT_VALUE_2_TEMP;         // 累加采样值
            
            // 达到指定采样次数后进行平均计算
            if(sum_cnt[step] >= OFFSET_AV_NUM)
            {
                Param.Correct[step] = sum_temp[step] / OFFSET_AV_NUM;  // 计算1kΩ平均值
                sum_temp[step] = 0;                    // 重置累加和
                sum_cnt[step] = 0;                     // 重置计数
                step++;                                // 进入下一步校准
                Beep_Flash = 3;                        // 蜂鸣器提示3声(提示更换电阻)
            }
        }
        // 步骤1: 2kΩ电阻校准
        else if(step == 1)
        {
            // 检查是否插入2kΩ电阻(1980-2020Ω范围内)
            if(step == 1 && PT_VALUE_2_TEMP > 1950 && PT_VALUE_2_TEMP < 2050)
            {
                sum_cnt[step]++;                       // 增加采样计数
                sum_temp[step] += PT_VALUE_2_TEMP;     // 累加采样值
                
                // 达到指定采样次数后进行平均计算
                if(sum_cnt[step] >= OFFSET_AV_NUM)
                {
                    Param.Correct[step] = sum_temp[step] / OFFSET_AV_NUM;  // 计算2kΩ平均值
                    sum_temp[step] = 0;                // 重置累加和
                    sum_cnt[step] = 0;                 // 重置计数
                    Param.Calibration = 1;             // 标记已校准
                    Calibration.Switch = 0;            // 关闭校准模式
                    Beep_Flash = 5;                    // 蜂鸣器提示5声(校准完成)
                    Save_Param_En = 1;                 // 使能参数保存
                }
            }
        }
    }
}
