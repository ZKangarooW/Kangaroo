#ifndef __SHOW_H__
#define __SHOW_H__

#include "main.h"

/**********全局变量**********/
extern uint32_t rel_time;//实时时间
extern uint32_t set_time;//设定时间
extern uint8_t time_status;//时间显示模式
extern uint8_t Set_Mode_Enable;//P键进入设置模式 0：模式设置不予显示 1：模式设置显示
extern uint8_t run_mode_flag;//进入P时显示
extern uint8_t Select_Option;//设置时当前设置的选项
extern uint16_t Twinkle_Time;//闪烁的时间
extern uint16_t Twinkle_On;//闪烁倒计时
extern uint8_t temp_flag;//选中设置温度时闪烁
extern uint8_t time_flag;//选中设置时间时闪烁
extern uint8_t mode_flag;//选中设置模式时闪烁
extern uint8_t circle_dis;//梯度模式下外圈转动显示（本代码不操作此寄存器，单加热）
extern uint8_t circle_dis_flag;//外圈开始转动（本代码不操作此寄存器，单加热）
extern uint8_t mode_flag_p1;//梯度模式下P1的闪烁（本代码不操作此寄存器，单加热）
extern uint8_t mode_flag_p2;//梯度模式下P1的闪烁（本代码不操作此寄存器，单加热）
extern uint8_t mode_run_p1;//梯度模式下P1的值（本代码不操作此寄存器，单加热）
extern uint8_t mode_run_p2;//梯度模式下P1的值（本代码不操作此寄存器，单加热）
extern uint8_t set_mode_p;//P模式下切换梯度模式还是就记忆模式 1：梯度模式 0：p模式（本代码不操作此寄存器，单加热）
extern uint8_t ADD_Wait_Count;//升温显示缓慢上升
extern int Dis_Rel_Temp;//实时时间
extern uint8_t SetTime_State;//未设定时间显示“----”

/**********全局函数**********/
void LCD_Display(void);//屏幕显示
void Circle_Go(void);//外圈转动
void Cheak_ShowFlag(uint16_t dT);//闪烁检测
void Dis_RelTemp(int dis_rel_temp);//显示实际温度
void time_icn(float dT);//启动时时间图标闪烁 
void ADD_Show(uint16_t dT);//显示上升时间

#endif
