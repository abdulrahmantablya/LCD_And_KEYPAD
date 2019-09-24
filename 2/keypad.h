/****************************************
 *
 *  File Name: keypad.h        
 *                       
 *  Created on: Sep 23, 2019   
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "DIO.h"
#include "keypad_cfg.h"

/*******************************************************************************
 *                   			   Defines                                     *
 *******************************************************************************/
enum{
	NOT_OK,
	PRE_PENDING,
	OK,
	POST_PENDING
};
enum{
	NO_RESULT,
	NO,
	YES
};
enum{
	PRESSED,
	NOT_PRESSED
};

extern uint8 keyValue;
/*******************************************************************************
 *                          Functions Prototypes                               *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(uint8* value,uint8 *btnStatus);

extern void KeyPAD_DebouncingHandler(void);

#endif /* KEYPAD_H_ */
