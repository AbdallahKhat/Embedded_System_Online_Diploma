/*
 * SPI.c
 *
 * Created: 6/20/2023 1:06:08 PM
 *  Author: Abdallah Khater
 */ 



#include "SPI.h"


/*
 * ================================================================
 * 						API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn          -SPI_Init
 * @brief       -This is used to initialize SPI in Atmega32 
 * @retval      -none
 * Note         -supports for now: CLK Polarity idle (low) in case of Master, MSB of the data word is transmitted first,
 *              -leading clock edge sample, SCK Frequency (Fosc/4)
 */
void SPI_Init(void)
{
	#if (SPI_MODE == Master)
	
	SET_BIT(SPCR,MSTR) ;	//The SPI is configured as a Master
	CLR_BIT(SPCR,CPOL) ;	//Clock polarity idle (low)
	
	#elif (SPI_MODE == Slave)
	
	CLR_BIT(SPCR,MSTR) ;	//The SPI is configured as a Slave
	
	#endif
	
	SET_BIT(SPCR,SPE) ;		//Enable SPI Peripheral
	// Speed 2MHz freq ->> SPR1, SPR0 = 0 -> SPCR	(Fcpu / 4)
	
	
	
}


/**================================================================
 * @Fn          -SPI_SendReceive
 * @brief       -This is used to Transmit and receive data 
 * @param [in]  -data: data buffer to be transmitted and receive data
 * @retval      -received data
 * Note         -Supports full duplex communication 
 *              -Note 
 */
unsigned char SPI_SendReceive (unsigned char data)
{
	SPDR = data ;	//Assign data to SPI Data Register to be transmitted
	
	while(!(Read_BIT(SPSR,SPIF)));	//Busy waiting until serial transfer is complete
	
	return SPDR ;	//Return newly received buffer
	
}