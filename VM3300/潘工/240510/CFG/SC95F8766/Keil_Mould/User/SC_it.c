//************************************************************
//  Copyright (c)   
//	FileName	  : SC_it.c
//	Function	  : Interrupt Service Routine
//  Instructions  :  
//  Date          : 2022/03/03
// 	Version		  : V1.0002
//*************************************************************
/********************Includes************************************************************************/
#include "SC_it.h"
#include "..\Drivers\SCDriver_list.h"
#include "HeadFiles\SC_itExtern.h"
/**************************************Generated by EasyCodeCube*************************************/
//Forbid editing areas between the labels !!!

/*************************************.Generated by EasyCodeCube.************************************/
void INT0Interrupt()		interrupt 0				
{
    TCON &= 0XFD;//Clear interrupt flag bit
	/*INT0_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*INT0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT0Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*INT0Interrupt Flag Clear end*/
}
void Timer0Interrupt()		interrupt 1			   
{
    /*TIM0_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*TIM0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
	 /*<UserCodeStart>*//*<SinOne-Tag><55>*/
    //Timer0Interrupt
    {
        /*<UserCodeStart>*//*<SinOne-Tag><15>*/
        /***User program***/
        /*<UserCodeEnd>*//*<SinOne-Tag><15>*/
        /*<Begin-Inserted by EasyCodeCube for Condition>*/
    }
    /*<UserCodeEnd>*//*<SinOne-Tag><55>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer0Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*Timer0Interrupt Flag Clear end*/		
}
void INT1Interrupt()		interrupt 2		
{
    TCON &= 0XF7;//Clear interrupt flag bit
	/*INT1_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*INT1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT1Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*INT1Interrupt Flag Clear end*/					
}
void Timer1Interrupt()		interrupt 3		
{
    /*TIM1_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*TIM1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer1Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*Timer1Interrupt Flag Clear end*/		
}
#if defined (SC92F742x) || defined (SC92F7490)
void SSI0Interrupt()		interrupt 4		
{
	/*SSI0_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*SSI0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSI0Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*SSI0Interrupt Flag Clear end*/		
}
#elif  !defined ( SC92F827X)  &&  !defined (SC92F837X)
void UART0Interrupt()		interrupt 4		
{
    /*UART0_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*UART0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*UART0Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*UART0Interrupt Flag Clear end*/		
}
#endif
void Timer2Interrupt()		interrupt 5		
{
    /*TIM2_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*TIM2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer2Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*Timer2Interrupt Flag Clear end*/	
}
void ADCInterrupt()			interrupt 6		
{
    /*ADC_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*ADC_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*ADCInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*ADCInterrupt Flag Clear end*/		
}
#if defined (SC92F854x) || defined (SC92F754x) ||defined  (SC92F844xB) || defined (SC92F744xB)||defined  (SC92F84Ax_2) || defined (SC92F74Ax_2)|| defined (SC92F846xB) || defined (SC92F746xB)\
|| defined (SC92F836xB) || defined (SC92F736xB) || defined (SC92F8003) || defined (SC92F8003B) || defined  (SC92F84Ax) || defined (SC92F74Ax) || defined  (SC92F83Ax) || defined (SC92F73Ax) \
|| defined (SC92F7003) || defined (SC92F740x) || defined (SC92FWxx) || defined (SC93F743x) || defined (SC93F833x) || defined (SC93F843x) || defined (SC92F848x) || defined (SC92F748x)|| defined (SC92F859x) \
|| defined (SC92F759x) || defined(SC92F84Hx) || defined(SC92F83Hx)|| defined(SC92F827x)|| defined(SC92F837x) ||defined(SC92F841x) || defined(SC92F741x) || defined(SC92R511x) || defined(SC92R342)
void SSIInterrupt()			interrupt 7		
{
    /*SSI_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*SSI_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSIInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*SSIInterrupt Flag Clear end*/		
}
#elif defined (SC92F742x) || defined (SC92F7490)
void SSI1Interrupt()		interrupt 7		
{
	/*SSI1_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*SSI1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*SSI1Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*SSI1Interrupt Flag Clear end*/		
}
#elif !defined (SC92F730x) && !defined (SC92F730x_2) && !defined (SC92F720x) && !defined (SC92F725X) && !defined (SC92F735X) && !defined (SC92F732X)
void USCI0Interrupt()			interrupt 7		
{
	/*USCI0_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*USCI0_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI0Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI0Interrupt Flag Clear end*/		
}
#endif
void PWMInterrupt()			interrupt 8
{
    /*PWM_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*PWM_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*PWMInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*PWMInterrupt Flag Clear end*/		
}
#if !defined (TK_USE_BTM)
void BTMInterrupt()			interrupt 9
{
	/*BTM_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*BTM_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*BTMInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*BTMInterrupt Flag Clear end*/		
}
#endif
void INT2Interrupt()		interrupt 10
{	
	/*INT2_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*INT2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*INT2Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*INT2Interrupt Flag Clear end*/		
}
#if defined (SC92F854x) || defined (SC92F754x) || defined  (SC92F844xB) || defined (SC92F744xB)||defined  (SC92F84Ax_2) || defined (SC92F74Ax_2)|| defined (SC92F859x) || defined (SC92F759x) || defined (SC92R511x)\
|| defined (SC92FWxx) || defined (SC95F8x1x) || defined (SC95F7x1x) || defined (SC95FWxx) || defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB) ||defined ( SC95F7x1xB)\
|| defined (SC95R751) || defined (SC95F7610B) || defined (SC95F7619B) || defined (SC95R602) || defined (SC95R605) || defined (SC95F8x7x) || defined (SC95F7x7x) 
void ACMPInterrupt()		interrupt 12
{
	/*ACMP_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*ACMP_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*ACMPInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*ACMPInterrupt Flag Clear end*/		
}
#endif

#if defined (SC92L853x) || defined (SC92L753x) || defined(SC92F84Hx) || defined(SC92F83Hx) || defined( SC95F8x1x) || defined(SC95F7x1x) || defined(SC95F8x2x) || defined(SC95F7x2x) ||defined(SC95FWxx) \
|| defined(SC95F8x3x) || defined(SC95F7x3x) || defined(SC95F8x6x) || defined(SC95F7x6x) || defined(SC95F8x1xB) || defined(SC95F7x1xB) || defined(SC95R751) || defined(SC95F7610B) || defined(SC95F7619B) \
|| defined(SC95FS52x) || defined(SC95R602) || defined(SC95R605) || defined(SC95F8x7x) || defined(SC95F7x7x)
void Timer3Interrupt()		interrupt 13
{
	/*TIM3_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*TIM3_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer3Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*Timer3Interrupt Flag Clear end*/		
}
void Timer4Interrupt()		interrupt 14
{
	/*TIM4_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*TIM4_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*Timer4Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*Timer4Interrupt Flag Clear end*/		
}
#if  !defined (SC92F84Hx) && !defined (SC92F83Hx)

void USCI1Interrupt()		interrupt 15		
{	
	/*USCI1_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*USCI1_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI1Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI1Interrupt Flag Clear end*/		
}
void USCI2Interrupt()		interrupt 16		
{	
	/*USCI2_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*USCI2_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI2Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI2Interrupt Flag Clear end*/		
}
#endif

#if  defined (SC92L853x) || defined (SC92L753x)
void LPDInterrupt()		interrupt 22		
{
    /*LPD_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*LPD_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*LPDInterrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*LPDInterrupt Flag Clear end*/		
}
#endif
#endif

#if  defined (SC95F8x3x) || defined (SC95F7x3x) || defined (SC95F7619B) || defined ( SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB)|| defined (SC95F7x1xB) || defined (SC95R751)
void USCI3Interrupt()		interrupt 17		
{
	/*USCI3_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*USCI3_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI3Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI3Interrupt Flag Clear end*/		
}
#if !defined (SC95R751)
void USCI4Interrupt()		interrupt 18		
{
    /*USCI4_it write here begin*/
	//Forbid editing areas between the labels !!!
    /*USCI4_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI4Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI4Interrupt Flag Clear end*/		
}
#endif
#if defined (SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB) || defined (SC95F7x1xB) 
void USCI5Interrupt()		interrupt 19		
{
    /*USCI5_it write here begin*/	
	//Forbid editing areas between the labels !!!
    /*USCI5_it write here*/
    /*<Generated by EasyCodeCube begin>*/
    /*<Generated by EasyCodeCube end>*/
    /*USCI5Interrupt Flag Clear begin*/
	//Forbid editing areas between the labels !!!
    /*USCI5Interrupt Flag Clear end*/		
}
#endif

#endif
