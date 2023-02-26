/*
 * Atmega32A_Lab.c
 *
 * Created: 2/26/2023 3:37:27 PM
 * Author : abdal
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

ISR(INT0_vect)
{
	PORTD |= (1<<5);
	_delay_ms(1000);
	PORTD &= ~(1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	PORTD |= (1<<6);
	_delay_ms(1000);
	PORTD &= ~(1<<6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	PORTD |= (1<<7);
	_delay_ms(1000);
	PORTD &= ~(1<<7);
	_delay_ms(1000);
}

int main(void)
{
	//allow pins (5,6,7) as outputs in portD
	DDRD |= (1<<5);
	DDRD |= (1<<6);
	DDRD |= (1<<7);
	
	//Global Interrupt Enable
	sei();
	
    //Any logical change on INT0 generates an interrupt request.
	MCUCR |= (0b01 << 0);
	//The rising edge of INT1 generates an interrupt request.
	MCUCR |= (0b11 << 2);
	//a falling edge on INT2 activates the interrupt.
	MCUCSR &= ~(1 << 6);
	//Enable INT0,INT1,INT2
	GICR |= (0b111 << 5);
    while (1)		
    {
    }
}

