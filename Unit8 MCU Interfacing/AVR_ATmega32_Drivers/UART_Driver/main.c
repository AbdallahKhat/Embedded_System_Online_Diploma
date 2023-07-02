/*
 * UART_Driver.c
 *
 * Created: 6/11/2023 1:24:53 PM
 * Author : Abdallah Khater
 */ 

#include <avr/io.h>
#include "MCAL/UART.h"
#include "HAL/lcd.h"

int main(void)
{
	char Str1[] = "Transmitted!";
	char Str2[20];
	
	LCD_INIT();
	
	UART_INIT();
	
	UART_SendString(Str1);
	
	UART_ReceiveString(Str2);
	
	LCD_WRITE_STRING(Str2);
	
    while (1) 
    {
    }
}

