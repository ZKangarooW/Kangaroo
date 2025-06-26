#ifndef __LCDFONT_H__
#define __LCDFONT_H__ 

#include "include.h"

/**********宏定义************/
#define Seg_Buff_Size 120

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
    Dispaly_OFF,
	Dispaly_COUNT
} DispalyType;

/* 显示的位置 */
typedef enum {
	Work_1_RelSpeed_2,//工位1的实际速度的第二位
	Work_1_RelSpeed_3,//工位1的实际速度的第三位
	Work_1_SetSpeed_2,//工位1的设定速度的第二位
	Work_1_SetSpeed_3,//工位1的设定速度的第三位
    Work_1_RelTemp_1,//工位1的实际温度的第一位
	Work_1_RelTemp_2,//工位1的实际温度的第二位
    Work_1_RelTemp_3,//工位1的实际温度的第三位
	Work_1_RelTemp_4,//工位1的实际温度的第四位
    Work_1_SetTemp_1,//工位1的设定温度的第一位
	Work_1_SetTemp_2,//工位1的设定温度的第二位
    Work_1_SetTemp_3,//工位1的设定温度的第三位
	Work_1_SetTemp_4,//工位1的设定温度的第四位
    Work_1_RelTime_1,//工位1的实际时间的第一位
	Work_1_RelTime_2,//工位1的实际时间的第二位
    Work_1_RelTime_3,//工位1的实际时间的第三位
	Work_1_RelTime_4,//工位1的实际时间的第四位
    Work_1_SetTime_1,//工位1的设定时间的第一位
	Work_1_SetTime_2,//工位1的设定时间的第二位
    Work_1_SetTime_3,//工位1的设定时间的第三位
	Work_1_SetTime_4,//工位1的设定时间的第四位

    Work_2_RelSpeed_2,//工位2的实际速度的第二位
	Work_2_RelSpeed_3,//工位2的实际速度的第三位
	Work_2_SetSpeed_2,//工位2的设定速度的第二位
	Work_2_SetSpeed_3,//工位2的设定速度的第三位
    Work_2_RelTemp_1,//工位2的实际温度的第一位
	Work_2_RelTemp_2,//工位2的实际温度的第二位
    Work_2_RelTemp_3,//工位2的实际温度的第三位
	Work_2_RelTemp_4,//工位2的实际温度的第四位
    Work_2_SetTemp_1,//工位2的设定温度的第一位
	Work_2_SetTemp_2,//工位2的设定温度的第二位
    Work_2_SetTemp_3,//工位2的设定温度的第三位
	Work_2_SetTemp_4,//工位2的设定温度的第四位
    Work_2_RelTime_1,//工位2的实际时间的第一位
	Work_2_RelTime_2,//工位2的实际时间的第二位
    Work_2_RelTime_3,//工位2的实际时间的第三位
	Work_2_RelTime_4,//工位2的实际时间的第四位
    Work_2_SetTime_1,//工位2的设定时间的第一位
	Work_2_SetTime_2,//工位2的设定时间的第二位
    Work_2_SetTime_3,//工位2的设定时间的第三位
	Work_2_SetTime_4,//工位2的设定时间的第四位

    Work_3_RelSpeed_2,//工位3的实际速度的第二位
	Work_3_RelSpeed_3,//工位3的实际速度的第三位
	Work_3_SetSpeed_2,//工位3的设定速度的第二位
	Work_3_SetSpeed_3,//工位3的设定速度的第三位
    Work_3_RelTemp_1,//工位3的实际温度的第一位
	Work_3_RelTemp_2,//工位3的实际温度的第二位
    Work_3_RelTemp_3,//工位3的实际温度的第三位
	Work_3_RelTemp_4,//工位3的实际温度的第四位
    Work_3_SetTemp_1,//工位3的设定温度的第一位
	Work_3_SetTemp_2,//工位3的设定温度的第二位
    Work_3_SetTemp_3,//工位3的设定温度的第三位
	Work_3_SetTemp_4,//工位3的设定温度的第四位
    Work_3_RelTime_1,//工位3的实际时间的第一位
	Work_3_RelTime_2,//工位3的实际时间的第二位
    Work_3_RelTime_3,//工位3的实际时间的第三位
	Work_3_RelTime_4,//工位3的实际时间的第四位
    Work_3_SetTime_1,//工位3的设定时间的第一位
	Work_3_SetTime_2,//工位3的设定时间的第二位
    Work_3_SetTime_3,//工位3的设定时间的第三位
	Work_3_SetTime_4,//工位3的设定时间的第四位


    Work_4_RelSpeed_2,//工位4的实际速度的第二位
	Work_4_RelSpeed_3,//工位4的实际速度的第三位
	Work_4_SetSpeed_2,//工位4的设定速度的第二位
	Work_4_SetSpeed_3,//工位4的设定速度的第三位
    Work_4_RelTemp_1, //工位4的实际温度的第一位
	Work_4_RelTemp_2, //工位4的实际温度的第二位
    Work_4_RelTemp_3, //工位4的实际温度的第三位
	Work_4_RelTemp_4, //工位4的实际温度的第四位
    Work_4_SetTemp_1, //工位4的设定温度的第一位
	Work_4_SetTemp_2, //工位4的设定温度的第二位
    Work_4_SetTemp_3, //工位4的设定温度的第三位
	Work_4_SetTemp_4, //工位4的设定温度的第四位
    Work_4_RelTime_1, //工位4的实际时间的第一位
	Work_4_RelTime_2, //工位4的实际时间的第二位
    Work_4_RelTime_3, //工位4的实际时间的第三位
	Work_4_RelTime_4, //工位4的实际时间的第四位
    Work_4_SetTime_1, //工位4的设定时间的第一位
	Work_4_SetTime_2, //工位4的设定时间的第二位
    Work_4_SetTime_3, //工位4的设定时间的第三位
	Work_4_SetTime_4, //工位4的设定时间的第四位

	Work_5_RelSpeed_2,//工位5的实际速度的第二位
	Work_5_RelSpeed_3,//工位5的实际速度的第三位
	Work_5_SetSpeed_2,//工位5的设定速度的第二位
	Work_5_SetSpeed_3,//工位5的设定速度的第三位
    Work_5_RelTemp_1, //工位5的实际温度的第一位
	Work_5_RelTemp_2, //工位5的实际温度的第二位
    Work_5_RelTemp_3, //工位5的实际温度的第三位
	Work_5_RelTemp_4, //工位5的实际温度的第四位
    Work_5_SetTemp_1, //工位5的设定温度的第一位
	Work_5_SetTemp_2, //工位5的设定温度的第二位
    Work_5_SetTemp_3, //工位5的设定温度的第三位
	Work_5_SetTemp_4, //工位5的设定温度的第四位
    Work_5_RelTime_1, //工位5的实际时间的第一位
	Work_5_RelTime_2, //工位5的实际时间的第二位
    Work_5_RelTime_3, //工位5的实际时间的第三位
	Work_5_RelTime_4, //工位5的实际时间的第四位
    Work_5_SetTime_1, //工位5的设定时间的第一位
	Work_5_SetTime_2, //工位5的设定时间的第二位
    Work_5_SetTime_3, //工位5的设定时间的第三位
	Work_5_SetTime_4, //工位5的设定时间的第四位

	Work_6_RelSpeed_2,//工位6的实际速度的第二位
	Work_6_RelSpeed_3,//工位6的实际速度的第三位
	Work_6_SetSpeed_2,//工位6的设定速度的第二位
	Work_6_SetSpeed_3,//工位6的设定速度的第三位
    Work_6_RelTemp_1, //工位6的实际温度的第一位
	Work_6_RelTemp_2, //工位6的实际温度的第二位
    Work_6_RelTemp_3, //工位6的实际温度的第三位
	Work_6_RelTemp_4, //工位6的实际温度的第四位
    Work_6_SetTemp_1, //工位6的设定温度的第一位
	Work_6_SetTemp_2, //工位6的设定温度的第二位
    Work_6_SetTemp_3, //工位6的设定温度的第三位
	Work_6_SetTemp_4, //工位6的设定温度的第四位
    Work_6_RelTime_1, //工位6的实际时间的第一位
	Work_6_RelTime_2, //工位6的实际时间的第二位
    Work_6_RelTime_3, //工位6的实际时间的第三位
	Work_6_RelTime_4, //工位6的实际时间的第四位
    Work_6_SetTime_1, //工位6的设定时间的第一位
	Work_6_SetTime_2, //工位6的设定时间的第二位
    Work_6_SetTime_3, //工位6的设定时间的第三位
	Work_6_SetTime_4, //工位6的设定时间的第四位
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
