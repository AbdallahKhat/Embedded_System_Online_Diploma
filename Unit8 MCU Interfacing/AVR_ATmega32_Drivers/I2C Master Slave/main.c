/*
 * SPI_Driver.c
 *
 * Created: 6/20/2023
 * Author : Abdallah Khater
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "I2C.h"

//#define MCU_AS_MASTER
#define MCU_AS_SLAVE

int main(void)
{
	#ifdef MCU_AS_MASTER
	unsigned char ch = 0 ;
	I2C_Init(0x48) ;
	#endif
	
	#ifdef MCU_AS_SLAVE
	DDRA = 0xFF;	                       //make PORTA as output
	I2C_Set_Address(0b11010000);
	#endif
		
    while (1) 
    {
		#ifdef MCU_AS_MASTER
		_delay_ms(2000) ;
		I2C_Start() ;                     //Transmit start condition
		I2C_Write(0b11010000 + 0) ;       //Transmit SLA + W(0) (Slave address + write command
		while((TWSR) != 0x18) ;           //SLA + W(0) has been transmitted and ACK has been received 
		I2C_Write(ch++) ;                 //Transmit data
		I2C_Stop() ;                      //Transmit stop condition
		#endif
		
		#ifdef MCU_AS_SLAVE
		PORTA = I2C_Read(1);
		#endif
    }
	
	return 0;
}

