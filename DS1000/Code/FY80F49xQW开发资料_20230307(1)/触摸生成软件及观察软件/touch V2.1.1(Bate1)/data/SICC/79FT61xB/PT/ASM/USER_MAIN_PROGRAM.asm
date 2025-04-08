
		#INCLUDE		CMS79FT616B.H

		#INCLUDE		"Touch_Kscan_Library.h"
		#include		"SendTouchKey_79FT61xB.h"
;**********************************************
;**********************************************


GPR0		EQU 		?	       
GPR1		EQU 		?        
TCOUNT		EQU 		？	
TEMP        EQU         ?
COUNT       EQU         ?

KEYF_OLD	EQU			?
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
		SUBIA		07FH				;20-7F,A0-FF,120-17F
		SNZB 		STATUS,Z
		JP  		CLR_RAM_LOOP
		SZB 		FSR,7
		JP  		CLR_RAM_H
		LDIA		20H
		SZB 		STATUS,IRP
		JP			CLR_RAM_BACK		;第4页不用清
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
INIT_LOOP:						;上电延时9*256*256/4=150MS
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
		LD  		PR2,A
		LDIA		B'00000101'
		LD  		T2CON,A
		LDIA		02H
		LD			PIE1,A
		LDIA		0C0H
		LD  		INTCON,A		;定时2中断使能
		LDIA		0X01
		LD			WDTCON,A
		CLRWDT
		CLR			OPTION_REG
		CLRWDT
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
		LDIA		0X01
		LD			WDTCON,A
		CLRWDT
		CLR			OPTION_REG
		CLRWDT
		LDIA		.125			;16M下125US
		LD  		PR2,A
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
;TK_FLAG,B_KERR:复位按键标志，此标志位为1，则触摸程序会将触摸相关寄存器清0,完成后b_kerr清0
;*****************************************
MAINK:
		LD			A,KEYF
		SZB			STATUS,Z
		JP			MAINK_NO
		
		LD			A,KEYF
		XORA		KEYF_OLD		;相同
		SZB			STATUS,Z
		JP			MAINK_BACK
		
		LD			KEYF_OLD,A
		
		LDIA		01H
		SNZB		KEYF_OLD,0
		JP			$+3
		SZB			KEYF,0
		XORR		PORTA
		
		LDIA		02H
		SNZB		KEYF_OLD,1
		JP			$+3
		SZB			KEYF,1
		XORR		PORTA

		LDIA		04H
		SNZB		KEYF_OLD,2
		JP			$+3
		SZB			KEYF,2
		XORR		PORTA
		
		LDIA		08H
		SNZB		KEYF_OLD,3
		JP			$+3
		SZB			KEYF,3
		XORR		PORTA
		
		LD			A,KEYF
		LD			KEYF_OLD,A
		JP			MAINK_BACK
MAINK_NO:
		CLR			KEYF_OLD
MAINK_BACK:
        RET
;********************************************
;调用按键库文件
;********************************************
KSCAN：
		#INCLUDE	"CMS_CheckTouch_79FT61xB_V1.02.Lib"
;********************************************
;********************************************
#if (CMS_DEBUG_MODE == 1)
		#INCLUDE 	"SendTouchKey_79FT61xB.asm"
#endif
;********************************************
;********************************************
;********************************************
		END

