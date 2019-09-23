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
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);



#endif /* KEYPAD_H_ */
