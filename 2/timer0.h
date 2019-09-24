/****************************************
 *
 *  File Name: timer0.h
 *
 *  Created on: Sep 16, 2019
 *
 *  Author: Stawro Walaa
 *
 ****************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "dio.h"
#include "timer0_cfg.h"

/*******************************************************************************
*                          Mapped Registers                                   *
*******************************************************************************/

#define		TCCR0			(*((volatile uint8 *)0x53))
#define		TCNT0			(*((volatile uint8 *)0x52))
#define		OCR0			(*((volatile uint8 *)0x5c))


#define		TIMSK			(*((volatile uint8 *)0x59))

#define		TIFR			(*((volatile uint8 *)0x58))
#define     SREG            (*((volatile uint8 *)0x5F))

/********** Pin Description **********/

#define     I               7
#define		CS00			0
#define		CS01			1
#define		CS02			2
#define		WGM01			3
#define		COM00			4
#define		COM01			5
#define		WGM00			6
#define		FOC0			7

#define		TOIE0			0
#define		OCIE0			1

#define		TOV0			0
#define		OCF0			1

#define		OC0				11



/*******************************************************************************
 *                      Configuration Enums                                    *
 *******************************************************************************/

/* Waveform Generation Mode */

typedef enum
{	TIMER0_Normal_Mode,
	TIMER0_PhaseCorrectPWM_Mode,
	TIMER0_CTC_Mode,
	TIMER0_FastPWM_Mode

}EnmTimer0_Mode_t;
/*******************************************************************************/
/*******************************************************************************/

/* Compare Output Mode, non-PWM Mode */

typedef enum
{
	TIMER0_CTC_Disconnected,
	TIMER0_CTC_Toggle,
	TIMER0_CTC_Clear,
	TIMER0_CTC_Set

}EnmTimer0_CTC_t;
/*******************************************************************************/
/*******************************************************************************/

/* Compare Output Mode, Fast PWM Mode */

typedef enum
{
	TIMER0_FastPWM_Disconnected,
	TIMER0_FastPWM_Clear=2,
	TIMER0_FastPWM_Set

}EnmTimer0_FastPWM_t;
/*******************************************************************************/
/*******************************************************************************/

/* Compare Output Mode, Phase Correct PWM Mode */

typedef enum
{
	TIMER0_PhaseCorrectPWM_Disconnected,
	TIMER0_PhaseCorrectPWM_Clear=2,
	TIMER0_PhaseCorrectPWM_Set

}EnmTimer0_PhasePWM_t;
/*******************************************************************************/
/*******************************************************************************/

/* Clock Select */

typedef enum
{
	TIMER0_NoClock,
	TIMER0_NoPrescaller,
	TIMER0_Prescaller_8,
	TIMER0_Prescaller_64,
	TIMER0_Prescaller_256,
	TIMER0_Prescaller_1024,

}EnmTimer0_Prescaller_t;
/*******************************************************************************/
/*******************************************************************************/

/* Interrupt Enable */

typedef enum
{
	TIMER0_INT_OFF,
	TIMER0_INT_OV,
	TIMER0_INT_OC

}EnmTimer0_INTenable_t;
/*******************************************************************************/
/*******************************************************************************/
/**************************************************************************************************************************************
 * Configuration Structure = {	
								Mode  ( Normal,PWM,CTC,PhaseCorrectPWM ) ,
 *								Prescaller( Noclock , NoPrescaller , Prescaller_8 , Prescaller_64 , Prescaller_256 , Prescaller_1024 ),
 *								Interrupt( Off, overflow , compare match ),
 *								CTC Modes( Disconnected , Toggle , Clear , Set ),
 *								FastPwm Modes( Disconnected , Clear , Set ),
 *								PhaseCorrect Modes( Disconnected , Clear , Set ),
 *								
 *								};							
 **************************************************************************************************************************************/

typedef struct
{
	EnmTimer0_Mode_t 	 		MbrTimer0Mode;
	EnmTimer0_Prescaller_t		MbrTimer0Prescaller;
	EnmTimer0_INTenable_t 		MbrTimer0Interrupt;
	EnmTimer0_CTC_t	 			MbrTimer0CTC;
	EnmTimer0_FastPWM_t 		MbrTimer0FastMode;
	EnmTimer0_PhasePWM_t		MbrTimer0PhaseCorrectPWM;


}StrTimer0_config_t;
extern StrTimer0_config_t Timer0Cfg;
/*******************************************************************************/
/*******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		TIMER0_init
 * Description: 		used to intialize TIMER0 module
 * parameters:
 *		Inputs:			object of structure to initialize TIMER0
 *		
		Outputs:		None
		
 * 		Return:			None
 *******************************************************************************/
void TIMER0_init (StrTimer0_config_t * Timer0cfg);
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/*******************************************************************************
 * Function Name:		TIMER0_ON
 * Description: 		used to start TIMER0 by selecting its clock
 * parameters:
 *		Inputs:			variable of EnmTimer0_Prescaller_t
 *		
		Outputs:		None
		
 * 		Return:			None
 *******************************************************************************/
void TIMER0_ON(StrTimer0_config_t *Timer0Pre);
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/*******************************************************************************
 * Function Name:		TIMER0_OFF
 * Description: 		used to stop TIMER0 
 * parameters:
 *		Inputs:			None
 *		
		Outputs:		None
		
 * 		Return:			None
 *******************************************************************************/
void TIMER0_OFF(void);
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/*******************************************************************************
 * Function Name:		TIMER0_SetCallBack
 * Description: 		used to link between global pointer and function you want 
						to call in ISR of TIMER0 OverFlow
 * parameters:
 *		Inputs:			pointer to function
 *		
		Outputs:		None
		
 * 		Return:			None
 *******************************************************************************/
void TIMER0_SetCallBack (void (*ptr_CallBack)(void));
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/
/*******************************************************************************
 * Function Name:		delay_m
 * Description: 		used to make delay in milli seconds
 * parameters:
 *		Inputs:			number of milli seconds
 *		
		Outputs:		None
		
 * 		Return:			None
 *******************************************************************************/
void delay_m (uint32 delay);
/********************************************************************************/
/********************************************************************************/
/********************************************************************************/

#endif /* TIMER0_H_ */
