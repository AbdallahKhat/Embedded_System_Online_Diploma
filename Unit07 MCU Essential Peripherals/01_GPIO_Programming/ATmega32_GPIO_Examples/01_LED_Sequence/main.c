/*
 * Section_Task1.c
 *
 * Created: 3/1/2023 4:15:53 PM
 * Author : abdal
 */ 

#include "utils.h"
#include "MemMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void Led_Toggle(int n)	//LED increment Turn on PortA0 -> 7 , Turn off 7 -> 0 (By Recursion)
{
	if(n<8)
	{
		
	SetBit(PORTA,n);		//Turn on LED
	_delay_ms(250);
	
	Led_Toggle(n + 1);
	
	ClearBit(PORTA,n);		//Turn off LED
	_delay_ms(250);
	}
}

int main(void)
{
	//Config all PortA Pins as outputs
	DDRA = 0xFF ;
	
    while (1) 
    {
		Led_Toggle(0);
    }
}
