#ifndef _LED_H_
#define _LED_H_


extern void Led_Config(void);

extern void UpdateDisplay2(void);

void SetData1(int Data1);
void SetData2(int Data2);
void SetSpecialData1(int Data);
void SetSpecialData2(int Data);
void SetLed(int Data);
int GetData1(void);
int GetData2(void);

extern int DisplayNum[4];
extern int DisplayNum1;
extern int Num1Valid;
extern int DisplayNum2;

#endif