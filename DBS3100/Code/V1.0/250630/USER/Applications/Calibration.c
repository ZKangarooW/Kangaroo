#include "Calibration.h"

void Calibration_Init(void)
{
    if(!Key1 && !Key2)
	{
		Calibration.Switch = 1;//如果开机按住P和Menu按键就打开校准
    }
}
