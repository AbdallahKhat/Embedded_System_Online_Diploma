/*
 * lcd.h
 *
 * Created: 3/7/2023 9:43:39 AM
 *  Author: Abdal
 */ 


#ifndef LCD_H_
#define LCD_H_

 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT PORTA
#define DataDir_LCD_PORT DDRA
#define LCD_CTRL PORTB
#define DataDir_LCD_CTRL DDRB
#define RS_SWITCH 1
#define RW_SWITCH 2
#define ENABLE_SWITCH 3
#define DATA_shift 4 // in 8 bit mode 0 and in 4 bit mode 4

//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF								(0x08)
#define LCD_DISP_ON_CURSOR							(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON									(0x0C)
#define LCD_ENTRY_DEC								(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_								(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char data);
void LCD_WRITE_STRING(char* data);
void LCD_isbusy(void);
void LCD_clear_screen(void);
void LCD_CUSTOM_CHARACTERS(void);
void LCD_GOTO_XY(int line,int position);
void LCD_WRITE_NUMBER(unsigned char Num);

#endif /* LCD_H_ */