#include "Drv_HT16H25.h"

/*
*****************************************************************
 * 函数原型：static void HT16H25_Enable(uint8_t ena)
 * 功    能：使能SPI_ICM引脚
 * 输    入: ena 0或1使能
 * 参    数: uint8_t ena
 * 调    用：内部调用
*****************************************************************
*/
static void HT16H25_Enable(uint8_t ena)
{
    if(ena)
        CS_HT_L();
    else
        CS_HT_H();
}

// 单命令格式（1字节）：
void SendCommand(uint8_t cmd) {
    HT16H25_Enable(1);
    SPI2_ReadWriteByte(cmd); // 直接发送命令字节
    HT16H25_Enable(0);
}

// 地址+数据格式（2字节）：
void WriteData(uint8_t addr, uint8_t data) {
    HT16H25_Enable(1);
    SPI2_ReadWriteByte(addr & 0x0F); // 地址低4位有效
    SPI2_ReadWriteByte(data);
    HT16H25_Enable(0);
}

uint8_t init_seq[] = {
    0x21,   // 系统振荡器ON
    0xA0,   // INT/ROW配置
    0x87,   // 1/16 duty + 1/5 bias (0x82|0x05)
    0x84,   // A型驱动波形
    0xEF,   // 最大亮度
    0x81    // 显示ON
};

void Hardware_Reset(void) {
    HT16H25_Enable(0);  // CSB拉高
    HAL_Delay(100);  // 保持100ms
    HT16H25_Enable(1);  // CSB拉低开始通信
    HAL_Delay(10);
    SendCommand(0x21);  // 单独发送振荡器启动
}

void Emergency_Config(void) {
    // 1. 禁用内部偏置电路
    SendCommand(0x2F);  // 工厂测试命令（禁用LDO）
    HAL_Delay(50);
    
    // 2. 手动设置偏置电压
    SendCommand(0x89);  // 改为1/3 bias适应异常电压
    SendCommand(0xD2 | 0x0F);  // 最大对比度补偿
    
    // 3. 强制刷新显示
    for(uint8_t i=0; i<16; i++) {
        WriteData(i, 0xFF);  // 全屏点亮测试
    }
}

/**
  * @brief HT16H25初始化（VLCD=5V配置）
  * @note 需确保：
  *       1. VLCD引脚已接5V±5%
  *       2. VDD=3.3V/5V
  *       3. IFS引脚接地（SPI模式）
  */
void HT16H25_Init(void)
{
	HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
//	Emergency_Config();
//	Hardware_Reset();
    // 1. 硬件复位（严格时序）
    HT16H25_Enable(0);  // CSB拉高
    HAL_Delay(15);      // 保持15ms
    HT16H25_Enable(1);  // CSB拉低开始通信
    
    // 2. 电源配置（关键命令）
    SendCommand(0xD0 | 0x08);  // 使用外部VLCD（禁止电荷泵）
    SendCommand(0xD2 | 0x0D);  // 最大对比度补偿低压（0x0F=15）
    HAL_Delay(5);
    
    // 3. 基础显示配置
    uint8_t init_cmds[] = {
        0x21,   // 系统振荡器ON
        0xA0,   // INT/ROW配置（标准模式）
        0x8F,   // 1/16 duty + 1/5 bias（0x82|0x07）
        0x84,   // 驱动波形类型A
        0x81    // 显示ON
    };
    
    for(uint8_t i=0; i<sizeof(init_cmds); i++) {
        SendCommand(init_cmds[i]);
        HAL_Delay(5);
    }
	for(uint8_t addr=0; addr<0x10; addr++) {
		WriteData(addr, 0xFF);
	}
}


//void HT16H25_Init(void) {
//	HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);


//    // 1. 超长复位（针对异常状态）
//    HT16H25_Enable(0);
//    HAL_Delay(200);  // 延长至200ms
//    HT16H25_Enable(1);
//	

//    // 2. 偏置电路激活命令（非标准序列）
//    SendCommand(0x2F);  // 强制重置偏置发生器
//    HAL_Delay(30);
//    
//    // 3. 标准配置（增加重试机制）
//    uint8_t cmds[] = {0x21, 0xA0, 0x8F, 0x84, 0x81};
//    for(uint8_t retry=0; retry<5; retry++) {
//        for(uint8_t i=0; i<5; i++) {
//            SendCommand(cmds[i]);
//            HAL_Delay(10);
//        }
////        if(Read_ADC(V4_PIN) > 0.5f) break; // 检测V4是否恢复
//    }
//	for(uint8_t addr=0; addr<0x10; addr++) {
//		WriteData(addr, 0xFF);
//	}

//}
