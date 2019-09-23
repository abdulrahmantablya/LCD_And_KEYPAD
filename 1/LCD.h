/*
 * LCD.h
 *
 *  Created on: Aug 27, 2019
 *      Author: abdul
 */

#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"



void LCD_Intialization (void);

void LCD_Command (uint8 u8Commandcopy);

void LCD_Write_ASCII (uint8 u8Datacopy);

void LCD_GOTO (uint8 LINE,uint8 COLUMN);

void LCD_Write_Word(uint8* word);

void LCD_Write_Integer_Number (sint32 number );


#endif /* LCD_H_ */
