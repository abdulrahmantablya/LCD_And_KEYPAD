/****************************************
 *
 *  File Name: timer0.c
 *
 *  Created on: Sep 16, 2019
 *
 *  Author: Stawro Walaa
 *
 ****************************************/
#include "timer0.h"

/*******************************************************************************
 *                       	Attribute                                 			*
 *******************************************************************************/

#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#define __INTR_ATTRS used, externally_visible
#endif

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#define TIMER0_COMP_vect		_VECTOR(10)
#define TIMER0_OVF_vect			_VECTOR(11)

#ifndef _VECTOR
#define _VECTOR(N) __vector_ ## N
#endif
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************
 *                       	Global pointer to function                          	  *
 *************************************************************************************/

 void (*CallBack_ptrTimer0)(void)=NULL;
 
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/


/**************************************************************************************
 *                    Interrupt Service Routin of Overflow of Timer0	              *
 *************************************************************************************/
ISR(TIMER0_OVF_vect)
{
	static uint8 ovf_flag = 0;
	if(ovf_flag>=8){
		if(CallBack_ptrTimer0 != NULL)
		{
			CallBack_ptrTimer0();

		}
		TCNT0=6;
		ovf_flag=0;

	}
	else{
		ovf_flag++;
	}

}
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

void TIMER0_init (StrTimer0_config_t * config)
{

	switch (config->MbrTimer0Mode)
	{
		/* TIMER0_Normal_Mode */

		case TIMER0_Normal_Mode :
			ClrBit(TCCR0,WGM00);
			ClrBit(TCCR0,WGM01);
			break;
		/**************************************************/
			/* TIMER0_PhaseCorrectPWM_Mode */
		case TIMER0_PhaseCorrectPWM_Mode :
			SetBit(TCCR0,WGM00);
			ClrBit(TCCR0,WGM01);

				switch (config->MbrTimer0PhaseCorrectPWM)
				{
					case TIMER0_PhaseCorrectPWM_Disconnected :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;

					case TIMER0_PhaseCorrectPWM_Clear :
						ClrBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					case TIMER0_PhaseCorrectPWM_Set :
						SetBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					default :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;
				}

				/* configure pin of OC0 as output and initialize it with LOW Voltage */
				DIO_SetPinDirection(OC0,OUTPUT);
				DIO_WritePin(OC0,LOW);

				break;
				/**************************************************/
				/* TIMER0_CTC_Mode */
		case TIMER0_CTC_Mode :

			ClrBit(TCCR0,WGM00);
			SetBit(TCCR0,WGM01);

				switch(config->MbrTimer0CTC )
				{
					case TIMER0_CTC_Disconnected :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;

					case TIMER0_CTC_Toggle :
						SetBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;

					case TIMER0_CTC_Clear:
						ClrBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					case TIMER0_CTC_Set :
						SetBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					default :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;
				}
				/* configure pin of OC0 as output and initialize it with LOW Voltage */
				DIO_SetPinDirection(OC0,OUTPUT);
				DIO_WritePin(OC0,LOW);

				break;
				/**************************************************/
				/* TIMER0_CTC_Mode */
		case TIMER0_FastPWM_Mode :
			SetBit(TCCR0,WGM00);
			SetBit(TCCR0,WGM01);

				switch (config->MbrTimer0FastMode)
				{
					case TIMER0_FastPWM_Disconnected :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;


					case TIMER0_FastPWM_Clear :
						ClrBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					case TIMER0_FastPWM_Set :
						SetBit(TCCR0,COM00);
						SetBit(TCCR0,COM01);
						break;

					default :
						ClrBit(TCCR0,COM00);
						ClrBit(TCCR0,COM01);
						break;
				}
				/* configure pin of OC0 as output and initialize it with LOW Voltage */
				DIO_SetPinDirection(OC0,OUTPUT);
				DIO_WritePin(OC0,LOW);

				break;
				/**************************************************/

		default :
			ClrBit(TCCR0,WGM00);
			ClrBit(TCCR0,WGM01);
			break;

	}


	switch(config->MbrTimer0Interrupt)
	{
		case TIMER0_INT_OFF :
			ClrBit(TIMSK,TOIE0);
			ClrBit(TIMSK,OCIE0);
			break;

		case TIMER0_INT_OV :
			SetBit(TIMSK,TOIE0);
			ClrBit(TIMSK,OCIE0);
			SetBit(SREG,I);
			break;

		case TIMER0_INT_OC :
			ClrBit(TIMSK,TOIE0);
			SetBit(TIMSK,OCIE0);
			SetBit(SREG,I);
			break;

		default:
			ClrBit(TIMSK,TOIE0);
			ClrBit(TIMSK,OCIE0);
			break;

	}


}

void TIMER0_ON(StrTimer0_config_t *Timer0Pre)
{
	switch (Timer0Pre->MbrTimer0Prescaller)
	{

		case TIMER0_NoClock :

			ClrBit(TCCR0,CS00);
			ClrBit(TCCR0,CS01);
			ClrBit(TCCR0,CS02);
			break;

		case TIMER0_NoPrescaller :

			SetBit(TCCR0,CS00);
			ClrBit(TCCR0,CS01);
			ClrBit(TCCR0,CS02);
			break;

		case TIMER0_Prescaller_8 :

			ClrBit(TCCR0,CS00);
			SetBit(TCCR0,CS01);
			ClrBit(TCCR0,CS02);
			break;

		case TIMER0_Prescaller_64 :

			SetBit(TCCR0,CS00);
			SetBit(TCCR0,CS01);
			ClrBit(TCCR0,CS02);
			break;

		case TIMER0_Prescaller_256 :

			ClrBit(TCCR0,CS00);
			ClrBit(TCCR0,CS01);
			SetBit(TCCR0,CS02);
			break;

		case TIMER0_Prescaller_1024 :

			SetBit(TCCR0,CS00);
			ClrBit(TCCR0,CS01);
			SetBit(TCCR0,CS02);
			break;

		default :
			ClrBit(TCCR0,CS00);
			ClrBit(TCCR0,CS01);
			ClrBit(TCCR0,CS02);
			break;
	}

}

void TIMER0_OFF(void)
{
	ClrBit(TCCR0,CS00);
	ClrBit(TCCR0,CS01);
	ClrBit(TCCR0,CS02);
}

void delay_m (uint32 delay)
{
	uint32 i;
	TCNT0=0;
	OCR0=SetCounts(TIME,F_CPU,PRE);

	for (i=0;i<delay;i++)
	{
		/* poll on OCR0 bit in TIFR*/
		while((GetBit(TIFR,OCF0) == LOW)); 
		/* clear OCR0 bit */
		SetBit(TIFR,OCF0);				   

	}

}

void TIMER0_SetCallBack (void (*ptr_CallBack)(void))
{
	CallBack_ptrTimer0=ptr_CallBack;
}
