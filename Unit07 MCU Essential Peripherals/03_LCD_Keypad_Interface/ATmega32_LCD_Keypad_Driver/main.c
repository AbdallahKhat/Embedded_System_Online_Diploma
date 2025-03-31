/*
 * LCD_Keypad_Driver.c
 *
 * Created: 3/7/2023 9:41:57 AM
 * Author : Abdal
 */ 

#include <avr/io.h>
#include "LCD_Driver/lcd.h"
#include "Keypad_Driver/Keypad.h"

int main(void)
{
    /* Replace with your application code */
	LCD_INIT();
	KEYPAD_INIT();
	LCD_CUSTOM_CHARACTERS();
	_delay_ms(50);
	unsigned char pressed_key;
    while (1) 
    {
		pressed_key = KEYPAD_GETCHAR();
		switch(pressed_key)
		{
			case ('!'):
				LCD_clear_screen();
				break;
			case ('N'):
				break;
			default:
				LCD_WRITE_CHAR(pressed_key);
				break;
		}
    }
}

