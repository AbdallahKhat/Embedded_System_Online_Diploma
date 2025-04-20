/*
 * Section_Task2.c
 *
 * Created: 3/1/2023 4:15:53 PM
 * Author : abdal
 */ 

#include "utils.h"
#include "MemMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>



int main(void)
{
	//Config all PortA Pins as outputs
	DDRA = 0xFF ;
	
	//Config PortC0 as input PUR
	ClearBit(DDRC,0) ;
	SetBit(PORTC,0) ;
	
	int n = 0;
	
    while (1) 
    {
		if(ReadBit(PINC,0) == 0 && n < 8)	//Press
		{
			SetBit(PORTA,n);
			n++;
			_delay_ms(250);
		}
    }
}
