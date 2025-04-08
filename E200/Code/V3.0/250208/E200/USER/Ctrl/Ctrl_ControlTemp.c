#include "Ctrl_ControlTemp.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Iint(void)
 * ��    �ܣ��¶ȳ�ʼ��
*****************************************************************
*/
void Temp_Iint(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//����tim1ͨ��2��PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��2��PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ��2��PWM
}

/**********�ṹ��************/
_PID_Val_ HeatTemp_Val;//pid���ݽṹ
_PID_Arg_ HeatTemp_Arg;//pid����ϵ��
_PID_Val_ CoolTemp_Val;//pid���ݽṹ
_PID_Arg_ CoolTemp_Arg;//pid����ϵ��

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
*****************************************************************
*/
void PID_Init(void)
{
	HeatTemp_Arg.Kp=0;
	HeatTemp_Arg.Ki=0;
	HeatTemp_Arg.Kd=0;
	HeatTemp_Arg.Kp_i = 0.1;
    
	CoolTemp_Arg.Kp=0;
	CoolTemp_Arg.Ki=0;
	CoolTemp_Arg.Kd=0;
    CoolTemp_Arg.Kp_i = 0.1;
}
/*
*****************************************************************
 * ����ԭ�ͣ�void CoolTemp_Mode(float dT,int pwm)
 * ��    �ܣ����������л�
*****************************************************************
*/uint8_t Mode,mode;//��ʱ�洢��ǰģʽ
void CoolTemp_Mode(float dT,float Ctrl_temp,float pwm)
{
	static float T;
//	static 
	
	if(pwm >= 40 && (Ctrl_temp > Cool_Temp.Rel_Temp))
	{
		if(pwm > 50)
			WIND_OFF;
		mode = 0;//����
	}
	else if(pwm < 40 && (Ctrl_temp < Cool_Temp.Rel_Temp))
	{
		if(pwm < -60)
			WIND_ON;
		mode = 1;//����
	}
		
	if(Mode != mode)//���ģʽ�任��
	{
		T += dT;//��ʼ��ʱ
		if(T <= 1.0f)//һ��û�Ѽ��Ⱥ����䶼���Ͳ�����
		{
			COLD = 0;
			HEAT = 0;
		}
		else//һ��󽫸ĵ�ģʽ��ֵ
		{
			T = 0;
			Mode = mode;
		}
	}
	else//û�иı�ģʽ�������
	{
		if(Ctrl_temp > Cool_Temp.Rel_Temp)
		{
			HEAT = (int)(ABS(pwm*10));
            COLD = 0;
		}			
		else if(Ctrl_temp < Cool_Temp.Rel_Temp)
		{
            HEAT = 0;
			COLD = (int)(ABS(pwm*10));
		}
        else
        {
            COLD = 0;
			HEAT = 0;
        }
	}
}

/**********�ֲ���������******/
float Ku = 0.0;//�ٽ�����
float Tu = 0.0;//�ٽ�����

/**********ȫ�ֱ�������******/
bool tuning_complete = false;//�Զ����α�־λ
float last_peak_time = 0.0;//��һ������
int oscillation_count = 0;//������

/*
*****************************************************************
 * ����ԭ�ͣ�void setPWM(float duty_cycle)
 * ��    �ܣ����� PWM ��������Ƽ�������
*****************************************************************
*/
void setPWM(float Ctrl_Temp,float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Heat_Temp.Rel_Temp >= Ctrl_Temp)
        duty_cycle = 0;
    UC_HEAT = (int)(duty_cycle*10);
}

/*
*****************************************************************
 * ����ԭ�ͣ�bool AutoTunePID(float dt, float *Ku, float *Tu) 
 * ��    �ܣ��Զ�����ģ��
 * ��    �룺dT�����ڣ���λ���룩
			 Ku���ٽ�����
			 Tu���ٽ�����
 * ��    ����float dT, float *Ku, float *Ku
*****************************************************************
*/
bool AutoTunePID(float dT,float temp_ctrl, float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��
    
    //ʹ�ñ�������
    HeatTemp_Val.Out = HeatTemp_Arg.Kp_i * (temp_ctrl - Heat_Temp.Rel_Temp);
    setPWM(temp_ctrl,HeatTemp_Val.Out);
    
    //�����
    if (Heat_Temp.Rel_Temp > temp_ctrl && last_temp < temp_ctrl) 
    {
        if (oscillation_count < 2) {
            peak_time[oscillation_count] = last_peak_time;
        }
        oscillation_count++;
    }
    last_temp = Heat_Temp.Rel_Temp;
    last_peak_time += dT;

    //���� Ku �� Tu
    if (oscillation_count >= 2) 
    {
        *Ku = HeatTemp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count = 0;
        return true; //�Զ��������
    }

    //��������
    if(Heat_Temp.Rel_Temp < temp_ctrl)
//        HeatTemp_Arg.Kp_i += 0.01;
    HeatTemp_Arg.Kp_i += 0.1;
    return false; //��δ���
}
/**********�ֲ���������******/
float Ku1 = 0.0;//�ٽ�����
float Tu1 = 0.0;//�ٽ�����

/**********ȫ�ֱ�������******/
bool tuning_complete1 = false;//�Զ����α�־λ
float last_peak_time1 = 0.0;//��һ������
int oscillation_count1 = 0;//������
/*
*****************************************************************
 * ����ԭ�ͣ�bool AutoTunePID(float dt, float *Ku, float *Tu) 
 * ��    �ܣ��Զ�����ģ��
 * ��    �룺dT�����ڣ���λ���룩
			 Ku���ٽ�����
			 Tu���ٽ�����
 * ��    ����float dT, float *Ku, float *Ku
*****************************************************************
*/
bool AutoCoolTunePID(float dT, float ctrl_Temp,float *Ku, float *Tu) 
{    
    static float last_temp = 0.0;
    static float peak_time[2] = {0.0, 0.0}; // ��¼������ֵ��ʱ��
    
    //ʹ�ñ�������
    CoolTemp_Val.Out = CoolTemp_Arg.Kp_i * (ctrl_Temp - Cool_Temp.Rel_Temp);
    CoolTemp_Mode(dT,ctrl_Temp,CoolTemp_Val.Out);
    
    //�����
    if (Cool_Temp.Rel_Temp > ctrl_Temp && last_temp < ctrl_Temp) 
    {
        if (oscillation_count1 < 2) {
            peak_time[oscillation_count1] = last_peak_time1;
        }
        oscillation_count1++;
    }
    last_temp = Cool_Temp.Rel_Temp;
    last_peak_time1 += dT;

    //���� Ku �� Tu
    if (oscillation_count1 >= 2) 
    {
        *Ku = CoolTemp_Arg.Kp_i;
        *Tu = peak_time[1] - peak_time[0];
        oscillation_count1 = 0;
        return true; //�Զ��������
    }

    //��������
//    CoolTemp_Arg.Kp_i += 0.008;
    CoolTemp_Arg.Kp_i += 0.08;
    return false; //��δ���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
		// �Զ����ν׶�
        if (!tuning_complete) {
            tuning_complete = AutoTunePID(dT,Heat_Temp.Ctrl_Temp, &Ku, &Tu);
            if(tuning_complete)
            {
                HeatTemp_Arg.Kp = 0.6 * Ku;
                HeatTemp_Arg.Ki = 2 * HeatTemp_Arg.Kp_i / Tu;
                HeatTemp_Arg.Kd = HeatTemp_Arg.Kp_i * Tu / 8; 
                HeatTemp_Arg.Kp_i = 0.1;// ��ʼ����
            }
            return;
        }
        AltPID_Calculation(dT,Heat_Temp.Ctrl_Temp,Heat_Temp.Rel_Temp,&HeatTemp_Arg,&HeatTemp_Val,80,20);   
        setPWM(Heat_Temp.Ctrl_Temp, HeatTemp_Val.Out);
	}
	else
	{
        tuning_complete = false;//�Զ���������Ϊfalse
        last_peak_time = 0.0;//��һ����������
        oscillation_count = 0;//������
		setPWM(Heat_Temp.Ctrl_Temp,0);
	}
}

void Cool_Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        // �Զ����ν׶�
        if (!tuning_complete1) {
            tuning_complete1 = AutoCoolTunePID(dT, Cool_Temp.Ctrl_Temp,&Ku1, &Tu1);
            if(tuning_complete1)
            {
                CoolTemp_Arg.Kp = 0.6 * Ku1;
                CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
//                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                CoolTemp_Arg.Kp_i = 0.1;// ��ʼ����
            }
            return;
        }
        AltPID_Calculation(dT,Cool_Temp.Ctrl_Temp,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
        CoolTemp_Mode(dT,Cool_Temp.Ctrl_Temp,CoolTemp_Val.Out);
	}
    else if(sys.Calibration == 1)
	{
		WIND_OFF;//�رշ���
		if(sys.Calibration_Step == 0)
		{
			 // �Զ����ν׶�
            if (!tuning_complete1) {
                tuning_complete1 = AutoCoolTunePID(dT, 260,&Ku1, &Tu1);
                if(tuning_complete1)
                {
                    CoolTemp_Arg.Kp = 0.6 * Ku1;
                    CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
    //                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                    CoolTemp_Arg.Kp_i = 0.1;// ��ʼ����
                }
                return;
            }
            AltPID_Calculation(dT,260,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,260,CoolTemp_Val.Out);
		}
		else
		{
			// �Զ����ν׶�
            if (!tuning_complete1) {
                tuning_complete1 = AutoCoolTunePID(dT, 400,&Ku1, &Tu1);
                if(tuning_complete1)
                {
                    CoolTemp_Arg.Kp = 0.6 * Ku1;
                    CoolTemp_Arg.Ki = 2 * CoolTemp_Arg.Kp_i / Tu1;
    //                CoolTemp_Arg.Kd = CoolTemp_Arg.Kp_i * Tu1 / 8; 
                    CoolTemp_Arg.Kp_i = 0.1;// ��ʼ����
                }
                return;
            }
            AltPID_Calculation(dT,400,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,400,CoolTemp_Val.Out);
		}
	}
	else
	{
		WIND_OFF;//�رշ���
        tuning_complete1 = false;//�Զ���������Ϊfalse
        last_peak_time1 = 0.0;//��һ����������
        oscillation_count1 = 0;//������
        CoolTemp_Mode(dT,0,0);
	}
}
