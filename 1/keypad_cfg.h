/****************************************
 *
 *  File Name: keypad_cfg.h        
 *                       
 *  Created on: Sep 23, 2019   
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC


#endif /* KEYPAD_CFG_H_ */
