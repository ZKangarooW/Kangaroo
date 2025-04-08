#include "Ctrl_ControlTemp.h"

/**********ȫ�ֱ�������******/
uint8_t Temp_Control;//�¶ȿ��ƿ���
uint8_t Add_Ctrl;//�¶Ȳ���ֵ
int Temp_Out;//�¶�pwm���ֵ

/*
*****************************************************************
 * ����ԭ�ͣ� void temp_Control(void)
 * ��    �ܣ� �¶ȼ��ȿ���
*****************************************************************
*/
void temp_Control(void)
{ 
    if(Run_Status == 1 && Temp_Control == 1 && Temp_State == 1)//�������������¶Ⱥ��¶ȿ���
    { 
        if(Temp >= 460 && Temp < 760)
            Add_Ctrl = 90;
        else if(Temp >= 760 && Temp < 960)
            Add_Ctrl = 140;
        else if(Temp >= 960 && Temp < 1090)
            Add_Ctrl = 160;
        else if(Temp >= 1090 && Temp <= 1200)
            Add_Ctrl = 220;
        PID_Calc(Ture_Temp,Ctrl_Temp+Add_Ctrl);//pid����
        if(Temp_Val.Out>5 && Temp_Val.Out<18)//�������ȹ�����3��12��Χ��ʱ
        {
           Temp_Val.Out = 15;//������С����
        }
        Temp_Out = (int)Temp_Val.Out;//pidֵ��ֵ
        if(Temp_Out >= 1000) 	Temp_Out = 1000;//pid����޷�
        else if(Temp_Out <=0)	Temp_Out = 0; 
        HEAT = Temp_Out;//���Ƽ���ģ��
    }
    else
    {
        Temp_Out = 0;//PWM���Ϊ��
        HEAT = 0;//���Ȳ�����
        Temp_ADDMode = 0;//��ʾģʽΪ��
    }
}
