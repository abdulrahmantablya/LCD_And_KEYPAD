/****************************************
 *
 *  File Name: keypad.c        
 *                       
 *  Created on: Sep 23, 2019   
 * 
 *  Author: Stawro Walaa   
 *
 ****************************************/


#include "keypad.h"


static uint8 KeyPad_3x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
	case 1: return 1;
	break;
	case 2: return 2;
	break;
	case 3: return 3;
	break;
	case 4: return 4; // ASCII Code of %
	break;
	case 5: return 5;
	break;
	case 6: return 6;
	break;
	case 7: return 7;
	break;
	case 8: return 8; /* ASCII Code of '*' */
	break;
	case 9: return 9;
	break;
	default: return button_number;
	}
}

uint8 KeyPad_getPressedKey(void)
{
	uint8 col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			KEYPAD_PORT_DIR = (0b00100000<<col);

			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the rows pins
			 */
			KEYPAD_PORT_OUT = (~(0b00100000<<col));

			for(row=2;row<5;row++) /* loop for rows */
			{
				if(GetBit(KEYPAD_PORT_IN,row)==0) /* if the switch is press in this row */
				{
					while( GetBit(KEYPAD_PORT_IN,row)==0 );

					return KeyPad_3x3_adjustKeyNumber(3*(row-2)+col+1);

				}
			}
		}
	}
}
