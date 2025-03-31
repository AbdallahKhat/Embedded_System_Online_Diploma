/*
 * I2C.c
 *
 * Created: 6/22/2023 2:24:38 PM
 *  Author: Abdallah Khater
 */ 


#include "I2C.h"


/*
 * ================================================================
 *                      API Function Definitions
 * ================================================================
 */


/**================================================================
 * @Fn          -I2C_Init
 * @brief       -This is used to initialize TWI in Atmega32 
 * @param [in]  -SCL_Clock: Freq of SCL
 * @retval      -none
 * Note         -none
 */
void I2C_Init(unsigned long SCL_Clock)
{
	// SCL frequency = CPU Clock frequency/16 + 2(TWBR) * 4^TWPS
	// TWBR = Value of the TWI Bit Rate Register
	// TWPS = Value of the prescaler bits in the TWI Status Register

	
	//Settings SCL frequency
	TWBR = (unsigned char)(((F_CPU/SCL_Clock)-16)/(2*prescaler));
	
	switch(prescaler)
	{
		case 1:
		TWSR = 0;
		break;
		case 4:
		TWSR = 1;
		break;
		case 16:
		TWSR = 2;
		break;
		case 64:
		TWSR = 3;
		break;
	}
}


/**================================================================
 * @Fn          -I2C_Start
 * @brief       -This is used to generate Start Condition
 * @retval      -none
 * Note         -none
 */
void I2C_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);       //Send START condition 
	
	while(!(TWCR&(1<<TWINT)));                        //Wait for TWINT Flag set.
												      //This indicates that the START condition has been transmitted
	
	while((TWSR) != 0x08) ;                           //Status code is set after Start condition has been transmitted
	
}


/**================================================================
 * @Fn          -I2C_Write
 * @brief       -This is used to transmit data
 * @retval      -none
 * Note         -none
 */
void I2C_Write(unsigned char Data)
{
	TWDR = Data ;                                    //Load DATA into TWDR Register
	
	TWCR = (1<<TWINT) | (1<<TWEN) ;                  //Clear TWINT bit in TWCR to start transmission of data
	
	while(!(TWCR & (1<<TWINT)));                     //Wait for TWINT Flag set
	                                                 //This indicates that the DATA has been transmitted, and ACK/NACK has been received
}


/**================================================================
 * @Fn          -I2C_Stop
 * @brief       -This is used to generate Stop Condition
 * @retval      -none
 * Note         -none
 */
void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) ;
}


/**================================================================
 * @Fn          -I2C_Set_Address
 * @brief       -This is set address of slave
 * @param [in]  -address: address of slave
 * @retval      -none
 * Note         -none
 */
void I2C_Set_Address(unsigned char address)
{
	TWAR = address ;
}


/**================================================================
 * @Fn          -I2C_Read
 * @brief       -This is used to read data
 * @retval      -received data
 * Note         -none
 */
unsigned char I2C_Read(unsigned char ack)
{
	if(ack == 1)
	{
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
		
		// If the TWEA bit is written to one, the ACK pulse is generated on the TWI bus if the following conditions are met:
		 
		//1. The device’s own slave address has been received.
		//2. A general call has been received, while the TWGCE bit in the TWAR is set.
		//3. A data byte has been received in Master Receiver or Slave Receiver mode.
	}
	
	while(!(TWCR & (1<<TWINT))) ;		         //This indicates that the SLA+W has been transmitted, and ACK/NACK has been received
	
	while(TWSR != 0x60) ;                        // Own SLA+W has been received; ACK has been returned
	
	if (ack == 1)
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
	
	while(!(TWCR & (1<<TWINT))) ;		         //This indicates that the DATA has been transmitted, and ACK/NACK has been received
	
	while(TWSR != 0x80) ;                        //data has been received; ACK has been returned
	
	return TWDR ;

}