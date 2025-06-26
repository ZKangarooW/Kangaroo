#ifndef __DRV_HT16H25_H__
#define __DRV_HT16H25_H__

#include "include.h"

/**********宏定义************/
/* 显示缓冲区大小定义 */
#define LCD_Buff_Size   120

/* HT16H25寄存器命令定义 */
#define SoftwareReset       0xAA
#define Pageconfig          0x72
#define WriteDisRam         0x80
#define DriveMode           0x82
#define DriveWaveform       0x84
#define SystemMode          0x86
#define FrameFrequence      0x88
#define Blinking            0x8A
#define GPO_Data            0x90
#define GPO_Mode            0x92
#define PWM_Enable          0xB0
#define WritePWM_GPO0       0xB2
#define WritePWM_GPO1       0xB4
#define WritePWM_GPO2       0xB6
#define WritePWM_GPO3       0xB8
#define ChargePump_vol      0xC0
#define ChargePump_ctrl     0xC2
#define BiasCircuit         0xD0

/* 显示RAM地址映射（根据实际硬件连接调整） */
#define Y1_RAMBuff_Add      0x01
#define Y2_RAMBuff_Add      0x03
#define		Y3_RAMBuff_Add			0x05
#define		Y4_RAMBuff_Add			0x07
#define		Y5_RAMBuff_Add			0x04
#define		Y6_RAMBuff_Add			0x02
#define		Y7_RAMBuff_Add			0x71
#define		Y8_RAMBuff_Add			0x6f
#define		Y9_RAMBuff_Add			0x42
#define		Y10_RAMBuff_Add			0x44
#define		Z1_RAMBuff_Add			0x46
#define		Z2_RAMBuff_Add			0x4a
#define		Z3_RAMBuff_Add			0x4e
#define		Z4_RAMBuff_Add			0x52
#define		Z5_RAMBuff_Add			0x6a
#define		Z6_RAMBuff_Add			0x66
#define		Z7_RAMBuff_Add			0x62
#define		Z8_RAMBuff_Add			0x5e
#define		Z9_RAMBuff_Add			0x56
#define		Z10_RAMBuff_Add			0x5a
#define		Z11_RAMBuff_Add			0x56
#define		Z12_RAMBuff_Add			0x5e
#define		Z13_RAMBuff_Add			0x62
#define		Z14_RAMBuff_Add			0x66
#define		Z15_RAMBuff_Add			0x6a
#define		Z16_RAMBuff_Add			0x52
#define		Z17_RAMBuff_Add			0x4e
#define		Z18_RAMBuff_Add			0x4a
#define		Z19_RAMBuff_Add			0x46

/* 函数声明 */
void HT16H25_Init(void);
void HT16H25_Command_Write(uint8_t command, uint8_t data);
void HT16H25_RamUpdate(uint8_t* buff);
void HT16H25_ClearScreen(void);
void HT16H25_TestPattern(uint8_t on);

#endif
