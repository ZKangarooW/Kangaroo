
;以下地址寄存器已被触摸库使用，请注意使用
;0X30-0X39, 0X70-0X75, 0XB0-0XEF, 0X50-0X6F @ 12Key

#pragma	ram 0x70-0x75
#pragma	ram 0x30-0x39

#if	C_KCOUNT > 0
#pragma	ram 0xb0-0xb7
#endif

#if	C_KCOUNT > 1
#pragma	ram 0xb8-0xbf
#endif

#if	C_KCOUNT > 2
#pragma	ram 0xc0-0xc7
#endif

#if	C_KCOUNT > 3
#pragma	ram 0xc8-0xcf
#endif

#if	C_KCOUNT > 4
#pragma	ram 0xd0-0xd7
#endif

#if	C_KCOUNT > 5
#pragma	ram 0xd8-0xdf
#endif

#if	C_KCOUNT > 6
#pragma	ram 0xe0-0xe7
#endif

#if	C_KCOUNT > 7
#pragma	ram 0xe8-0xef
#endif

#if	C_KCOUNT > 8
#pragma	ram 0x68-0x6f
#endif

#if	C_KCOUNT > 9
#pragma	ram 0x60-0x67
#endif

#if	C_KCOUNT > 10
#pragma	ram 0x58-0x5F
#endif

#if	C_KCOUNT > 11
#pragma	ram 0x50-0x58
#endif

