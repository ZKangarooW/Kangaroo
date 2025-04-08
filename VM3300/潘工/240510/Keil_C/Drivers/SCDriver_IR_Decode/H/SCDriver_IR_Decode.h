#ifndef _SCDriver_IR_Decode_H_
#define _SCDriver_IR_Decode_H_
//<<<Use SPTML>>>
#include "include.h"
#define SCDriver_IR_Pin P15//SCDriver_IR_Pin 
#define SCDriver_IR_Pin_INIT 0x0120//SCDriver_IR_Pin_INIT 
#define SCD_IR_DECODE_INIT 0x0120//SCD_IR_DECODE_INIT 
extern unsigned char SCD_IR_GetReceiveFlag();
extern void SCD_IR_Decode();
extern unsigned char SCD_IR_Decode_ReadValue(unsigned char i);
extern void SCD_IR_BaseTime();
extern void SCD_IR_Decode_Init();
//<<<end of SPTML>>>
#endif
