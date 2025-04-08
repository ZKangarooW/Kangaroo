#include "Speed.h"

/*
*****************************************************************
 * 函数原型： void Encoder_Init(void)
 * 功    能： 编码器初始化 
*****************************************************************
*/
void Encoder_Init(void)
{   
    #if (Integration_TYPE == 0)
		if(Param.type == 0 || Param.type == 2)//四联
		{
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//motor1 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//motor2 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//motor3 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//motor4 输入捕获
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//motor1 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//motor2 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);//motor3 输入捕获
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//motor4 输入捕获
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//motor5 输入捕获
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);//motor6 输入捕获
		}
    #elif (Integration_TYPE == 1)   
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);//motor1 输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);//motor2 输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_3);//motor3 输入捕获
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_4);//motor4 输入捕获
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//motor5 输入捕获
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);//motor6 输入捕获
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//motor7 输入捕获
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);//motor8 输入捕获
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);//motor9 输入捕获
    #endif
}

/*
*****************************************************************
 * 函数原型： void Check_Speed(void)
 * 功    能： 检测速度是否停止
*****************************************************************
*/
void Check_Speed(void)
{
    #if (Integration_TYPE == 0)//设置成四联时
	if(Param.type == 0 || Param.type == 2)//四联
	{
		Speed_Cnt.L1++;//每50ms进入
		Speed_Cnt.L2++;
		Speed_Cnt.L5++;
		Speed_Cnt.L6++;
		if(Speed_Cnt.L1>=10)//0.5s发现没出发输入捕获
			Rel_Speed.L1 = 0;//将速度清零
		if(Speed_Cnt.L2>=10)
			Rel_Speed.L2 = 0; 
		if(Speed_Cnt.L5>=10)
			Rel_Speed.L5 = 0;
		if(Speed_Cnt.L6>=10)
			Rel_Speed.L6 = 0;
	}
	else if(Param.type == 1 || Param.type == 3)//六联
	{
		Speed_Cnt.L1++;//每50ms进入
		Speed_Cnt.L2++;
		Speed_Cnt.L3++;
		Speed_Cnt.L4++;
		Speed_Cnt.L5++;
		Speed_Cnt.L6++;
		if(Speed_Cnt.L1>=10)//0.5s发现没出发输入捕获
			Rel_Speed.L1 = 0;//将速度清零
		if(Speed_Cnt.L2>=10)
			Rel_Speed.L2 = 0; 
		if(Speed_Cnt.L3>=10)
			Rel_Speed.L3 = 0; 
		if(Speed_Cnt.L4>=10)
			Rel_Speed.L4 = 0; 
		if(Speed_Cnt.L5>=10)
			Rel_Speed.L5 = 0;
		if(Speed_Cnt.L6>=10)
			Rel_Speed.L6 = 0; 
	}      
    #elif (Integration_TYPE == 1)
	Speed_Cnt.L1++;//每50ms进入
    Speed_Cnt.L2++;
    Speed_Cnt.L3++;
    Speed_Cnt.L4++;
    Speed_Cnt.L5++;
    Speed_Cnt.L6++;
    Speed_Cnt.L7++;
    Speed_Cnt.L8++;
	Speed_Cnt.L9++;
	if(Speed_Cnt.L1>=10)//0.5s发现没出发输入捕获
        Rel_Speed.L1 = 0;//将速度清零
    if(Speed_Cnt.L2>=10)
        Rel_Speed.L2 = 0; 
    if(Speed_Cnt.L3>=10)
        Rel_Speed.L3 = 0; 
    if(Speed_Cnt.L4>=10)
        Rel_Speed.L4 = 0; 
    if(Speed_Cnt.L5>=10)
        Rel_Speed.L5 = 0;
    if(Speed_Cnt.L6>=10)
        Rel_Speed.L6 = 0;  
    if(Speed_Cnt.L7>=10)//0.5s发现没出发输入捕获
        Rel_Speed.L7 = 0;//将速度清零
    if(Speed_Cnt.L8>=10)
        Rel_Speed.L8 = 0;   
	if(Speed_Cnt.L9>=10)
        Rel_Speed.L9 = 0;		
    #endif
}

#if (Integration_TYPE == 0)//设置成四联时
/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel1Callback(void)
 * 功    能： Tim1通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t L1_capture,L1_capture1,L1_capture2;
uint32_t rel1;
void TIM1CaptureChannel1Callback(void)
{
	if(Param.type == 1 || Param.type == 3)//六联
	{
		L1_capture1=__HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);//获取Tim1通道1的输入捕获
		if(L1_capture1>L1_capture2)
			L1_capture=L1_capture1-L1_capture2;
		else
			L1_capture=L1_capture1+(0xFFFF-L1_capture2);
		if(L1_capture<100)
			return;
		rel1=60000000/(L1_capture*200);//计算速度
		L1_capture2=L1_capture1;
		Rel_Speed.L1=rel1;//将速度赋值给L1的实际速度	
		Speed_Cnt.L1 = 0;
	}
}	

/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel2Callback(void)
 * 功    能： Tim1通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t L2_capture,L2_capture1,L2_capture2;
uint32_t rel2;
void TIM1CaptureChannel2Callback(void)
{
	if(Param.type == 1 || Param.type == 3)//六联
	{
		L2_capture1=__HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2);//获取Tim1通道2的输入捕获
		if(L2_capture1>L2_capture2)
			L2_capture=L2_capture1-L2_capture2;
		else
			L2_capture=L2_capture1+(0xFFFF-L2_capture2);
		if(L2_capture<100)
			return;  
		rel2=60000000/(L2_capture*200);//计算速度
		L2_capture2=L2_capture1;
		Rel_Speed.L2=rel2;//将速度赋值给L1的实际速度	
		Speed_Cnt.L2 = 0;
	}
}	

/*
*****************************************************************
 * 函数原型： void TIM3CaptureChannel4Callback(void)
 * 功    能： Tim3通道4的输入捕获回调函数
*****************************************************************
*/
uint32_t L3_capture, L3_capture1, L3_capture2;
uint32_t rel3;
void TIM3CaptureChannel4Callback()
{
	if(Param.type == 0 || Param.type == 2)//四联
	{
		L1_capture1=__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);//获取Tim3通道4的输入捕获
		if(L1_capture1>L1_capture2)
			L1_capture=L1_capture1-L1_capture2;
		else
			L1_capture=L1_capture1+(0xFFFF-L1_capture2);
		if(L1_capture<100)
			return;
		rel1=60000000/(L1_capture*200);//计算速度
		L1_capture2=L1_capture1;
		Rel_Speed.L1=rel1;//将速度赋值给L1的实际速度	
		Speed_Cnt.L1 = 0;
	}
	else if(Param.type == 1 || Param.type == 3)//六联
	{
		L3_capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);
		if(L3_capture1 > L3_capture2)
			L3_capture = L3_capture1 - L3_capture2;
		else
			L3_capture = L3_capture1 + (0xFFFF - L3_capture2);
		if(L3_capture < 100)
			return;
		rel3 = 60000000 / (L3_capture * 200);
		L3_capture2 = L3_capture1;
		Rel_Speed.L3 = rel3;
		Speed_Cnt.L3 = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void TIM3CaptureChannel1Callback(void)
 * 功    能： Tim3通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t L4_capture, L4_capture1, L4_capture2;
uint32_t rel4;
void TIM3CaptureChannel1Callback()
{
	if(Param.type == 0 || Param.type == 2)//四联
	{
		L2_capture1=__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);//获取Tim3通道1的输入捕获
		if(L2_capture1>L2_capture2)
			L2_capture=L2_capture1-L2_capture2;
		else
			L2_capture=L2_capture1+(0xFFFF-L2_capture2);
		if(L2_capture<100)
			return;  
		rel2=60000000/(L2_capture*200);//计算速度
		L2_capture2=L2_capture1;
		Rel_Speed.L2=rel2;//将速度赋值给L1的实际速度	
		Speed_Cnt.L2 = 0;
	}
	else if(Param.type == 1 || Param.type == 3)//六联
	{
		L4_capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
		if(L4_capture1 > L4_capture2)
			L4_capture = L4_capture1 - L4_capture2;
		else
			L4_capture = L4_capture1 + (0xFFFF - L4_capture2);
		if(L4_capture < 100)
			return;
		rel4 = 60000000 / (L4_capture * 200);
		L4_capture2 = L4_capture1;
		Rel_Speed.L4 = rel4;
		Speed_Cnt.L4 = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void TIM3CaptureChannel3Callback(void)
 * 功    能： Tim3通道3的输入捕获回调函数
*****************************************************************
*/
uint32_t L5_capture, L5_capture1, L5_capture2;
uint32_t rel5;
void TIM3CaptureChannel3Callback()
{
	L5_capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);
	if(L5_capture1 > L5_capture2)
		L5_capture = L5_capture1 - L5_capture2;
	else
		L5_capture = L5_capture1 + (0xFFFF - L5_capture2);
	if(L5_capture < 100)
		return;
	rel5 = 60000000 / (L5_capture * 200);
	L5_capture2 = L5_capture1;
	Rel_Speed.L5 = rel5;
	Speed_Cnt.L5 =0;
}

/*
*****************************************************************
 * 函数原型： void TIM3CaptureChannel2Callback(void)
 * 功    能： Tim3通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t L6_capture, L6_capture1, L6_capture2;
uint32_t rel6;
void TIM3CaptureChannel2Callback()
{
	L6_capture1 = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);
	if(L6_capture1 > L6_capture2)
		L6_capture = L6_capture1 - L6_capture2;
	else
		L6_capture = L6_capture1 + (0xFFFF - L6_capture2);
	if(L6_capture < 100)
		return;
	rel6 = 60000000 / (L6_capture * 200);
	L6_capture2 = L6_capture1;
	Rel_Speed.L6 = rel6;
	Speed_Cnt.L6 =0;
}

#elif (Integration_TYPE == 1)
/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel1Callback(void)
 * 功    能： Tim1通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t L1_capture, L1_capture1, L1_capture2;
uint32_t rel1;
void TIM1CaptureChannel1Callback()
{
    L1_capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);
    if(L1_capture1 > L1_capture2)
        L1_capture = L1_capture1 - L1_capture2;
    else
        L1_capture = L1_capture1 + (0xFFFF - L1_capture2);
    if(L1_capture < 100)
        return;
    rel1 = 60000000 / (L1_capture * 200);
    L1_capture2 = L1_capture1;
    Rel_Speed.L1 = rel1;
    Speed_Cnt.L1 =0;
}

/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel2Callback(void)
 * 功    能： Tim1通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t L2_capture, L2_capture1, L2_capture2;
uint32_t rel2;
void TIM1CaptureChannel2Callback()
{
    L2_capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_2);
    if(L2_capture1 > L2_capture2)
        L2_capture = L2_capture1 - L2_capture2;
    else
        L2_capture = L2_capture1 + (0xFFFF - L2_capture2);
    if(L2_capture < 100)
        return;
    rel2 = 60000000 / (L2_capture * 200);
    L2_capture2 = L2_capture1;
    Rel_Speed.L2 = rel2;
    Speed_Cnt.L2 =0;
}

/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel3Callback(void)
 * 功    能： Tim1通道3的输入捕获回调函数
*****************************************************************
*/
uint32_t L3_capture, L3_capture1, L3_capture2;
uint32_t rel3;
void TIM1CaptureChannel3Callback()
{
    L3_capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_3);

    if(L3_capture1 > L3_capture2)
        L3_capture = L3_capture1 - L3_capture2;
    else
        L3_capture = L3_capture1 + (0xFFFF - L3_capture2);
    if(L3_capture < 100)
        return;
    // __HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC1);
    rel3 = 60000000 / (L3_capture * 200);
    L3_capture2 = L3_capture1;
    Rel_Speed.L3 = rel3;
    Speed_Cnt.L3 =0;
}

/*
*****************************************************************
 * 函数原型： void TIM8CaptureChannel4Callback(void)
 * 功    能： Tim8通道4的输入捕获回调函数
*****************************************************************
*/
uint32_t L4_capture, L4_capture1, L4_capture2;
uint32_t rel4;
void TIM8CaptureChannel4Callback()
{
    L4_capture1 = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_4);
    if(L4_capture1 > L4_capture2)
        L4_capture = L4_capture1 - L4_capture2;
    else
        L4_capture = L4_capture1 + (0xFFFF - L4_capture2);
    if(L4_capture < 100)
        return;
    rel4 = 60000000 / (L4_capture * 200);
    L4_capture2 = L4_capture1;
    Rel_Speed.L4 = rel4;
    Speed_Cnt.L4 = 0;
}

/*
*****************************************************************
 * 函数原型： void TIM8CaptureChannel3Callback(void)
 * 功    能： Tim8通道3的输入捕获回调函数
*****************************************************************
*/
uint32_t L5_capture, L5_capture1, L5_capture2;
uint32_t rel5;
void TIM8CaptureChannel3Callback()
{
    L5_capture1 = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_3);
    if(L5_capture1 > L5_capture2)
        L5_capture = L5_capture1 - L5_capture2;
    else
        L5_capture = L5_capture1 + (0xFFFF - L5_capture2);
    if(L5_capture < 100)
        return;
    rel5 = 60000000 / (L5_capture * 200);
    L5_capture2 = L5_capture1;
    Rel_Speed.L5 = rel5;
    Speed_Cnt.L5 = 0;
}

/*
*****************************************************************
 * 函数原型： void TIM1CaptureChannel1Cal4back(void)
 * 功    能： Tim1通道4的输入捕获回调函数
*****************************************************************
*/
uint32_t L6_capture, L6_capture1, L6_capture2;
uint32_t rel6;
void TIM1CaptureChannel4Callback()
{
    L6_capture1 = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_4);
    if(L6_capture1 > L6_capture2)
        L6_capture = L6_capture1 - L6_capture2;
    else
        L6_capture = L6_capture1 + (0xFFFF - L6_capture2);
    if(L6_capture < 100)
        return;
    rel6 = 60000000 / (L6_capture * 200);
    L6_capture2 = L6_capture1;
    Rel_Speed.L6 = rel6;
    Speed_Cnt.L6 =0;
}

/*
*****************************************************************
 * 函数原型： void TIM8CaptureChannel2Callback(void)
 * 功    能： Tim8通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t L7_capture, L7_capture1, L7_capture2;
uint32_t rel7;
void TIM8CaptureChannel2Callback()
{
    L7_capture1 = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_2);
    if(L7_capture1 > L7_capture2)
        L7_capture = L7_capture1 - L7_capture2;
    else
        L7_capture = L7_capture1 + (0xFFFF - L7_capture2);
    if(L7_capture < 100)
        return;
    rel7 = 60000000 / (L7_capture * 200);
    L7_capture2 = L7_capture1;
    Rel_Speed.L7 = rel7;
    Speed_Cnt.L7 = 0;
}

/*
*****************************************************************
 * 函数原型： void TIM8CaptureChannel1Callback(void)
 * 功    能： Tim8通道1的输入捕获回调函数
*****************************************************************
*/
uint32_t L8_capture, L8_capture1, L8_capture2;
uint32_t rel8;
void TIM8CaptureChannel1Callback(void)
{
    L8_capture1 = __HAL_TIM_GET_COMPARE(&htim8, TIM_CHANNEL_1);//获取捕获的值
    if(L8_capture1 > L8_capture2)//判断是不是比上次多
        L8_capture = L8_capture1 - L8_capture2;//多的话就直接减去上一个值
    else//表示超出满值自动清零后
        L8_capture = L8_capture1 + (0xFFFF - L8_capture2);//将用65536满值减去上一个值
    if(L8_capture < 100)//小于100的话表示错误
        return;
    rel8 = 60000000 / (L8_capture * 200);//计算转速
    L8_capture2 = L8_capture1;//将当前的值保存
    Rel_Speed.L8 = rel8;//实际值赋值
    Speed_Cnt.L8 = 0;//将判断标志位清零
}

/*
*****************************************************************
 * 函数原型： void TIM2CaptureChannel2Cal4back(void)
 * 功    能： Tim2通道2的输入捕获回调函数
*****************************************************************
*/
uint32_t L9_capture, L9_capture1, L9_capture2;
uint32_t rel9;
void TIM2CaptureChannel2Callback()
{
    L9_capture1 = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_2);
    if(L9_capture1 > L9_capture2)
        L9_capture = L9_capture1 - L9_capture2;
    else
        L9_capture = L9_capture1 + (0xFFFF - L9_capture2);
    if(L9_capture < 100)
        return;
    rel9 = 60000000 / (L9_capture * 200);
    L9_capture2 = L9_capture1;
    Rel_Speed.L9 = rel9;
    Speed_Cnt.L9 =0;
}
#endif

/*
*****************************************************************
 * 函数原型： void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能： TIM_IC回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    #if(Integration_TYPE == 0)//设置成四联时
		if(Param.type == 0 || Param.type == 2)//四联
		{
			if(htim->Instance == TIM3) 
			{
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
				{
					TIM3CaptureChannel1Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2) 
				{           
					TIM3CaptureChannel2Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
				{
					TIM3CaptureChannel3Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
				{
					TIM3CaptureChannel4Callback();
				}      
			}
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			if(htim->Instance == TIM1)
			{
				if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
				{
					TIM1CaptureChannel1Callback();
				}
				else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
				{
					TIM1CaptureChannel2Callback();
				}
			}
			if(htim->Instance == TIM3) 
			{    
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1) 
				{
					TIM3CaptureChannel1Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2) 
				{           
					TIM3CaptureChannel2Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
				{
					TIM3CaptureChannel3Callback();
				} 
				if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
				{
					TIM3CaptureChannel4Callback();
				}      
			}
		}
    #elif (Integration_TYPE == 1)//设置成九联时
    if(htim->Instance == TIM1)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            TIM1CaptureChannel1Callback();
        }
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM1CaptureChannel2Callback();
        }
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            TIM1CaptureChannel3Callback();
        }
        else
        {
            TIM1CaptureChannel4Callback();
        }
    }
    if(htim->Instance == TIM8)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            TIM8CaptureChannel1Callback();
        }
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM8CaptureChannel2Callback();
        }
        else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            TIM8CaptureChannel3Callback();
        }
        else
        {
            TIM8CaptureChannel4Callback();
        }
    }
	if(htim->Instance == TIM2)
    {
        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            TIM2CaptureChannel2Callback();
        }
    }
    #endif
}
