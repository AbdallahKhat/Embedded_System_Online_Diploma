/*
 * SPI.h
 *
 * Created: 6/20/2023 1:06:19 PM
 *  Author: Abdallah Khater
 */ 


#ifndef SPI_H_
#define SPI_H_

//-----------------------------
//Includes
//-----------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//-----------------------------
//Generic Macros
//-----------------------------

//Macros to set/reset/read bit in a register
#define SET_BIT(reg, shift)				reg |= (1 << shift)
#define CLR_BIT(reg, shift)				reg &= ~(1 << shift)
#define Read_BIT(reg, shift)			((reg & (1 << shift)) >> shift)



#define Master 1
#define Slave 0
#define SPI_MODE SLAVE				//Select SPI Mode (Master / Slave)


/*
* ===============================================
* APIs Supported by "SPI DRIVER"
* ===============================================
*/

void SPI_Init(void) ;
unsigned char SPI_SendReceive (unsigned char data) ;




#endif /* SPI_H_ */