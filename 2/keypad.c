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
#include "os.h"
#include "LCD.h"
uint8 keyValue;

uint8 KeyPad_getPressedKey(uint8* value, uint8 *btnStatus) {
	uint8 col, row, pressFlag = NOT_PRESSED;

	for (col = 0; col < N_col; col++) /* loop for columns */
	{
		/*
		 * each time only one of the column pins will be output and
		 * the rest will be input pins include the row pins
		 */
		KEYPAD_PORT_DIR = (0b00100000 << col);

		/*
		 * clear the output pin column in this trace and enable the internal
		 * pull up resistors for the rows pins
		 */
		KEYPAD_PORT_OUT = (~(0b00100000 << col));

		for (row = 2; row < 5; row++) /* loop for rows */
		{
			if (GetBit(KEYPAD_PORT_IN,row) == 0) /* if the switch is press in this row */
			{

				pressFlag = PRESSED;
				if (*btnStatus == NOT_OK) {

					*btnStatus = PRE_PENDING;
					break;
				}
				if (*btnStatus == PRE_PENDING) {
					*value = (3 * (row - 2) + col + 1);
					*btnStatus = OK;
					break;
				}

			}
		}
		if(*btnStatus == PRE_PENDING && pressFlag==NOT_PRESSED){
			btnStatus = NOT_OK;
		}

	}
	return pressFlag;

}
void KeyPAD_DebouncingHandler(void) {
	static uint8 btnStatus = NOT_OK;
	uint8 value,pressStatus;
	pressStatus = KeyPad_getPressedKey(&value, &btnStatus);
	switch (btnStatus) {
	case OK:
		if(pressStatus==PRESSED){
			if (value == 1) {
				keyValue = YES;
			} else if (value == 7) {
				keyValue = NO;
			}
		}
		else {
			btnStatus = POST_PENDING;
			keyValue = NO_RESULT;
		}

		break;

	case PRE_PENDING:
		keyValue = NO_RESULT;
		break;

	case NOT_OK:
		keyValue = NO_RESULT;
		break;
	case POST_PENDING:
		if(btnStatus==PRESSED){
			btnStatus=OK;
		}
		else{
			btnStatus=NOT_OK;
		}
		keyValue = NO_RESULT;
	}

}
