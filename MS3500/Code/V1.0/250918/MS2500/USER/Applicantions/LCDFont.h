#ifndef __LCDFONT_H__
#define __LCDFONT_H__ 

#include "include.h"

/**********宏定义************/
#define Seg_Buff_Size 31

/**********结构体************/
/* 定义段类型 */
typedef enum {
    SEG_A,
    SEG_B,
    SEG_C,
    SEG_D,
    SEG_E,
    SEG_F,
    SEG_G,
    SEG_COUNT
} SegmentType;

/* 定义显示的内容 */
typedef enum {
	Dispaly_0,
    Dispaly_1,
    Dispaly_2,
    Dispaly_3,
    Dispaly_4,
    Dispaly_5,
    Dispaly_6,
    Dispaly_7,
    Dispaly_8,
	Dispaly_9,
	Dispaly__,
	Dispaly_A,
	Dispaly_B,
	Dispaly_C,
	Dispaly_D,
	Dispaly_E,
	Dispaly_F,
	Dispaly_G,
	Dispaly_P,
    Dispaly_OFF,
	Dispaly_COUNT
} DispalyType;

/* 显示的位置 */
typedef enum {
	RelSpeed_1,//实际速度的第一位
	RelSpeed_2,//实际速度的第二位
	RelSpeed_3,//实际速度的第三位
	RelSpeed_4,//实际速度的第四位
	SetSpeed_1,//设定速度的第一位
	SetSpeed_2,//设定速度的第二位
	SetSpeed_3,//设定速度的第三位
	SetSpeed_4,//设定速度的第四位
    RelTime_1,//实际时间的第一位
	RelTime_2,//实际时间的第二位
    RelTime_3,//实际时间的第三位
	RelTime_4,//实际时间的第四位
    SetTime_1,//设定时间的第一位
	SetTime_2,//设定时间的第二位
    SetTime_3,//设定时间的第三位
	SetTime_4,//设定时间的第四位
	P_1,//P的第一位
	P_2,//P的第二位
	P_3,//P的第三位
	Location_COUNT
} Display_Location;

/* 定义每位数字的每个段的地址和数据值 */
typedef struct {
    uint8_t address; // 寄存器地址
    uint8_t value;   // 要发送的数据值
} SegmentMapping;

/**********全局变量声明******/
extern uint8_t seg[Seg_Buff_Size];//存储显示数据

/**********全局函数**********/
void bit_Cal(uint8_t bit,uint8_t num,uint8_t num1);
void ShowDigit(uint8_t Loc,uint8_t number) ;

#endif
