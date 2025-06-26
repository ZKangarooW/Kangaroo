#include "Drv_HT16H25.h"

void HT16H25_SPI_Write(uint8_t *data, uint16_t size) {
  // CS建立时间 >50ns
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  Delay_us(2); 
  
  // 分段传输（防SPI FIFO溢出）
  for(uint16_t i=0; i<size; i++) {
    HAL_SPI_Transmit(&hspi2, &data[i], 1, 100);
    Delay_us(5); // 字节间隔
  }
  
  // CS保持时间 >2μs
  Delay_us(10);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}
#define PWM htim1.Instance->CCR4//motor PWM输出 （0~200）
// 3. HT16H25初始化序列
void HT16H25_Init(void) {
	HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	PWM = 30;
  // 硬件复位
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  HAL_Delay(50);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  HAL_Delay(50);
  
  // 初始化命令序列
  uint8_t init_cmds[] = {
    0x21, // 开启系统振荡器
    0xA0, // INT/ROW配置
    0x82 | 0x07, // 1/16 duty + 1/5 bias
    0x84, // A型驱动波形
    0xEF, // 最大亮度
    0x81  // 显示ON
  };
  
  for(uint8_t i=0; i<sizeof(init_cmds); i++) {
    HT16H25_SPI_Write(&init_cmds[i], 1);
    HAL_Delay(10);
  }
  
//  // 清屏
//  for(uint8_t addr=0; addr<0x10; addr++) {
//    uint8_t packet[2] = {addr & 0x0F, 0x00};
//    HT16H25_SPI_Write(packet, 2);
//  }
  for(uint8_t addr=0; addr<0x10; addr++) {
    uint8_t packet[2] = {addr, 0xFF};
    HT16H25_SPI_Write(packet, 2);
  }
}
