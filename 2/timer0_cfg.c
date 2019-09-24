/****************************************
 *
 *  File Name: timer0_cfg.c
 *
 *  Created on: Sep 16, 2019
 *
 *  Author: Stawro Walaa
 *
 ****************************************/

#include "timer0_cfg.h"


/****************************************************************************
 * Configuration Structure = {	
								Mode  ( Normal,PWM,CTC,PhaseCorrectPWM ) ,

 *								Prescaller(
 *								Noclock ,
 *								NoPrescaller ,
 *								Prescaller_8 ,
 *								Prescaller_64 ,
 *								Prescaller_256 ,
 *								 Prescaller_1024 ),
 *
 *								Interrupt( Off, overflow , compare match ),
 *
 *								CTC Modes( Disconnected , Toggle , Clear , Set ),
 *
 *								FastPwm Modes( Disconnected , Clear , Set ),
 *
 *								PhaseCorrect Modes( Disconnected , Clear , Set ),
 *								
 *								};
 *					Note that timer ISR Call every 1 millisecond
 ***********************************************************************************/
		
		
StrTimer0_config_t Timer0Cfg = {
							   TIMER0_Normal_Mode,
							   TIMER0_Prescaller_8,
							   TIMER0_INT_OV,
							   TIMER0_CTC_Disconnected,
							   TIMER0_FastPWM_Disconnected,
							   TIMER0_PhaseCorrectPWM_Disconnected
							   };
