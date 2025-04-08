#include "REL_Sender.h"
#include <stdlib.h>
#include "Touch_Kscan_Library.h"

#define PACK_SEND_COUNT_ONCE	2

#if (C_KEY_TOTAL % PACK_SEND_COUNT_ONCE)
	#define PACK_IDX_MAX 			(C_KEY_TOTAL / PACK_SEND_COUNT_ONCE)
	#define PACK_SEND_COUNT_FINAL	(C_KEY_TOTAL % PACK_SEND_COUNT_ONCE)
#else
	#define PACK_IDX_MAX 			((C_KEY_TOTAL-1) / PACK_SEND_COUNT_ONCE)
	#define PACK_SEND_COUNT_FINAL	PACK_SEND_COUNT_ONCE
#endif

#ifdef	VOL_VALUE
	#define REL_TYPE_ID_USE	0x01
#else		
	#define REL_TYPE_ID_USE	0x00
#endif

typedef struct _PackStrcut
{
	u16 baseLine;					//基准值
	u16 rawData;					//滤波值
	#ifdef VOL_VALUE
	u16 noiseData;				 	//噪声值
	#endif
}PackStrcut;

void REL_SenderLoop()
{
	static bit bSend = 0;
	bSend = ~bSend;
	if(bSend == 0) return;	
	
	static u8 curIdx = 0;
	static u8 packIdx = 0;
	
	u8 thisSendCount;	
	PackHeader packHeader;
	PackStrcut packStrcut;

	#ifdef VOL_VALUE
	packHeader.extData[0] = VOL_VALUE;
	#else
	packHeader.extData[0] = 0;
	#endif
	
	// 填写头部数据
	packHeader.m.typeId = REL_TYPE_ID_USE;
	packHeader.m.packIdxMax = PACK_IDX_MAX;
	packHeader.m.packIdx = packIdx;
	
	if(packIdx == PACK_IDX_MAX)
	{
		thisSendCount = PACK_SEND_COUNT_FINAL;
		packHeader.length = sizeof(packHeader) + sizeof(packStrcut) * PACK_SEND_COUNT_FINAL + 1;
	}
	else
	{
		thisSendCount = PACK_SEND_COUNT_ONCE;
		packHeader.length = sizeof(packHeader) + sizeof(packStrcut) * PACK_SEND_COUNT_ONCE + 1;
	}
	
	// 开始发送
	REL_SendStart(packHeader);
	do
	{
		packStrcut.baseLine = KeyReference[curIdx];							//基准值
		#ifdef VOL_VALUE
			packStrcut.rawData = KeyOldValue[curIdx];						//EMC库滤波值
			packStrcut.noiseData = abs(KeySum0[curIdx] - KeySum1[curIdx]);	//噪声值	
		#else
			packStrcut.rawData = KeyOldValue0[curIdx];						//普通库滤波值
		#endif						
		REL_SendNext(packStrcut);
		
		thisSendCount--;
		curIdx++;		
	}while(thisSendCount != 0);
	REL_SendEnd();	
	
	// 是否最后一包
	if(packIdx == PACK_IDX_MAX)
	{
		packIdx = 0;
		curIdx = 0;
	}
	else
	{
		packIdx++;
	}
}
