/*
 * STM32_F103C6_USART_Driver.c
 *
 *  Created on: June 15, 2023
 *      Author: Abdallah Khater
 */

#include "STM32_F103C6_USART_Driver.h"


/*
 * ================================================================
 *                       Generic Variables
 * ================================================================
 */

UART_Config* Global_UART_Config[3] = {NULL,NULL,NULL};
UART_Config Global_UART_Config1 ;
UART_Config Global_UART_Config2 ;
UART_Config Global_UART_Config3 ;


/*
 * ================================================================
 *                     API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes UART (Supported feature: ASYNCH. only)
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @param [in] 	-UART_Config: All UART Configuration UART_Config
 * @retval 		-none
 * Note			-Support for now: Asynch. mode & Clock 8 MHz
 */
void MCAL_UART_Init (USART_TypeDef* USARTx,UART_Config* UART_Config)
{
	uint32_t pclk, BRR;

	//Assigning UART_Config pointer to Global_UART_Config pointer for use in another functions
	if(USARTx == USART1)
	{
		Global_UART_Config1 = *UART_Config ;
		Global_UART_Config[0] = &Global_UART_Config1 ;
	}
	else if(USARTx == USART2)
	{
		Global_UART_Config2 = *UART_Config ;
		Global_UART_Config[1] = &Global_UART_Config2 ;
	}
	else if(USARTx == USART3)
	{
		Global_UART_Config3 = *UART_Config ;
		Global_UART_Config[2] = &Global_UART_Config3;
	}

	//Enable the clock for given USART Peripheral
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();

	else if(USARTx == USART2)
		RCC_USART2_CLK_EN();

	else if(USARTx == USART3)
		RCC_USART3_CLK_EN();

	//Enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= (1<<13);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode ;

	//PAYLOAD WIDTH
	//USARTx->CR1 Bit 12 M: Word Length
	USARTx->CR1 |= UART_Config->Payload_Length ;

	//Configuration of Parity control bit field
	//USARTx->CR1 Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity ;

	//Configure the number of stop bits
	//USART_CR2 Bits 13:12 STOP: STOP Bits
	USARTx->CR2 |= UART_Config->StopBits ;

	//USART Hardware flow control
	//USART_CR3 Bit 9 CTSE: CTS enable	Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HwFlowCtl ;

	//configuration of BRR(Baudrate Register)
	//PCLK1 for UART2,3
	//PCLK2 for UART1

	if( USARTx == USART1 )
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = UART_BRR_Register(pclk,UART_Config->BaudRate);
	USARTx->BRR = BRR;


	//Enable / Disable Interrupt
	//USART_CR1

	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		//Enable NVIC for USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable();

		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable();

		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable();

	}

}


/**================================================================
 * @Fn			-MCAL_UART_DeInit
 * @brief 		-De-Initializes UART (Supported feature: ASYNCH. only)
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @retval 		-none
 * Note			-Reset the module by RCC
 */
void MCAL_UART_DeInit (USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable();
	}

	else if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable();
	}

	else if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable();
	}
}


/**================================================================
 * @Fn			-MCAL_UART_SendData
 * @brief 		-Send Buffer on UART
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @param [in] 	-pTxBuffer: Buffer to be sent
 * @param [in] 	-PollingEn: Enable polling or disable it
 * @retval 		-none
 * Note			-Should initialize UART first
 * 				When transmitting with the parity enable (PCE bit set to 1 in the USART_CR1 register),
 * 				the value written in the MSB (Bit 7 or 8 depending on the data length) has no effect
 * 				because it is replaced by the parity.
 * 				When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_UART_SendData (USART_TypeDef* USARTx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn)
{
	//wait until the TXE Flag is set in the SR
	if(PollingEn == enable)
		while(!(USARTx->SR & (1<<7)));


	//Check the USART_WordLength item for 9BIT or 8BIT in a frame

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit.

	if(USARTx == USART1)
	{
		if(Global_UART_Config[0]->Payload_Length ==  UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
		}
		else
		{
			//This is 8bit data transfer
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}

	else if(USARTx == USART2)
	{
		if(Global_UART_Config[1]->Payload_Length ==  UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
		}
		else
		{
			//This is 8bit data transfer
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}

	else if(USARTx == USART3)
	{
		if(Global_UART_Config[2]->Payload_Length ==  UART_Payload_Length_9B)
		{
			USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
		}
		else
		{
			//This is 8bit data transfer
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}

}


/**================================================================
 * @Fn			-MCAL_UART_Wait_TC
 * @brief 		-Wait till Transmission complete
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @retval 		-none
 * Note			-none
 */
void MCAL_UART_Wait_TC (USART_TypeDef *USARTx)
{
	//Wait till TC flag is set in the SR
	while(!(USARTx->SR & (1<<6)));
}


/**================================================================
 * @Fn			-MCAL_UART_ReceiveData
 * @brief 		-Receive Buffer on UART
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @param [in] 	-pRxBuffer: Buffer to receive data
 * @param [in] 	-PollingEn: Enable polling or disable it
 * @retval 		-none
 * Note			-Should initialize UART first
 * 				When transmitting with the parity enable (PCE bit set to 1 in the USART_CR1 register),
 * 				the value written in the MSB (Bit 7 or 8 depending on the data length) has no effect
 * 				because it is replaced by the parity.
 * 				When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_UART_ReceiveData (USART_TypeDef* USARTx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn)
{

	//wait until the RXNE Flag is set in the SR
	if(PollingEn == enable)
		while(!(USARTx->SR & (1<<5)));


	//Check the USART_WordLength item for 9BIT or 8BIT in a frame

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit.

	if(USARTx == USART1)
	{
		if(Global_UART_Config[0]->Payload_Length ==  UART_Payload_Length_9B)
		{
			if(Global_UART_Config[0]->Parity == UART_Parity_NONE)
			{
				//No parity so all 9 bits are considered data
				*((uint16_t*)pRxBuffer) = USARTx->DR ;
			}
			else
			{
				//Parity is used, so, 8bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
		}

		else
		{
			//This is 8bit data
			if(Global_UART_Config[0]->Parity == UART_Parity_NONE)
			{
				//No parity so all 8 bits are considered data
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
			else
			{
				//Parity is used, so, 7bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0x7F ) ;
			}
		}
	}

	else if(USARTx == USART2)
	{
		if(Global_UART_Config[1]->Payload_Length ==  UART_Payload_Length_9B)
		{
			if(Global_UART_Config[1]->Parity == UART_Parity_NONE)
			{
				//No parity so all 9 bits are considered data
				*((uint16_t*)pRxBuffer) = USARTx->DR ;
			}
			else
			{
				//Parity is used, so, 8bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
		}

		else
		{
			//This is 8bit data
			if(Global_UART_Config[1]->Parity == UART_Parity_NONE)
			{
				//No parity so all 8 bits are considered data
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
			else
			{
				//Parity is used, so, 7bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0x7F ) ;
			}
		}
	}

	else if(USARTx == USART3)
	{
		if(Global_UART_Config[2]->Payload_Length ==  UART_Payload_Length_9B)
		{
			if(Global_UART_Config[2]->Parity == UART_Parity_NONE)
			{
				//No parity so all 9 bits are considered data
				*((uint16_t*)pRxBuffer) = USARTx->DR ;
			}
			else
			{
				//Parity is used, so, 8bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
		}

		else
		{
			//This is 8bit data
			if(Global_UART_Config[2]->Parity == UART_Parity_NONE)
			{
				//No parity so all 8 bits are considered data
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
			}
			else
			{
				//Parity is used, so, 7bits will be the user data and 1 bit is parity
				*((uint16_t*)pRxBuffer) = ( USARTx->DR & (uint8_t)0x7F ) ;
			}
		}
	}

}


/**================================================================
 * @Fn			-MCAL_UART_GPIO_Set_pins
 * @brief 		-Initializes GPIO Pins
 * @param [in] 	-USARTx: where x can be (1..3 depending on device used)
 * @retval 		-none
 * Note			-Should enable the corresponding ALT & GPIO in RCC Clock, also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_pins (USART_TypeDef* USARTx)
{
	GPIO_PinConfig_t PinCfg ;

	if( USARTx == USART1 )
	{
		//PA9 	TX
		//PA10 	RX
		//PA11	CTS
		//PA12	RTS


		//PA9 	TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9 ;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 	RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10 ;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA11	CTS
		if(Global_UART_Config[0]->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_11 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		//PA12	RTS
		if(Global_UART_Config[0]->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[0]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_12 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}

	else if( USARTx == USART2 )
	{
		//PA2 	TX
		//PA3 	RX
		//PA0	CTS
		//PA1	RTS


		//PA2 	TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2 ;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 	RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3 ;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA0	CTS
		if(Global_UART_Config[1]->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_0 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		//PA1	RTS
		if(Global_UART_Config[1]->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[1]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}

	else if( USARTx == USART3 )
	{
		//PB10 	TX
		//PB11 	RX
		//PB13	CTS
		//PB14	RTS


		//PB10 	TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10 ;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 	RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11 ;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB13	CTS
		if(Global_UART_Config[2]->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

		//PB14	RTS
		if(Global_UART_Config[2]->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config[2]->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

	}

}


//==============================ISR==============================

void USART1_IRQHandler(void)        			// USART1 global interrupt
{
	Global_UART_Config[0]->P_IRQ_Callback() ;
}
void USART2_IRQHandler(void)        			// USART2 global interrupt
{
	Global_UART_Config[1]->P_IRQ_Callback() ;
}
void USART3_IRQHandler(void)        			// USART3 global interrupt
{
	Global_UART_Config[2]->P_IRQ_Callback() ;
}














