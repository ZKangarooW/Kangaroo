#ifndef __DRV_ARRAYVISUALI_H__
#define __DRV_ARRAYVISUALI_H__

#include "include.h"

/**********�궨��************/
#define Array_Size 128

/**********�ṹ��************/
typedef struct
{
	int16_t A[Array_Size];
    int16_t Index;
}_Array_;
extern _Array_ Temp_Array;

/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void Array_Check(float dT);//������

#endif
