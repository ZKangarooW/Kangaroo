#include "Drv_PT1000.h"

/*
-22-400摄氏度
*/
const float Temp_map[423]=
{
	913.73f,//-22
	917.67f,//-21
	921.60f, 925.53f, 929.46f, 933.39f, 937.32f, 941.24f, 945.17f, 949.09f, 953.02f, 956.94f,// -20°C to --11°C
	960.86f, 964.78f, 968.70f, 972.61f, 976.53f, 980.44f, 984.36f, 988.27f, 992.18f, 996.09f,// -10°C to -1°C
		
	// 0°C to 100°C
	1000.00f, 1003.91f, 1007.81f, 1011.72f, 1015.62f, 1019.53f, 1023.43f, 1027.33f, 1031.23f, 1035.13f,// 0°C to 9°C
	1039.03f, 1042.92f, 1046.82f, 1050.71f, 1054.60f, 1058.49f, 1062.38f, 1066.27f, 1070.16f, 1074.05f, 
	1077.94f, 1081.82f, 1085.70f, 1089.59f, 1093.47f, 1097.35f, 1101.23f, 1105.10f, 1108.98f, 1112.86f,
	1116.73f, 1120.60f, 1124.47f, 1128.35f, 1132.21f, 1136.08f, 1139.95f, 1143.82f, 1147.68f, 1151.55f,
	1155.41f, 1159.27f, 1163.13f, 1166.99f, 1170.85f, 1174.70f, 1178.56f, 1182.41f, 1186.27f, 1190.12f,
	1193.97f, 1197.82f, 1201.67f, 1205.52f, 1209.36f, 1213.21f, 1217.05f, 1220.90f, 1224.74f, 1228.58f,
	1232.42f, 1236.26f, 1240.09f, 1243.93f, 1247.77f, 1251.60f, 1255.43f, 1259.26f, 1263.09f, 1266.92f,
	1270.75f, 1274.58f, 1278.40f, 1282.23f, 1286.05f, 1289.87f, 1293.70f, 1297.52f, 1301.33f, 1305.15f,
	1308.97f, 1312.78f, 1316.60f, 1320.41f, 1324.22f, 1328.03f, 1331.84f, 1335.65f, 1339.46f, 1343.26f,
	1347.07f, 1350.87f, 1354.68f, 1358.48f, 1362.28f, 1366.08f, 1369.87f, 1373.67f, 1377.47f, 1381.26f,
	1385.06f,

	// 101°C to 200°C
	1388.85f, 1392.64f, 1396.43f, 1400.22f, 1404.00f, 1407.79f, 1411.58f, 1415.36f, 1419.14f, 1422.93f,// 101°C to 110°C
	1426.71f, 1430.49f, 1434.26f, 1438.04f, 1441.82f, 1445.59f, 1449.37f, 1453.14f, 1456.91f, 1460.68f,
	1464.45f, 1468.22f, 1471.98f, 1475.75f, 1479.51f, 1483.28f, 1487.04f, 1490.80f, 1494.56f, 1498.32f,
	1502.08f, 1505.83f, 1509.59f, 1513.34f, 1517.10f, 1520.85f, 1524.60f, 1528.35f, 1532.10f, 1535.84f,
	1539.59f, 1543.33f, 1547.08f, 1550.82f, 1554.56f, 1558.30f, 1562.04f, 1565.78f, 1569.52f, 1573.25f,
	1576.99f, 1580.72f, 1584.45f, 1588.18f, 1591.91f, 1595.64f, 1599.37f, 1603.09f, 1606.82f, 1610.54f,
	1614.27f, 1617.99f, 1621.71f, 1625.43f, 1629.15f, 1632.86f, 1636.58f, 1640.30f, 1644.01f, 1647.72f,
	1651.43f, 1655.14f, 1658.85f, 1662.56f, 1666.27f, 1669.97f, 1673.68f, 1677.38f, 1681.08f, 1684.78f,
	1688.48f, 1692.18f, 1695.88f, 1699.58f, 1703.27f, 1706.96f, 1710.66f, 1714.35f, 1718.04f, 1721.73f,
	1725.42f, 1729.10f, 1732.79f, 1736.48f, 1740.16f, 1743.84f, 1747.52f, 1751.20f, 1754.88f, 1758.56f,

	// 201°C to 400°C
	1762.24f, 1765.91f, 1769.59f, 1773.26f, 1776.93f, 1780.60f, 1784.27f, 1787.94f, 1791.61f, 1795.28f,
	1798.94f, 1802.60f, 1806.27f, 1809.93f, 1813.59f, 1817.25f, 1820.91f, 1824.56f, 1828.22f, 1831.88f, 
	1835.53f, 1839.18f, 1842.83f, 1846.48f, 1850.13f, 1853.78f, 1857.43f, 1861.07f, 1864.72f, 1868.36f,
	1872.00f, 1875.64f, 1879.28f, 1882.92f, 1886.56f, 1890.19f, 1893.83f, 1897.46f, 1901.10f, 1904.73f,
	1908.36f, 1911.99f, 1915.62f, 1919.24f, 1922.87f, 1926.49f, 1930.12f, 1933.74f, 1937.36f, 1940.98f,
	1944.60f, 1948.22f, 1951.83f, 1955.45f, 1959.06f, 1962.68f, 1966.29f, 1969.90f, 1973.51f, 1977.12f,
	1980.73f, 1984.33f, 1987.94f, 1991.54f, 1995.14f, 1998.75f, 2002.35f, 2005.95f, 2009.54f, 2013.14f,
	2016.74f, 2020.33f, 2023.93f, 2027.52f, 2031.11f, 2034.70f, 2038.29f, 2041.88f, 2045.46f, 2049.05f,
	2052.63f, 2056.22f, 2059.80f, 2063.38f, 2066.96f, 2070.54f, 2074.11f, 2077.69f, 2081.27f, 2084.84f,
	2088.41f, 2091.98f, 2095.55f, 2099.12f, 2102.69f, 2106.26f, 2109.82f, 2113.39f, 2116.95f, 2120.52f,
	2124.08f, 2127.64f, 2131.20f, 2134.75f, 2138.31f, 2141.87f, 2145.42f, 2148.97f, 2152.52f, 2156.08f,
	2159.62f, 2163.17f, 2166.72f, 2170.27f, 2173.81f, 2177.36f, 2180.90f, 2184.44f, 2187.98f, 2191.52f,  
	2195.06f, 2198.60f, 2202.13f, 2205.67f, 2209.20f, 2212.73f, 2216.26f, 2219.79f, 2223.32f, 2226.85f, 
	2230.38f, 2233.90f, 2237.43f, 2240.95f, 2244.47f, 2247.99f, 2251.51f, 2255.03f, 2258.55f, 2262.06f, 
	2265.58f, 2269.09f, 2272.60f, 2276.12f, 2279.63f, 2283.14f, 2286.64f, 2290.15f, 2293.66f, 2297.16f, 
	2300.66f, 2304.17f, 2307.67f, 2311.17f, 2314.67f, 2318.16f, 2321.66f, 2325.16f, 2328.65f, 2332.14f, 
	2335.64f, 2339.13f, 2342.62f, 2346.10f, 2349.59f, 2353.08f, 2356.56f, 2360.05f, 2363.53f, 2367.01f, 
	2370.49f, 2373.97f, 2377.45f, 2380.93f, 2384.40f, 2387.88f, 2391.35f, 2394.82f, 2398.29f, 2401.76f, 
	2405.23f, 2408.70f, 2412.17f, 2415.63f, 2419.10f, 2422.56f, 2426.02f, 2429.48f, 2432.94f, 2436.40f, 
	2439.86f, 2443.31f, 2446.77f, 2450.22f, 2453.67f, 2457.13f, 2460.58f, 2464.03f, 2467.47f, 2470.92f,
};

/**********全局变量**********/
uint16_t ADC_Val[AD_LEN];//adc的值 0:台面温度ad值。 1：外部探头ad值
uint32_t ADC1_Val,ADC2_Val;//adc的值
#define OP_Value	6.8//放大系数
#define Vref_3V3	3.30f//3.3V电压
#define K1			0.2327367//电阻基准系数
#define Vref		2.497//参考电压
#define R_3K        3.0f//分压电阻3k
#define R_910R      0.91f//分压电阻910Ω

/*
*****************************************************************
 * 函数原型：int Filter_ADC(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
#define N 100//采集100次
int ADCvalue_Buf[Motor_Num][N];//用于储存采集到的adc值
int i[Motor_Num];
int Filter_ADC(uint8_t new_work)
{
    char count;
    long sum = 0;

    ADCvalue_Buf[new_work][i[new_work]++] =ADC_Val[(2*new_work)];
	
    if (i[new_work] == N)//假如读了100组就从新开始
    {
        i[new_work] = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[new_work][count];//100组相加
    }
    if(ADCvalue_Buf[new_work][N-1] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf[new_work][0];
    else//读到100组后
        return (int)(sum / N);//输出平均值
}

/*
*****************************************************************
 * 函数原型：int Filter_ADC1(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
int ADCvalue_Buf1[Motor_Num][N];//用于储存采集到的adc值
int j[Motor_Num];
int Filter_ADC1(uint8_t new_work)
{
    char count;
    long sum = 0;

    ADCvalue_Buf1[new_work][j[new_work]++] =ADC_Val[((2*new_work)+1)];
	
    if (j[new_work] == N)//假如读了100组就从新开始
    {
        j[new_work] = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf1[new_work][count];//100组相加
    }
    if(ADCvalue_Buf1[new_work][N-1] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf1[new_work][0];
    else//读到100组后
        return (int)(sum / N);//输出平均值
}

/*
*****************************************************************
 * 函数原型：void AFE_Sample_Handler(void)
 * 功    能：计算阻值
*****************************************************************
*/
float ADC_Val_Avg[Motor_Num][2];//0为台面温度  1为探头温度
float AD_T1[Motor_Num];//ADC计算后的电压值
float AD_T2[Motor_Num];//ADC计算后的电压值
float PT_VALUE_1_TEMP[Motor_Num];//外部探头阻值
float PT_VALUE_2_TEMP[Motor_Num];//台面探头阻值
float R_value1[Motor_Num];//外部探头阻值
float R_value2[Motor_Num];//台面探头阻值
float TL431_V = 2.5f;//计算TL431的电压值;//TL431基准2.5V电压的电压值
void AFE_Sample_Handler(void)
{
    for(uint8_t i = 0;i<Motor_Num;i++)
    {
        ADC_Val_Avg[i][0] = Filter_ADC(i);
        ADC_Val_Avg[i][1] = Filter_ADC1(i);
        
        AD_T1[i]=((float)ADC_Val_Avg[i][1]*Vref_3V3/4096)/OP_Value+(R_910R/(R_3K+R_910R)*TL431_V);//计算电压值
        AD_T2[i]=((float)ADC_Val_Avg[i][0]*Vref_3V3/4096)/OP_Value+(R_910R/(R_3K+R_910R)*TL431_V);//计算电压值
        
		R_value1[i] = (AD_T1[i]*R_3K)/(TL431_V-AD_T1[i])*1000;//乘1000是因为算出来是千欧为单位的，要转化成欧姆
		R_value2[i] = (AD_T2[i]*R_3K)/(TL431_V-AD_T2[i])*1000;//乘1000是因为算出来是千欧为单位的，要转化成欧姆
		
        PT_VALUE_2_TEMP[i]=R_value1[i] * (1000 /Param.Correct[i]);//计算电阻值
        PT_VALUE_1_TEMP[i]=R_value2[i] * (1000 /Param.Correct[i]);//计算电阻值
    }
}

uint16_t index_l, index_r;
/**
 * @brief 计算出PT1000的温度
 *
 * @param value_adc adc读到的电阻值
 * @return uint16_t 温度或者状态
 */
uint16_t AFE_GetTemperature(float value_adc)
{
    uint16_t R100k_Tab_Size = 423;
    int temp = 0;
    if (value_adc < Temp_map[0])
    {
        return 1;
    }

    else if (value_adc > Temp_map[R100k_Tab_Size - 1])
    {
        return 2;
    }

    index_l = 0;
    index_r = R100k_Tab_Size - 1;
    for (; index_r - index_l > 1;)
    {
        if ((value_adc <= Temp_map[index_r]) && (value_adc > Temp_map[(index_l + index_r) % 2 == 0 ? (index_l + index_r) / 2 : (index_l + index_r) / 2]))
        {
            index_l = (index_l + index_r) % 2 == 0 ? (index_l + index_r) / 2 : (index_l + index_r) / 2;
        }
        else
        {
            index_r = (index_l + index_r) / 2;
        }
    }
    if(value_adc <= 1378.56f)
    {
        if (Temp_map[index_l] == value_adc)
        {
            temp = (((int)index_l) - 22) * 10; // rate *10
        }
        else if (Temp_map[index_r] == value_adc)
        {
            temp = (((int)index_r) - 22) * 10; // rate *10
        }
        else
        {
            if (Temp_map[index_r] - Temp_map[index_l] == 0)
            {
                temp = (((int)index_l) - 22) * 10; // rate *10
            }
            else
            {
                temp = (((int)index_l) - 22) * 10 + ((value_adc - Temp_map[index_l]) * 100 + 5) / 10 / (Temp_map[index_r] - Temp_map[index_l]);
            }
        }
    }
    else//大于一百不显示小数点
    {
        if (Temp_map[index_l] == value_adc)
        {
            temp = (((int)index_l) - 22) * 10; // rate *10
        }
        else if (Temp_map[index_r] == value_adc)
        {
            temp = (((int)index_r) - 22) * 10; // rate *10
        }
        else
        {
            temp = (((int)index_l) - 22) * 10; // rate *10
        }
    }
        

    return temp;
}

/*
*****************************************************************
 * 函数原型：void Read_Temp(float dT)
 * 功    能：读取温度-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
	static float T;
    T += dT;
        
    if(T >= 1.0f)
    {
        for(uint8_t i = 0;i<Motor_Num;i++)
        {
            if(PT_VALUE_1_TEMP[i] < 2200)//假如插入外部探头
                Work_Num[i].Temp.Rel = Work_Num[i].Temp.Outside;//真实温度显示外部探头测的温度
            else//假如没有插入外部探头
                Work_Num[i].Temp.Rel = Work_Num[i].Temp.Mesa;//真实温度显示台面温度
        } 
        T = 0;
    }
}

/**
 * @brief ADC和DMA的初始化
 * 
 */
void ADCDMA_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1);//校准
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Val, AD_LEN);//用DMA获取ADC的值
	
    for(uint8_t i = 0; i < 100; i++)
	{
        AFE_Sample_Handler();//计算阻值
        for(uint8_t j = 0;j<Motor_Num;j++)
        {
            Work_Num[j].Temp.Outside = AFE_GetTemperature(PT_VALUE_1_TEMP[j]);//外部温度
            Work_Num[j].Temp.Mesa = AFE_GetTemperature(PT_VALUE_2_TEMP[j]);//台面温度
            Read_Temp(0.6f);
            Work_Num[j].Temp.Display_Rel = Work_Num[j].Temp.Rel;
        }
	}
}

/*
*****************************************************************
 * 函数原型：float Get_ADCVal(int16_t temp)
 * 功    能：查表读ADC值
*****************************************************************
*/
float Get_ADCVal(int16_t temp)
{
	int16_t adc,adc1;
	float val2;
	int16_t val3,val1;
	
	val3 = (temp/10)+48;
	val2 = (float)(temp%10)/10;
	
	val1 = ((temp+10)/10)+48;
	
	adc = Temp_map[val3];
	adc1 = Temp_map[val1];
	return adc+((adc1-adc)*val2);
}

/**
 * @brief PT1000任务
 * 
 */
void PT1000_Task(void *p)
{ 
    while(1)
    {
        for(uint8_t i = 0;i<Motor_Num;i++)
        {
            AFE_Sample_Handler();//计算阻值
            Work_Num[i].Temp.Outside = AFE_GetTemperature(PT_VALUE_1_TEMP[i]);//外部温度
            Work_Num[i].Temp.Mesa = AFE_GetTemperature(PT_VALUE_2_TEMP[i]);//台面温度
        }
        Read_Temp(0.01f);
        vTaskDelay(10);
    }
}

