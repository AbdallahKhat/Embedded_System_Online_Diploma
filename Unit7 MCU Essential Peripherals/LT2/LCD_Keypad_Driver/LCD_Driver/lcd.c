/*
 * lcd.c
 *
 * Created: 3/7/2023 9:43:53 AM
 *  Author: Abdal
 */ 

#include "lcd.h"

void LCD_kick(void)
{
	LCD_CTRL |= (1 << ENABLE_SWITCH);
	_delay_ms(50);
	LCD_CTRL &= ~(1 << ENABLE_SWITCH);
}

void LCD_GOTO_XY(int line,int position)
{
	if(line == 1)
	{
		if(position < 16 && position >= 0)
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
	}
	else if(line == 2)
	{
		if(position < 32 && position >= 0)
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
	}
}	

void LCD_isbusy(void)
{
	DataDir_LCD_PORT &= ~(0xFF << DATA_shift);
	LCD_CTRL |= (1<<RW_SWITCH);	
	LCD_CTRL &= ~(1<<RS_SWITCH);
	LCD_kick();
	DataDir_LCD_PORT |= (0xFF << DATA_shift);
	LCD_CTRL &= ~(1<<RW_SWITCH);
}

void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_INIT(void)
{
	_delay_ms(20);
	DataDir_LCD_CTRL |= (1<<ENABLE_SWITCH | 1<<RW_SWITCH | 1<<RS_SWITCH);
	LCD_CTRL &= ~((1<<ENABLE_SWITCH) | (1<<RW_SWITCH) | (1<<RS_SWITCH));
	DataDir_LCD_PORT = 0xFF;
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif	
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_isbusy();
	
	#ifdef EIGHT_BIT_MODE
	LCD_PORT = command;
	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	LCD_kick(); 
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	LCD_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	LCD_kick();
	#endif
}
void LCD_WRITE_CHAR(unsigned char data)
{

	#ifdef EIGHT_BIT_MODE
	LCD_isbusy();
	LCD_PORT = data;
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
	//LCD_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &= ~(1<<RW_SWITCH);
	LCD_kick();
	#endif
}
void LCD_WRITE_STRING(char* data)
{
	int count = 0;
	
	while(*data > 0)
	{
		LCD_WRITE_CHAR(*data++);
		count++;
		if(count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if(count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}


void LCD_CUSTOM_CHARACTERS()
{
	LCD_WRITE_COMMAND(64);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(14);
	LCD_WRITE_CHAR(17);
	LCD_WRITE_CHAR(2);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_CHAR(0);
	_delay_ms(10);
	
	LCD_WRITE_COMMAND(72);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(10);
	LCD_WRITE_CHAR(21);
	LCD_WRITE_CHAR(17);
	LCD_WRITE_CHAR(18);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(0);
	LCD_GOTO_XY(1, 1);
	LCD_WRITE_CHAR(1);
	_delay_ms(10);

}