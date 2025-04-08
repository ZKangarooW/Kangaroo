#ifndef _DELAY_H_
#define _DELAY_H_

//看门狗溢出时间约350ms，关总中断，清看门狗，使能看门狗复位，开总中断
#define clrwdt()		\	
{                   \
	u8 ea_tmp;        \
	ea_tmp = EA;      \
	CKCON |= 0xC0;    \
	CKCON &= 0xDF;    \
	EA = 0;           \
	_nop_();					\
	_nop_();					\
	TA=0xAA;          \
	TA=0x55;          \
	WDCON = 0x03;     \
	EA = ea_tmp;      \
}

extern void Delay_ms(unsigned char time);

#endif
