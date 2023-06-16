/*
 * UART.h
 *
 * Created: 6/11/2023 1:37:51 PM
 *  Author: Abdallah Khater
 */ 


#ifndef UART_H_
#define UART_H_


//Macros to set/reset/read bit in a register
#define SET_BIT(reg, shift)				reg |= (1 << shift)
#define CLR_BIT(reg, shift)				reg &= ~(1 << shift)
#define Read_BIT(reg, shift)			((reg & (1 << shift)) >> shift)


#define Defaultstop						'\r'


/**================================================================
 * @Fn			-UART_INIT
 * @brief 		-This is used to initialize USART in Atmega32 
 * @retval 		-none
 * Note			-Frame used has 1 start bit, 8-bit data, no parity, 1 stop bit, with Baud rate: 9600 bps				
 */
void UART_INIT(void);

/**================================================================
 * @Fn			-UART_Send
 * @brief 		-This is used to transmit data using UART Protocol
 * @param [in] 	-data: Effective data to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_Send(unsigned char data);

/**================================================================
 * @Fn			-UART_Receive
 * @brief 		-This is used to receive data transmitted using UART Protocol
 * @retval 		-received data
 * Note			-none
 */
unsigned char UART_Receive(void);

/**================================================================
 * @Fn			-UART_SendNumberU32
 * @brief 		-This is used to transmit 32-bit data using UART Protocol
 * @param [in] 	-num: 32-bit number to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_SendNumberU32(unsigned int num);

/**================================================================
 * @Fn			-UART_ReceiveNumberU32
 * @brief 		-This is used to Receive 32-bit data using UART Protocol
 * @retval 		-32-bit received data
 * Note			-none
 */
unsigned int UART_ReceiveNumberU32(void);

/**================================================================
 * @Fn			-UART_SendString
 * @brief 		-This is used to Send a string using UART Protocol
 * @param [in] 	-pstr: pointer to string to be transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_SendString(char* pstr);

/**================================================================
 * @Fn			-UART_ReceiveString
 * @brief 		-This is used to receive string using UART Protocol
 * @param [in] 	-Buff: The string variable to receive the string transmitted
 * @retval 		-none
 * Note			-none
 */
void UART_ReceiveString(char* Buff);

/**================================================================
 * @Fn			-UART_Receive_PeriodicCheck
 * @brief 		-This is used to receive data without blocking the CPU
 * @param [in] 	-pdata: The string variable to receive the string transmitted
 * @retval 		-received data
 * Note			-none
 */
unsigned char UART_Receive_PeriodicCheck(unsigned char *pdata);

void UART_SendNoBlock(unsigned char data);

unsigned char UART_ReceiveNoBlock(unsigned char data);

void UART_RX_InterruptEnable(void);

void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);

void UART_TX_InterruptDisable(void);

void UART_SendString_Asynch(unsigned char *str);

#endif /* UART_H_ */