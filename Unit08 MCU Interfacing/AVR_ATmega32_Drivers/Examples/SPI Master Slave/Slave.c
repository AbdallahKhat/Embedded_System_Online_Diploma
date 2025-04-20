/*
 * SPI Slave.c
 *
 * Created: 6/17/2023 7:06:44 PM
 * Author : Abdallah Khater
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

#define SS			4
#define MOSI		5
#define MISO		6
#define SCK			7

void SPI_SlaveInit()
{
	DDRB = (1<<MISO);
	
	SPCR = (1<<SPE);
}
 
unsigned char SPI_SlaveReceive(unsigned char cdata)
{
	SPDR = cdata;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}


int main(void)
{
	SPI_SlaveInit();
	DDRA = 0xFF;
	
	unsigned char data = 0;
	
	for(data = 0; data <= 255 ; data++)
	{
		_delay_ms(1000);
		PORTA = SPI_SlaveReceive(data);
	}
}

