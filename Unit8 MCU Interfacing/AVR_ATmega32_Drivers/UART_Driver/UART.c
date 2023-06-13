/*
 * UART.c
 *
 * Created: 6/11/2023 1:38:17 PM
 *  Author: Abdallah Khater
 */ 

#include <avr/io.h>
#include "UART.h"

#define NULL 0

/**================================================================
 * @Fn			-UART_INIT
 * @brief 		-This is used to initialize USART in Atmega32 
 * @retval 		-none
 * Note			-Frame used has 1 start bit, 8-bit data, no parity, 1 stop bit, with Baud rate: 9600 bps				
 */
void UART_INIT(void)
{
	// Baudrate
	
	UBRRL = 51;
	
	// normal mode
	CLR_BIT(UCSRA,U2X);
	
	// frame
	// No parity
	// 8-bit data (initial value by default)
		
	// Enable
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}


/**================================================================
 * @Fn			-UART_Send
 * @brief 		-This is used to transmit data using UART Protocol
 * @param [in] 	-data: Effective data to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_Send(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while(!Read_BIT(UCSRA,UDRE));
	
	/* Put data into buffer, sends the data */
	UDR = data;
	
}


/**================================================================
 * @Fn			-UART_Receive
 * @brief 		-This is used to receive data transmitted using UART Protocol
 * @retval 		-received data
 * Note			-none
 */
unsigned char UART_Receive(void)
{
	/* Wait for data to be received */
	while(!Read_BIT(UCSRA,RXC));
	
	/* Get and return received data from buffer */
	return UDR;
}


/**================================================================
 * @Fn			-UART_SendNumberU32
 * @brief 		-This is used to transmit 32-bit data using UART Protocol
 * @param [in] 	-num: 32-bit number to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_SendNumberU32(unsigned int num)
{
	unsigned char* p = (unsigned char*)&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

/**================================================================
 * @Fn			-UART_ReceiveNumberU32
 * @brief 		-This is used to Receive 32-bit data using UART Protocol
 * @retval 		-32-bit received data
 * Note			-none
 */
unsigned int UART_ReceiveNumberU32(void)
{
	unsigned int num;
	unsigned char* p = (unsigned char*)&num;
	
	p[0] = UART_Receive();
	p[1] = UART_Receive();
	p[2] = UART_Receive();
	p[3] = UART_Receive();
	
	return num;
}


/**================================================================
 * @Fn			-UART_SendString
 * @brief 		-This is used to Send a string using UART Protocol
 * @param [in] 	-pstr: pointer to string to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_SendString(char* pstr)
{
	int count;
	
	//for loop to send string char by char until NULL
	for(count=0; pstr[count] != NULL ; count++)
	{
		UART_Send(pstr[count]);
	}
}

/**================================================================
 * @Fn			-UART_ReceiveString
 * @brief 		-This is used to receive string using UART Protocol
 * @param [in] 	-String: The string variable to receive the string transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_ReceiveString(char* String)
{
	int count = 0;
	
	//assigning elements of transmitted string to string variable until '#' 
	while(1)
	{
		String[count] = UART_Receive();
		count++;
		
		if(String[count-1] == '#')
		{
			String[count-1] = NULL;
			break;
		}
	}
}