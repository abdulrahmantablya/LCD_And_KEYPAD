/*
 * LCD.c
 *
 *  Created on: Aug 27, 2019
 *      Author: abdul
 */
#include "LCD_Cfg.h"
#include "LCD.h"

#include "util/delay.h"

void LCD_Intialization (void)
{
	DIO_SetPinDirection(E_LCD,OUTPUT);
	DIO_SetPinDirection(RS_LCD,OUTPUT);
	DIO_SetPinDirection(RW_LCD,OUTPUT);

	DIO_SetPinDirection(LCD_D4,OUTPUT);
	DIO_SetPinDirection(LCD_D5,OUTPUT);
	DIO_SetPinDirection(LCD_D6,OUTPUT);
	DIO_SetPinDirection(LCD_D7,OUTPUT);

	_delay_ms(35);

	LCD_Command(lcd_4_bits_initialization_2);
	_delay_ms(2);
	LCD_Command(lcd_4_bits_initialization_1);
	_delay_ms(2);
	LCD_Command(lcd_2_lines_4_bits);
	_delay_ms(2);
	LCD_Command(lcd_displayon_cursor_off);
	_delay_ms(2);
	LCD_Command(lcd_increment_cursor);
	_delay_ms(2);
	LCD_Command(lcd_clear);
	_delay_ms(15);

}


void LCD_Command (uint8 u8Commandcopy)
{
	DIO_WritePin(RS_LCD,LOW);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(1);

	PORT_LCD=(PORT_LCD & 0x0f)|(u8Commandcopy & 0xf0);
	_delay_ms(1);
	DIO_WritePin(E_LCD,LOW);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(1);


	PORT_LCD=(PORT_LCD & 0x0f)|((u8Commandcopy & 0x0f) <<4 );
	_delay_ms(1);
	DIO_WritePin(E_LCD,LOW);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(15);
}


void LCD_Write_ASCII (uint8 u8Datacopy)
{
	DIO_WritePin(RS_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(1);

	PORT_LCD=(PORT_LCD & 0x0f)|(u8Datacopy & 0xf0);
	_delay_ms(1);
	DIO_WritePin(E_LCD,LOW);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(1);


	PORT_LCD=(PORT_LCD & 0x0f)|((u8Datacopy & 0x0f) <<4 );
	_delay_ms(1);
	DIO_WritePin(E_LCD,LOW);
	_delay_ms(1);
	DIO_WritePin(E_LCD,HIGH);
	_delay_ms(15);

}


void LCD_GOTO (uint8 LINE,uint8 COLUMN)
{
	if ( ( COLUMN > COLUMN_MIN ) && ( COLUMN <= COLUMN_MAX ) )
	{
		switch (LINE)
		{
			case LINE_1 :
							LCD_Command( ( lcd_line_1_address ) + ( COLUMN ) );
							break;

			case LINE_2 :
							LCD_Command( ( lcd_line_2_address ) + ( COLUMN ) );
							break;

			default :
							break;
		}
	}
	else
	{

	}

}


void LCD_Write_Word(uint8* word)
{
	uint8 iterator;
	for( iterator=0;word[iterator]!=0;iterator++ )
	{
		LCD_Write_ASCII( word[iterator] );
	}

}


// a function to reverse a string
void reverse (uint8 *str, uint8 length)
{
	uint8 start = 0;
	uint8 end = length-1;
	while( start < end )
	{
		uint8 temp = str[start] ;

		str[start] = str[end];

		str[end] = temp;

		start++;
		end--;
	}

}


uint8* integer_to_string (sint32 number,uint8* str,uint8 base)

{
	// index for length

	uint8 i = 0;
	uint8 isNegative = 0;

	// Handle 0 explicitely

	if (number == 0)
	{
		str[i++] = '0';
		str[i] = '\0';  // the end of the string
		return str;
	}

	// negative numbers are handled only with
	// base 10. Otherwise numbers are considered unsigned

	if (number <0 && base ==10)
	{
		isNegative = 1;
		number = -number; // to get the absolute value of the number
	}

	while (number != 0)
	{

		uint8 remainder = number % base ;
		if (remainder > 9)
		{
			str[i++] = (remainder-10) + 'A';  // for hexa-decimal only

		}
		else
		{
			str[i++] = remainder + '0';
		}
		number=number/base;
	}

	if (isNegative)
	{
		str[i++] = '-';
	}

	str[i] = '\0';  // the end of the string

	reverse(str,i); // where i  index for the length of the string

	return str;
}


void LCD_Write_Integer_Number (sint32 number )
{
	uint8 str[16];
	integer_to_string(number,str,10) ;

	LCD_Write_Word((uint8*)str);

}
