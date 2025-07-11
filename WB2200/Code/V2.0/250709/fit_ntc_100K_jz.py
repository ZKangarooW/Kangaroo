import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# 测量的数据：温度 (°C) 和 电阻 (Ω)
temperature_C = np.array([3, 8, 13, 18, 23, 28, 33, 36.3, 42.5, 48, 53, 58, 64, 70, 76, 82, 87, 92.6, 98])
resistance = np.array([327019, 254242, 199200, 157229, 124973, 100000, 80527, 65241, 53163, 43562, 35884, 29709, 
                       24717, 20659, 17345, 14625, 12382, 10525, 8980])
# temperature_C = np.array([0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100])
# resistance = np.array([327019, 254242, 199200, 157229, 124973, 100000, 80527, 65241, 53163, 43562, 35884, 29709, 
#                        24717, 20659, 17345, 14625, 12382, 10525, 8980, 7691, 6610])
# 转换为开尔文温度
temperature_K = temperature_C + 273.15

# Steinhart-Hart方程
def steinhart_hart(R, A, B, C):
    logR = np.log(R)  # 计算电阻的对数
    temperature_K = 1.0 / (A + B * logR + C * logR**3)  # 计算开尔文温度
    return temperature_K

# 定义优化目标函数（误差函数）
def objective(params, R, T_K):
    A, B, C = params
    T_calculated = steinhart_hart(R, A, B, C)
    return np.sum((T_calculated - T_K)**2)  # 平方误差

# 初始猜测值
initial_guess = [1e-3, 2e-4, 1e-7]

# 使用curve_fit优化A、B、C参数
params, covariance = curve_fit(steinhart_hart, resistance, temperature_K, p0=initial_guess)

# 获取拟合结果
A_fit, B_fit, C_fit = params
print(f"拟合结果: A = {A_fit}, B = {B_fit}, C = {C_fit}")

# 使用拟合结果计算温度
fitted_temperature_K = steinhart_hart(resistance, A_fit, B_fit, C_fit)
fitted_temperature_C = fitted_temperature_K - 273.15  # 转换回摄氏度

# 可视化数据和拟合曲线
plt.plot(temperature_C, resistance, 'bo', label='原始数据')  # 测量数据点
plt.plot(fitted_temperature_C, resistance, 'r-', label=f'拟合曲线: A={A_fit:.5e}, B={B_fit:.5e}, C={C_fit:.5e}')  # 拟合曲线
plt.xlabel('温度 (°C)')
plt.ylabel('电阻 (Ω)')
plt.title('NTC 温度与电阻的拟合关系')
plt.legend()
plt.grid(True)
plt.show()

# 使用拟合后的参数计算电阻为100000Ω时的温度
R_test = 100000  # 测试电阻值
calculated_temperature_K = 1.0 / (A_fit + B_fit * np.log(R_test) + C_fit * np.log(R_test)**3)
calculated_temperature_C = calculated_temperature_K - 273.15  # 转换为摄氏度

print(f"电阻 {R_test} Ω 对应的温度为: {calculated_temperature_C:.2f} °C")
