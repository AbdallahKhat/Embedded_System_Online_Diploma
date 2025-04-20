/*
 * lcd_driver.c
 *
 * Created: 3/7/2023 9:43:53 AM
 *  Author: Abdal
 */

#include "lcd_driver.h"

static GPIO_PinConfig_t PinCfg ;

void my_wait(int x);


void LCD_kick(void)
{
	my_wait(20);
	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_SET);
	//	LCD_CTRL |= (1 << ENABLE_SWITCH);
	my_wait(50);
	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_RESET);
	//	LCD_CTRL &= ~(1 << ENABLE_SWITCH);
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
	//DataDir_LCD_PORT &= ~(0xFF << DATA_shift);

	//DATA PINS input
	PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH ,GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH ,GPIO_PIN_RESET);

	//LCD_CTRL |= (1<<RW_SWITCH);
	//LCD_CTRL &= ~(1<<RS_SWITCH);
	LCD_kick();

	PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	//DataDir_LCD_PORT |= (0xFF << DATA_shift);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH ,GPIO_PIN_RESET);
	//LCD_CTRL &= ~(1<<RW_SWITCH);
}

void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_INIT(void)
{
	my_wait(20);

	//ENABLE_SWITCH,RS_SWITCH,RW_SWITCH input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = ENABLE_SWITCH ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = RS_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = RW_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	my_wait(15);

	//DATA PINS output pp with speed 10MHZ
	PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(LCD_PORT,&PinCfg);

	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);


	LCD_clear_screen();

	//#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	LCD_WRITE_COMMAND(0x02);
	//	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	//#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_isbusy();

	//#ifdef EIGHT_BIT_MODE
	//	LCD_PORT = command;

	MCAL_GPIO_WritePort(LCD_PORT, command);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	//	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	my_wait(1);

	LCD_kick();
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	//	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	//	LCD_kick();
	//	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	//	LCD_CTRL &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
	//	LCD_kick();
	//#endif
}
void LCD_WRITE_CHAR(unsigned char data)
{

	//#ifdef EIGHT_BIT_MODE
	LCD_isbusy();
	//	LCD_PORT = data;
	MCAL_GPIO_WritePort(LCD_PORT, data);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	//	LCD_CTRL &= ~(1<<RW_SWITCH);
	//	LCD_CTRL |= (1<<RS_SWITCH);
	my_wait(1);
	LCD_kick();
	//#endif

	//#ifdef FOUR_BIT_MODE
	//	//LCD_isbusy();
	//	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	//	LCD_CTRL |= (1<<RS_SWITCH);
	//	LCD_CTRL &= ~(1<<RW_SWITCH);
	//	LCD_kick();
	//	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	//	LCD_CTRL |= (1<<RS_SWITCH);
	//	LCD_CTRL &= ~(1<<RW_SWITCH);
	//	LCD_kick();
	//#endif
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
	my_wait(10);

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
	my_wait(10);

}
