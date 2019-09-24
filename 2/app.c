/*
 * app.c
 *
 *  Created on: Aug 27, 2019
 *      Author: abdul
 */
#include "LCD.h"
#include "keypad.h"
#include "util/delay.h"

int main ()
{
	LCD_Intialization();

	LCD_Write_ASCII('A');

	uint8 numberpressed=0;

	for(;;)
	{

		numberpressed = KeyPad_getPressedKey();
		LCD_Write_Integer_Number(numberpressed);

	}

}

