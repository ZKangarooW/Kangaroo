#ifndef __CTRL_PROTOCOL_H__
#define	__CTRL_PROTOCOL_H__

#include "include.h"

/**********�궨��************/
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint8_t Receive_ok;
/**********ȫ�ֺ���**********/
void Data_Receive(uint8_t data);

#endif
