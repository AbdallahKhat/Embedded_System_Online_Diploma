/*
 * I2C.h
 *
 * Created: 6/22/2023 2:24:59 PM
 *  Author: Abdallah Khater
 */ 


#ifndef I2C_H_
#define I2C_H_


//-----------------------------
//Includes
//-----------------------------

#include <avr/io.h>

//-----------------------------
//Macros
//-----------------------------

#define F_CPU 1000000UL

#define prescaler   1   //1, 4, 16, 64

/*
* ===============================================
* APIs Supported by "SPI DRIVER"
* ===============================================
*/

void I2C_Init(unsigned long SCL_Clock);
void I2C_Start(void);
void I2C_Write(unsigned char Data);
void I2C_Stop(void);
void I2C_Set_Address(unsigned char address);
unsigned char I2C_Read(unsigned char ack);




#endif /* I2C_H_ */