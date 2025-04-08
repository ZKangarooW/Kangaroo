
		#INCLUDE		CMS79FT628.H

		#INCLUDE		"Touch_Kscan_Library.h"
		#include		"SendTouchKey_79FT62x.h"
;**********************************************
;**********************************************
Buz			EQU		PORTB,2

PO_SEGA		EQU		PORTD,6
PO_SEGB		EQU		PORTB,0
PO_SEGC		EQU		PORTD,4
PO_SEGD		EQU		PORTD,1
PO_SEGE		EQU		PORTD,5
PO_SEGF		EQU		PORTB,1
PO_SEGG		EQU		PORTD,3
PO_SEGDP	EQU		PORTD,2


GPR0		EQU 		?	       
GPR1		EQU 		?        
TCOUNT		EQU 		?	
TEMP        EQU         ?
COUNT       EQU         ?

KEYF_OLD	EQU			?
KEYF1_OLD	EQU			?

BUZTIMEH	EQU			?
BUZTIMEL	EQU			?
RBEEP		EQU			?
RBEEPF		EQU			RBEEP,0
;--------------------------------------------
;工作RAM
;**************************************
;*********************************************************
		ORG 		00H

   		JP  		START
		ORG 		04H
;***************************************************

        LD  		GPR0,A			;中断现场保护
		SWAPR		GPR0
		SWAPA		STATUS
		LD  		GPR1,A
;********************************************
INT_TMR2:
		CLR 		PIR1			;清中断响应标志位
		INCR		TCOUNT
;********************************************
BUZ_SET:
		SNZB		RBEEPF
		JP			BUZ_SET_BACK
		LDIA		0X04
		XORR		PORTB
		SZDECR		BUZTIMEL
		JP			BUZ_SET_BACK
		SZDECR		BUZTIMEH
		JP			BUZ_SET_BACK
		CLRB		Buz
		CLRB		RBEEPF
BUZ_SET_BACK:
;********************************************
INT_EXIT:
		SWAPA		GPR1
		LD  		STATUS,A
		SWAPA		GPR0
		RETI
;********************************************

;********************************************
;********************************************
		
;********************************************
START:
		NOP
		CLRWDT
;-----------初始化I/O------------------------
		LDIA		071H
		LD			OSCCON,A
		
		LDIA		00H
		LD  		PORTA,A		
		LDIA		00H
		LD  		TRISA,A
	    LDIA		00H
		LD  		PORTA,A	
		
		LDIA		00H		
		LD  		PORTB,A
		LDIA		00H	
		LD  		TRISB,A
		LDIA		00H		
		LD  		PORTB,A	
		
		LDIA		00H
		LD  		PORTC,A
		LDIA		00H		
		LD  		TRISC,A			
	    LDIA		00H
		LD  		PORTC,A
		
		LDIA		00H
		LD  		PORTD,A
		LDIA		00H		
		LD  		TRISD,A			
	    LDIA		00H
		LD  		PORTD,A
		
		CLR			INTCON
;-----------清寄存器----------------------------
		CLRB		STATUS,IRP
CLR_RAM：
		LDIA		1FH					;从20H开始
		LD  		FSR,A
CLR_RAM_LOOP
		INCR		FSR
		CLR 		INDF
		LDIA		07FH
		ANDA		FSR
		SUBIA		07FH				;20-7F,A0-FF,120-17F,1A0-1FF
		SNZB 		STATUS,Z
		JP  		CLR_RAM_LOOP
		SZB 		FSR,7
		JP  		CLR_RAM_H
		LDIA		20H
		SZB 		STATUS,IRP
		LDIA		18H
		ADDR		FSR
		JP  		CLR_RAM_LOOP
CLR_RAM_H:						
		SZB 		STATUS,IRP			;判断是否已经是第3-4BANK
		JP  		CLR_RAM_BACK		;已经是第3-4BANK,清RAM结束
		SETB		STATUS,IRP			;不是3-4BANK,设置BANK标志位，开始清3-4BANK的RAM
		JP  		CLR_RAM
CLR_RAM_BACK:
		CLRB		STATUS,IRP
;----------------------------------------------
INIT_LOOP:							;上电延时9*256*256/4=150MS(16M)
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		SZDECR		COUNT
		JP  		INIT_LOOP
		CLRWDT
	
		SZDECR		TEMP
		JP  		INIT_LOOP
;************************************************
;-----------------------------------------------
INIT_RAM:
		LDIA		.125			;16M下125US
		LD  		PR2,A			;TMR2设置成125US
		LDIA		B'00000101'
		LD  		T2CON,A
		LDIA		02H
		LD			PIE1,A
		LDIA		0C0H
		LD  		INTCON,A		;定时2中断使能
		LDIA		0x01
		LD			WDTCON,A
		CLR			OPTION_REG
		SETB		RBEEPF
		LDIA		.2
		LD			BUZTIMEH,A
		CLR			BUZTIMEL
;********************************************
;********************************************
;********************************************
MAIN:
		LDIA		.20				;125us*20=2.5ms一个主循环
		SUBA		TCOUNT
		SNZB		STATUS,C
		JP  		MAIN
;********************************************
		CLR 		TCOUNT
		CLRWDT
;********************************************
;********************************************
MAIN_SUB:
		CALL		SET_SYS
		CALL  		KSCAN           ;触摸扫描程序	
		CALL        MAINK			;触摸处理程序
		#IF (CMS_DEBUG_MODE == 1)
			CALL		SEND_TOUCHKEY
		#ENDIF
		JP  		MAIN
;********************************************
;系统寄存器设置
;********************************************
SET_SYS:		
 	    LDIA		00H
		LD  		TRISA,A
		LD  		TRISB,A
		LD  		TRISC,A
		LD  		TRISD,A
		LDIA		0x01
		LD			WDTCON,A
		CLR			OPTION_REG
		LDIA		.125			;16M下125US
		LD  		PR2,A			;TMR2设置成125US
		LDIA		02H
		LD			PIE1,A
		LDIA		0C0H
		LD  		INTCON,A		;定时2中断使能
		LDIA		B'00000101'
		XORA		T2CON
		SZB			STATUS,Z
		RET
		LDIA		B'00000101'
		LD  		T2CON,A
		RET
;*****************************************
;根据KEYF和KEYF1判断有没有按键
;"TK_FLAG,B_KERR" 置1，则复位按键各参数
;*****************************************
MAINK:
		LD			A,KEYF
		#if	C_KCOUNT > 8
		ORA			KEYF1
		#endif
		SZB			STATUS,Z
		JP			MAINK_NO
		
		LD			A,KEYF
		XORA		KEYF_OLD		;相同
		SZB			STATUS,Z
		JP			MAINK_HIGH
		LD			KEYF_OLD,A
		
		SNZB		KEYF_OLD,0
		JP			MAINK_KEY2
		SNZB		KEYF,0
		JP			MAINK_KEY2
		LDIA		40H
		XORR		PORTD
		LDIA		.2
		LD			BUZTIMEH,A
		CLR			BUZTIMEL
		SETB		RBEEPF
MAINK_KEY2:
		SNZB		KEYF_OLD,1
		JP			MAINK_KEY3
		SNZB		KEYF,1
		JP			MAINK_KEY3
		LDIA		01H
		XORR		PORTB
		LDIA		.2
		LD			BUZTIMEH,A
		CLR			BUZTIMEL
		SETB		RBEEPF
MAINK_KEY3:
		SNZB		KEYF_OLD,2
		JP			MAINK_KEY4
		SNZB		KEYF,2
		JP			MAINK_KEY4
		LDIA		10H
		XORR		PORTD
		LDIA		.2
		LD			BUZTIMEH,A
		CLR			BUZTIMEL
		SETB		RBEEPF
MAINK_KEY4:
		SNZB		KEYF_OLD,3
		JP			MAINK_KEY5
		SNZB		KEYF,3
		JP			MAINK_KEY5
		LDIA		02H
		XORR		PORTD
		LDIA		.2
		LD			BUZTIMEH,A
		CLR			BUZTIMEL
		SETB		RBEEPF
MAINK_KEY5:
		SNZB		KEYF_OLD,4
		JP			MAINK_KEY6
		SNZB		KEYF,4
		JP			MAINK_KEY6
MAINK_KEY6:
		SNZB		KEYF_OLD,5
		JP			MAINK_KEY7
		SNZB		KEYF,5
		JP			MAINK_KEY7
MAINK_KEY7:
		SNZB		KEYF_OLD,6
		JP			MAINK_KEY8
		SNZB		KEYF,6
		JP			MAINK_KEY8
MAINK_KEY8:
		SNZB		KEYF_OLD,7
		JP			MAINK_KEY_END0
		SNZB		KEYF,7
		JP			MAINK_KEY_END0
MAINK_KEY_END0:
		LD			A,KEYF
		LD			KEYF_OLD,A
MAINK_HIGH:
		#if	C_KCOUNT > 8
		LD			A,KEYF1
		XORA		KEYF1_OLD
		SZB			STATUS,Z
		JP			MAINK_BACK
		LD			KEYF1_OLD,A
		
		SNZB		KEYF1_OLD,0
		JP			MAINK_KEY10
		SNZB		KEYF1,0
		JP			MAINK_KEY10
MAINK_KEY10:
		SNZB		KEYF1_OLD,1
		JP			MAINK_KEY11
		SNZB		KEYF1,1
		JP			MAINK_KEY11
MAINK_KEY11:
		SNZB		KEYF1_OLD,2
		JP			MAINK_KEY12
		SNZB		KEYF1,2
		JP			MAINK_KEY12
MAINK_KEY12:
		SNZB		KEYF1_OLD,3
		JP			MAINK_KEY_END1
		SNZB		KEYF1,3
		JP			MAINK_KEY_END1
MAINK_KEY_END1:
		LD			A,KEYF1
		LD			KEYF1_OLD,A
		#endif
		JP			MAINK_BACK
MAINK_NO:
		CLR			KEYF_OLD
		CLR			KEYF1_OLD
MAINK_BACK:
        RET
;********************************************
;调用按键库文件
;********************************************
KSCAN：
        #INCLUDE	"CMS_CheckTouch_79FT62x_V1.02.Lib"
;********************************************
;********************************************
#if (CMS_DEBUG_MODE == 1)
		#INCLUDE 	"SendTouchKey_79FT62x.asm"
#endif
;********************************************
;********************************************
;********************************************
		END

