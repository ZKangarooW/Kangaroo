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

ADC_Filter_t adc_filters[MAX_FILTER_CHANNELS];

/**********全局变量**********/
float PT_VALUE_1_TEMP;//外部PT1000探头阻值
float PT_VALUE_2_TEMP;//台面PT1000探头阻值

/**********局部变量**********/
uint16_t ADC_Val[AD_LEN];           // ADC采样值数组 [0:台面温度ADC值, 1：外部探头ad值, 2:内部参考电压ADC值]
float TL431_V;                      // TL431基准电压计算值(2.5V)
float Vref_AD;                      // 单片机内部参考电压ADC值
float VDD_Actual;                   // 单片机实际VDD供电电压
float ADC_Measured_Voltage[2];      // ADC测量电压值
float ADC_Calib;                    // ADC校准系数
float ADC_Val_Avg[3];               // 滤波后ADC平均值 [0:台面温度ADC]
float AD_T[2];                      // ADC转换后的电压值
float R_value[2];                   // PT1000探头阻值

/*
*****************************************************************
 * 函数名称：ADC_MultiChannel_Filter
 * 功能描述：多通道ADC滑动平均滤波器
 * 输入参数：channel - 通道编号(0-7), val - ADC原始采样值
 * 返回值：滤波后的ADC值
 * 调用说明：适用于多通道ADC数据平滑处理
*****************************************************************
*/
int ADC_MultiChannel_Filter(uint8_t channel, uint16_t val)
{
    if (channel >= MAX_FILTER_CHANNELS) 
	{
        return val; // 通道号超限，返回原始采样值
    }
    
    ADC_Filter_t *filter = &adc_filters[channel];
    
    // 缓冲区已满时，移除最早的数据点
    if (filter->buffer_full) 
	{
        filter->running_sum -= filter->buffer[filter->write_index];
    }
    
    // 添加新采样值到缓冲区并更新累加和
    filter->buffer[filter->write_index] = val;
    filter->running_sum += val;
    
    // 更新环形缓冲区写入索引
    filter->write_index++;
    if (filter->write_index >= FILTER_WINDOW_SIZE) 
	{
        filter->write_index = 0;
        filter->buffer_full = 1;  // 标记缓冲区已填满
    }
    
    // 计算滑动平均值
    uint32_t filtered_value;
    if (filter->buffer_full) 
	{
        filtered_value = filter->running_sum / FILTER_WINDOW_SIZE;  // 满窗口平均
    } 
	else 
	{
        filtered_value = filter->running_sum / filter->write_index; // 部分窗口平均
    }
    
    return (int)filtered_value;
}

/*
*****************************************************************
 * 函数名称：ADCDMA_Init
 * 功能描述：ADC和DMA模块初始化
 * 调用说明：系统启动时调用一次
*****************************************************************
*/
void ADCDMA_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc);           // ADC校准
    HAL_TIM_Base_Start_IT(&htim15);               // 启动TIM15定时器中断
    HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADC_Val, AD_LEN);  // 启动ADC DMA传输
	for(uint8_t i = 0; i < 200; i++)
	{
		Read_Temp(0.6f);
	}
	Temp.Rel = 0;
}

/*
*****************************************************************
 * 函数名称：Get_Actual_VDD_Voltage
 * 功能描述：获取单片机实际VDD供电电压
 * 返回值：实际VDD电压值(伏特)
 * 调用说明：基于内部参考电压计算
*****************************************************************
*/
float Get_Actual_VDD_Voltage(void) 
{
    uint16_t adc_raw_vrefint = ADC_Val_Avg[2];    // 内部参考电压ADC值
    
    // 防止除零错误
    if (adc_raw_vrefint == 0) 
	{
        return 3.3f; // 返回默认VDD电压值
    }

    // 计算实际VDD电压: VDD = 3.3V * (校准值/测量值)
    float vdd_actual = 3.3f * ((float)VREFINT_CAL / (float)adc_raw_vrefint);
    return vdd_actual;
}

/*
*****************************************************************
 * 函数名称：PT1000_Resistance_Calculation
 * 功能描述：PT1000温度探头阻值计算处理
 * 调用说明：ADC采样完成后调用
*****************************************************************
*/
void PT1000_Resistance_Calculation(void)
{
    ADC_Val_Avg[0] = ADC_MultiChannel_Filter(0, ADC_Val[0]);// 台面温度ADC值滤波
    ADC_Val_Avg[1] = ADC_MultiChannel_Filter(1, ADC_Val[1]);//外部温度ADC值滤波
	
    // 获取实际VDD电压
    VDD_Actual = Get_Actual_VDD_Voltage();
    
    // PT1000校准参数计算
    Calibration.gain = (2000.0f - 1000.0f) / (Param.Correct[1] - Param.Correct[0]);// 增益系数
    Calibration.offset_temp = 1000.0f - (Param.Correct[0] * Calibration.gain);   // 偏移补偿
    
    // ADC值转换为电压值
    ADC_Measured_Voltage[0] = ((float)ADC_Val_Avg[0] / 4096.0f) * VDD_Actual * ADC_Calib;
	ADC_Measured_Voltage[1] = ((float)ADC_Val_Avg[1] / 4096.0f) * VDD_Actual * ADC_Calib;
    
    // 计算分压网络电压
    AD_T[0] = ADC_Measured_Voltage[0] / OP_Value + (R_910R / (R_3K + R_910R) * TL431_V);
	AD_T[1] = ADC_Measured_Voltage[1] / OP_Value + (R_910R / (R_3K + R_910R) * TL431_V);
    
    // 计算PT1000探头阻值(欧姆)
    R_value[0] = (AD_T[0] * R_3K) / (TL431_V - AD_T[0]) * 1000.0f;
    R_value[1] = (AD_T[1] * R_3K) / (TL431_V - AD_T[1]) * 1000.0f;
	
    // 阻值滤波和校准
    PT_VALUE_1_TEMP = R_value[1] * Calibration.gain + Calibration.offset_temp;
	PT_VALUE_2_TEMP = R_value[0] * Calibration.gain + Calibration.offset_temp;
}

/** 
 * @brief 根据PT1000阻值查询温度值
 * @param resistance PT1000探头阻值(欧姆)
 * @return 温度值(放大10倍的整数值)
 * @note 使用查表法和线性插值计算温度
 */
uint16_t PT1000_Get_Temperature(float resistance) 
{
    const uint16_t table_size = 423;      // 温度-阻值映射表大小
    const float min_temp = -22.0f;        // 最低温度值
    
    // 边界检查：低于最低阻值
    if (resistance < Temp_map[0]) 
	{
        return 0; // 返回最低温度
    }
    
    // 边界检查：高于最高阻值
    if (resistance > Temp_map[table_size - 1]) 
	{
        return (uint16_t)((min_temp + table_size - 1) * 10); // 返回最高温度
    }

    // 顺序查找匹配的阻值区间
    uint16_t index = 0;
    for (index = 0; index < table_size - 1; index++) 
	{
        if (resistance >= Temp_map[index] && resistance < Temp_map[index + 1]) 
		{
            break;
        }
    }

    // 线性插值计算温度
    float temp_l = min_temp + (float)index;           // 区间左端温度
    float temp_r = min_temp + (float)index + 1.0f;    // 区间右端温度
    float res_l = Temp_map[index];                    // 区间左端阻值
    float res_r = Temp_map[index + 1];                // 区间右端阻值
    
    // 防止除零错误
    if (fabs(res_r - res_l) < 0.001f) 
	{
        // 100℃以下保持小数，100℃以上取整
        if (temp_l < 100.0f) 
        {
            return (uint16_t)(temp_l * 10);
        }
        else 
        {
            return (uint16_t)(roundf(temp_l)) * 10;
        }
    }
    
    // 线性插值公式: temp = temp_l + (R - R_l) * (temp_r - temp_l) / (R_r - R_l)
    float temperature = temp_l + ((resistance - res_l) * (temp_r - temp_l)) / (res_r - res_l);
    // 100℃以下保持小数点精度，100℃以上取整
    if (temperature < 100.0f) 
    {
        return (uint16_t)(temperature * 10)+10; // 返回放大10倍的整数值(保留1位小数)
    }
    else 
    {
        return (uint16_t)((roundf(temperature)) * 10)+10; // 返回整数温度值(放大10倍)
    }
}

/*
*****************************************************************
 * 函数名称：CelsiusToFahrenheit
 * 功能描述：摄氏度转华氏度温度转换
 * 输入参数：type - 转换类型, celsius - 摄氏度温度值
 * 返回值：转换后的温度值
 * 调用说明：type=1:摄氏转华氏, type=0:直接返回
*****************************************************************
*/
float CelsiusToFahrenheit(uint8_t type, int16_t celsius) 
{
    if (type) 
	{
        return ((float)celsius * 90.0f / 50.0f) + 320.0f;  // 摄氏转华氏公式
    } 
	else 
	{
        return celsius;  // 直接返回摄氏温度
    }
}

/*
*****************************************************************
 * 函数名称：Read_Temp
 * 功能描述：温度读取任务(10ms周期)
 * 输入参数：dT - 时间增量(秒)
 * 调用说明：每10ms调用一次
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
//    float TL431_ADC_Value;  // TL431基准电压ADC值
    
    T += dT;
	
    // 内部参考电压ADC值滤波
    Vref_AD = ADC_MultiChannel_Filter(2, ADC_Val[2]);
	
    // ADC校准系数计算
    ADC_Calib = (float)VREFINT_CAL / (float)Vref_AD;
    
    // TL431基准电压ADC值滤波
//    TL431_ADC_Value = ADC_MultiChannel_Filter(1, ADC_Val[1]);
    
    // 计算TL431实际电压值
//    TL431_V = (TL431_ADC_Value / Vref_AD) * Vref * ADC_Calib;
	TL431_V = 2.491f;
    
    // PT1000阻值计算
    PT1000_Resistance_Calculation();
    
    // 每秒更新一次温度显示
    if (T >= 1.0f) 
	{		
		Temp.Outside = PT1000_Get_Temperature(PT_VALUE_1_TEMP);//外部温度
		Temp.Mesa = PT1000_Get_Temperature(PT_VALUE_2_TEMP);//台面温度
        if(PT_VALUE_1_TEMP < 2200)//假如插入外部探头
			Temp.Rel = Temp.Outside;//真实温度显示外部探头测的温度
		else//假如没有插入外部探头
			Temp.Rel = Temp.Mesa;//真实温度显示台面温度
        T = 0;
    }
}
