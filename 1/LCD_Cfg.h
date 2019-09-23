/*
 * LCD_Cfg.h
 *
 *  Created on: Sep 23, 2019
 *      Author: abdul
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define E_LCD	3
#define RW_LCD	2
#define RS_LCD	1


#define LCD_D4	4
#define LCD_D5	5
#define LCD_D6	6
#define LCD_D7	7

#define	PORT_LCD 	PORTA

// from data sheet

#define lcd_clear               			 0x01
#define lcd_home                			 0x02
#define lcd_increment_cursor    			 0x06  // entry mode (shift cursor to right)
#define lcd_displayoff          			 0x08
#define lcd_displayon_cursor_blink           0x0F  // F or E
#define lcd_displayon_cursor_off			 0x0C
#define lcd_2_lines_4_bits      			 0x28
#define lcd_2_lines_8_bits      			 0x38

#define lcd_4_bits_initialization_1			 0x32
#define lcd_4_bits_initialization_2			 0x33

// to send command to set position  (address - 1 )

// addresses of postions

#define lcd_line_1_address  127        // cursor position line 1 column 1 0x80 -> 128 in decimal
#define lcd_line_2_address  191        // cursor position line 2 column 1 0xC0 -> 192 in decimal

// for function GOTO

#define LINE_1      1
#define LINE_2      2

#define COLUMN_MIN   0
#define COLUMN_MAX   16

#endif /* LCD_CFG_H_ */
