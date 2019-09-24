/****************************************
 *
 *  File Name: timer0_cfg.h
 *
 *  Created on: Sep 16, 2019
 *
 *  Author: Stawro Walaa
 *
 ****************************************/

#ifndef TIMER0_Cfg_H_
#define TIMER0_Cfg_H_

#include "timer0.h"

/**************************************************************************************
 *                    configuration of delay function 	            				  *
 *************************************************************************************/

#define		SetCounts(TIME,FCPU,PRE)	((TIME*F_CPU)/PRE)   /* equation to calculate the value in OCR0 */

#ifndef F_CPU
#define 	F_CPU			8000000UL  					/* clock */
#endif
	
#define		PRE				64							/* prescaller of timer0 */

	
#define		TIME			0.001					/* for milli seconds -> 0.001 */


/*******************************************************************************/
/*******************************************************************************/
#endif
