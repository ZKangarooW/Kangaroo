
		#INCLUDE		CMS8F0701A1D828SP.H

		#INCLUDE		"Touch_Kscan_Library.h"
		#INCLUDE 		"SendTouchKey_8F0701A.h"
;**********************************************
;**********************************************
Led1		EQU			PORTA,3
Led2		EQU			PORTA,2
Led3		EQU			PORTA,1
Led4		EQU			PORTA,0
Com			EQU			PORTC,0

GPR0		EQU 		?
GPR1		EQU 		?
TCOUNT		EQU 		?
TEMP        EQU         ?
TEMP1		EQU 		?
COUNT       EQU         ?

KFLAG		EQU 		?

KEYF_OLD	EQU			?
KEYF1_OLD	EQU			?

DispData	EQU			?

TABLE_SPL_BUF		EQU		?
TABLE_SPH_BUF		EQU		?
TABLE_DATAH_BUF		EQU		?
FSR_BUF		EQU				?
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
		
		LD			A,TABLE_SPL
		LD			TABLE_SPL_BUF,A
		LD			A,TABLE_SPH
		LD			TABLE_SPH_BUF,A
		LD			A,TABLE_DATAH
		LD			TABLE_DATAH_BUF,A
		LD			A,FSR
		LD			FSR_BUF,A
;********************************************
		SNZB		INTCON2,5
		JP			INT_TOUCH
INT_TMR2:
		SNZB		PIR1,1
		JP			INT_EXIT
		CLRB		PIR1,1;清中断响应标志位
		INCR		TCOUNT
		JP			INT_EXIT
;********************************************
INT_TOUCH:
		;触摸中断,PIE2的bit6为触摸中断使能位，不能在main主循环和中断里操作
		SNZB		PIR2,6
		JP			INT_EXIT
		CLRB		PIR2,6;需要清触摸中断标志
		CALL		KEY_CHECK
INT_EXIT:
		LD			A,TABLE_SPL_BUF
		LD			TABLE_SPL,A
		LD			A,TABLE_SPH_BUF
		LD			TABLE_SPH,A
		LD			A,TABLE_DATAH_BUF
		LD			TABLE_DATAH,A
		LD			A,FSR_BUF
		LD			FSR,A
		
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
		CLR			INTCON
		CLR			PIR1
		CLR			PIR2
		LDIA		01H
		LD			WDTCON,A
		CLR			OPTION_REG
		CLR			PIE1
		CLR			PIE2
		CLR			IOCB
		CLR			WPUA
		CLR			WPUB
		CLR			WPUC
		CLR			WPUD
		
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
		LDIA		03H
		LD  		TRISD,A
	    LDIA		00H
		LD  		PORTD,A
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
		LDIA		20H					;当前是7FH，增加20H，开始清A0-FF
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
INIT_LOOP:						;上电延时18*256*256/8=150mS（32M）
		JP			$+1
		JP			$+1
		JP			$+1
		JP			$+1
		JP			$+1
		JP			$+1
		JP			$+1
		NOP
		SZDECR		COUNT
		JP  		INIT_LOOP
		CLRWDT
	
		SZDECR		TEMP
		JP  		INIT_LOOP
;************************************************
;-----------------------------------------------
INIT_RAM:
		LDIA		.250			;32M下125uS
		LD  		PR2,A			;TMR2设置成125uS
		LDIA		B'00000101'
		LD  		T2CON,A
		LDIA		02H
		LD			PIE1,A
		LDIA		0C0H
		LD  		INTCON,A		;定时2中断使能
		LDIA		01H
		LD			INTCON2,A		;TM2为高优先级中断
		CLR			PIE2
		LDIA		071H
		LD			OSCCON,A
		LDIA		01H
		LD			WDTCON,A
		CLRWDT
		CLR			OPTION_REG
		
		SETB		Led1
		SETB		DispData,0
;********************************************
;********************************************
;********************************************
MAIN:
		LDIA		.32					;125us*32=4ms一个主循环
		SUBA		TCOUNT
		SNZB		STATUS,C
		JP  		MAIN
;********************************************
		CLR 		TCOUNT
		CLRWDT
;********************************************
;********************************************
MAIN_SUB:
		CALL		Display
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
		LDIA		01H
		LD			WDTCON,A
		CLRWDT
		CLR			OPTION_REG
		LDIA		.250			;32M下125US
		LD  		PR2,A			;TMR2设置成125US
		LDIA		02H
		LD			PIE1,A
		LDIA		0C0H
		LD  		INTCON,A		;定时2中断使能
		LDIA		01H
		LD			INTCON2,A		;TM2为高优先级中断
		LDIA		B'00000101'
		XORA		T2CON
		SZB			STATUS,Z
		RET
		LDIA		B'00000101'
		LD  		T2CON,A
		RET
;********************************************
;显示程序
;********************************************
Display:
		CLRB		Com
		
		SZB			DispData,0
		SETB		Led1
		SNZB		DispData,0
		CLRB		Led1
		
		SZB			DispData,1
		SETB		Led2
		SNZB		DispData,1
		CLRB		Led2
		
		SZB			DispData,2
		SETB		Led3
		SNZB		DispData,2
		CLRB		Led3
		
		SZB			DispData,3
		SETB		Led4
		SNZB		DispData,3
		CLRB		Led4
		
		LDIA		0x0F
		LD			SEGEN0,A
		LDIA		0x00
		LD			SEGEN1,A
		LDIA		0x20
		LD			SEGEN2,A
Display_Back:
		RET
;*****************************************
;根据KEYF和KEYF1判断有没有按键
;"B_KERR" 置1，则复位按键各参数
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
		
		LD			A,KEYF
		LD			KEYF_OLD,A
		
		SNZB		KEYF_OLD,0
		JP			$+3
		LDIA		01H
		XORR		DispData
		
		SNZB		KEYF_OLD,1
		JP			$+3
		LDIA		02H
		XORR		DispData
		
		SNZB		KEYF_OLD,2
		JP			$+3
		LDIA		04H
		XORR		DispData
		
		SNZB		KEYF_OLD,3
		JP			$+3
		LDIA		08H
		XORR		DispData
MAINK_HIGH:
		#if	C_KCOUNT > 8
		LD			A,KEYF1
		XORA		KEYF1_OLD		;相同
		SZB			STATUS,Z
		JP			MAINK_BACK
		LD			A,KEYF1
		LD			KEYF1_OLD,A
		
		;SNZB		KEYF1_OLD,3
		;JP			$+3
		;LDIA		01H
		;XORR		DispData
		
		JP			MAINK_BACK
		#endif
		JP			MAINK_BACK
MAINK_NO:
		CLR			KEYF_OLD
		CLR			KEYF1_OLD
MAINK_BACK:
        RET
;********************************************
;调用按键判断库文件
;********************************************
KSCAN:
        #INCLUDE	"CheckTouch_8F0701A_V1.01.lib"
;********************************************
;调用按键检测库文件
;********************************************
KEY_CHECK:
		;触摸中断,PIE2的bit6为触摸中断使能位，不能在main主循环和中断里操作
		;需要在触摸中断INT_TOUCH里清标志位PIR2,6
        #INCLUDE	"CheckTouch_8F0701A_Check_V1.01.lib"
;********************************************
#if (CMS_DEBUG_MODE == 1)
		#INCLUDE 	"SendTouchKey_8F0701A.asm"
#endif
		END

