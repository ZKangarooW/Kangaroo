;**********************************************************
;*********************触摸按键常量文件*********************
;**********************************************************
#ifndef	_TOUCH_KSCAN_CONST_H_
#define	_TOUCH_KSCAN_CONST_H_
;----------------------------------------------------------
;MCU所有按键通道定义
C_KCHS0     DEF         0028H         ;P0,0 
C_KCHS1     DEF         0029H         ;P0,1       
C_KCHS2     DEF         002AH         ;P0,2 
C_KCHS3     DEF         002BH         ;P0,3 
C_KCHS4     DEF         002CH         ;P0,4 
C_KCHS5     DEF         002DH         ;P0,5 
C_KCHS6     DEF         002EH         ;P0,6 
C_KCHS7     DEF         002FH         ;P0,7 
C_KCHS8     DEF         0128H         ;P1,0 
C_KCHS9     DEF         0129H         ;P1,1 
C_KCHS10    DEF         012AH         ;P1,2 
C_KCHS11    DEF         012BH         ;P1,3 
C_KCHS12    DEF         012CH         ;P1,4 
C_KCHS13    DEF         012DH         ;P1,6 
C_KCHS14    DEF         012EH         ;P2,0
C_KCHS15    DEF         012FH         ;P2,1 
;----------------------------------------------------------
;MCU触摸通道口电容定义
C_KCAP_0     DEF       B'00000010' ;按键口不接电容
C_KCAP_1     DEF       B'00001010' ;按键口接电容c*1
C_KCAP_2     DEF       B'00010010' ;按键口接电容c*2
C_KCAP_3     DEF       B'00011010' ;按键口接电容c*3
C_KCAP_4     DEF       B'00100010' ;按键口接电容c*4
C_KCAP_5     DEF       B'00101010' ;按键口接电容c*5
C_KCAP_6     DEF       B'00110010' ;按键口接电容c*6
C_KCAP_7     DEF       B'00111010' ;按键口接电容c*7
;----------------------------------------------------------
#endif