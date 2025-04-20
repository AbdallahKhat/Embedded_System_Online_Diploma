/*
 * Unit7_Section1.c
 *
 * Created: 3/1/2023 10:13:16 AM
 * Author : abdal
 */ 

#include "utils.h"
#include "MemMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	//Configure PORTD0 as input
	ClearBit(DDRD,0) ;
	SetBit(PORTD,0) ;
	
	//Configure PORTD4 as output
	SetBit(DDRD,4) ;
	
	while(1)
	{
		if(ReadBit(PIND,0) == 1) //Press
		{
			SetBit(PORTD,4) ;
			_delay_ms(1000) ;
			ClearBit(PORTD,4) ;
			while(ReadBit(PIND,0) == 1); //Single Press
		}
	}
	

}











/*
int main(void)
{
	//DDR
	//PORT
	//PIN READ CPU
	
	DDRA |= (0b111<<0) ;
	ClearBit(DDRC,0) ;
	SetBit(PORTC,0) ;
	
	while (1)
	{
		if(ReadBit(PINC,0) == 0)	//Press
		{
			ToggleBit(PORTA,0);
			while(ReadBit(PINC,0) == 0); //Single Press
		}
		
	}
}



















int main(void)
{
    DDRA |= (1<<0) ;
	DDRA |= (1<<1) ;
	DDRA |= (1<<2) ;  
	
    while (1) 
    {
		//Toggle Led
		ToggleBit(PORTA,0) ;
		ToggleBit(PORTA,1) ;
		ToggleBit(PORTA,2) ;
		_delay_ms(500); // delay 0.5s
		
    }
}
*/
