
#ifndef	_TOUCH_KSCAN_CONST_H_
#define	_TOUCH_KSCAN_CONST_H_
;----------------------------------------------------------
;MCU所有按键通道定义
C_KCHS0		DEF         0050H
C_KCHS1     DEF         0051H
C_KCHS2     DEF         0052H
C_KCHS3     DEF         0053H
C_KCHS4     DEF         0054H
C_KCHS5     DEF         0055H
C_KCHS6     DEF         0056H
C_KCHS7     DEF         0057H
C_KCHS8     DEF         0058H
C_KCHS9     DEF         0059H
C_KCHS10    DEF         005AH
C_KCHS11    DEF         005BH
C_KCHS12    DEF         005CH
C_KCHS13    DEF         005DH
C_KCHS14    DEF         005EH
C_KCHS15    DEF         005FH
;----------------------------------------------------------
;MCU触摸通道口电容定义
C_KCAP_0	DEF			B'00000010' ;按键口不接电容
C_KCAP_1	DEF			B'00001010' ;按键口接电容c*1
C_KCAP_2	DEF			B'00010010' ;按键口接电容c*2
C_KCAP_3	DEF			B'00011010' ;按键口接电容c*3
C_KCAP_4	DEF			B'00100010' ;按键口接电容c*4
C_KCAP_5	DEF			B'00101010' ;按键口接电容c*5
C_KCAP_6	DEF			B'00110010' ;按键口接电容c*6
C_KCAP_7	DEF			B'00111010' ;按键口接电容c*7
;----------------------------------------------------------
#endif