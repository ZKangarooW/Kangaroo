#ifndef __PID_H__
#define	__PID_H__

#include "include.h"

/**********�궨��************/
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/

void controlLoop(void);
#endif
