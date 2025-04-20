/*
 * STM32_F103C6_SPI_Driver.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Abdallah Khater
 */


#include "STM32_F103C6_SPI_Driver.h"


/*
 * ================================================================
 * 						Generic Variables
 * ================================================================
 */

SPI_Config* Global_SPI_Config[2] = {NULL,NULL}  ;
SPI_Config Global_SPI_Config1 ;
SPI_Config Global_SPI_Config2 ;

/*
 * ================================================================
 * 						Generic Macros
 * ================================================================
 */

#define		SPI1_INDEX		0
#define		SPI2_INDEX		1

#define		SPI_SR_TXE		(1<<1)					/* Transmit buffer empty */
#define		SPI_SR_RXNE		(1<<0)					/* Receive buffer not empty */
#define		SPI_SR_CRCERR	(1<<4)					/* CRCERR: CRC error flag */

/*
 * ================================================================
 * 						API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initializes the SPI according to specified parameters
 * @param [in] 	-SPIx: where x can be (1..2 depending on device used)
 * @param [in] 	-SPI_Config: All SPI Configuration SPI_Config
 * @retval 		-none
 * Note			-Support for SPI Full-duplex Master/slave only & NSS HW/SW
 * 				-in case of Master, you have to configure pin and drive it
 */
void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config* SPI_Config)
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0 ;
	uint16_t tmpreg_CR2 = 0 ;

	//Backup for SPI_Config to Global_SPI_Config for use in another functions
	//& Enable the clock for given USART Peripheral
	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config ;
		Global_SPI_Config[SPI1_INDEX] = &Global_SPI_Config1 ;
		RCC_SPI1_CLK_EN();
	}
	else if (SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_Config ;
		Global_SPI_Config[SPI2_INDEX] = &Global_SPI_Config2 ;
		RCC_SPI2_CLK_EN();
	}


	//Enable SPI.. CR1:Bit 6 SPE: SPI enable
	tmpreg_CR1 = (0x1U<<6);

	//Master or slave
	tmpreg_CR1 |= SPI_Config->Device_Mode ;

	//SPI Communication mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode ;

	//SPI Frame Format
	tmpreg_CR1 |= SPI_Config->Frame_Format ;

	//SPI Data Size
	tmpreg_CR1 |= SPI_Config->DataSize ;

	//SPI Clock Polarity
	tmpreg_CR1 |= SPI_Config->CLKPolarity ;

	//SPI Clock Phase
	tmpreg_CR1 |= SPI_Config->CLKPhase ;

	//=======================NSS=======================

	if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS ;
	}
	else if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable)
	{
		tmpreg_CR2 &= SPI_Config->NSS ;
	}
	else
	{
		tmpreg_CR1 |= SPI_Config->NSS ;
	}

	//=================================================

	//SPI Baud rate Pre-scaler
	tmpreg_CR1 |= SPI_Config->BAUDRATEPRESCALER ;

	//Enable / Disable Interrupt
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable() ;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable() ;
		}

	}


	//Assigning safety registers to SPIx registers
	SPIx->CR1 = tmpreg_CR1 ;
	SPIx->CR2 = tmpreg_CR2 ;

}


/**================================================================
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-De-Initializes SPI Module
 * @param [in] 	-SPIx: where x can be (1..2 depending on device used)
 * @retval 		-none
 * Note			-Reset the module by RCC
 */
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	//Reset Module by RCC and Reset NVIC IRQ Mask
	if(SPIx == SPI1)
	{
		RCC_SPI1_Reset() ;
		NVIC_IRQ35_SPI1_Disable() ;
	}
	else if(SPIx == SPI2)
	{
		RCC_SPI2_Reset() ;
		NVIC_IRQ36_SPI2_Disable() ;
	}
}


/**================================================================
 * @Fn			-MCAL_SPI_SendData
 * @brief 		-Send Buffer on SPI
 * @param [in] 	-USARTx: where x can be (1..2 depending on device used)
 * @param [in] 	-pTxBuffer: Buffer to be sent
 * @param [in] 	-PollingEn: Enable polling or disable it
 * @retval 		-none
 * Note			-Should initialize SPI first
 * 				-Only transmits the buffer, buffer's value doesn't get replaced by the received buffer
 * 				-Only supports Full-duplex for now
 */
void MCAL_SPI_SendData (SPI_TypeDef* SPIx, uint16_t *pTxBuffer, enum PollingMechanism PollingEn)
{
	//todo check communication mode: transmit only

	//wait until the TXE Flag is set in the SR
	if(PollingEn == pollingEnable)
		while(!(SPIx->SR & SPI_SR_TXE));

	//Sends Buffer to Transmit buffer in DR to be transmitted
	SPIx->DR = *pTxBuffer;

}


/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief 		-Receive Buffer on SPI
 * @param [in] 	-SPIx: where x can be (1..2 depending on device used)
 * @param [in] 	-pRxBuffer: Buffer to receive data
 * @param [in] 	-PollingEn: Enable polling or disable it
 * @retval 		-none
 * Note			-Should initialize SPI first
 *				-Only supports Full-duplex for now
 */
void MCAL_SPI_ReceiveData (SPI_TypeDef* SPIx, uint16_t *pRxBuffer, enum PollingMechanism PollingEn)
{
	//todo check communication mode: Receive only

	//wait until the RXNE Flag is set in the SR
	if(PollingEn == pollingEnable)
		while(!(SPIx->SR & SPI_SR_RXNE));

	//Reads Buffer from Receive buffer in DR
	*pRxBuffer = SPIx->DR ;

}


/**================================================================
 * @Fn			-MCAL_SPI_TX_RX
 * @brief 		-Transmits and Receive Buffer on SPI
 * @param [in] 	-SPIx: where x can be (1..2 depending on device used)
 * @param [in] 	-pTxRxBuffer: Buffer to transmit and receive data
 * @param [in] 	-PollingEn: Enable polling or disable it
 * @retval 		-none
 * Note			-Should initialize SPI first
 * 				-Transmits buffer, then content of buffer is replaced by the received buffer
 *				-Only supports Full-duplex
 */
void MCAL_SPI_TX_RX (SPI_TypeDef* SPIx, uint16_t *pTxRxBuffer, enum PollingMechanism PollingEn)
{

	//wait until the TXE Flag is set in the SR
	if(PollingEn == pollingEnable)
		while(!(SPIx->SR & SPI_SR_TXE));

	//Sends Buffer to Transmit buffer in DR to be transmitted
	SPIx->DR = *pTxRxBuffer;

	//wait until the RXNE Flag is set in the SR
	if(PollingEn == pollingEnable)
		while(!(SPIx->SR & SPI_SR_RXNE));

	//Reads Buffer from Receive buffer in DR
	*pTxRxBuffer = SPIx->DR ;

}


/**================================================================
 * @Fn			-MCAL_SPI_GPIO_Set_pins
 * @brief 		-Initializes GPIO Pins
 * @param [in] 	-SPIx: where x can be (1..3 depending on device used)
 * @retval 		-none
 * Note			-Should enable the corresponding ALT & GPIO in RCC Clock, also called after MCAL_SPI_Init()
 */
void MCAL_SPI_GPIO_Set_pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PinCfg ;

	if(SPIx == SPI1)
	{
		//PA4	SPI1_NSS
		//PA5	SPI1_SCK
		//PA6 	SPI1_MISO
		//PA7	SPI1_MOSI

		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_Master)	//Master Mode
		{
			//PA4	SPI1_NSS

			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master / slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOA, &PinCfg) ;
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master / NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOA, &PinCfg) ;
				break;
			}

			//PA5	SPI1_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;


			//PA6 	SPI1_MISO	(Supports only Full duplex)
			//Full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;

			//todo support half duplex and simplex

			//PA7	SPI1_MOSI	(Supports only Full duplex)
			//Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		}

		else //Slave Mode
		{
			//PA4	SPI1_NSS

			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master / slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4 ;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOA, &PinCfg) ;
			}

			//PA5	SPI1_SCK
			//Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_5 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;


			//PA6 	SPI1_MISO	(Supports only Full duplex)
			//Full duplex / slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_6 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;

			//todo Full duplex / slave (multi-slave) Alternate function open drain

			//PA7	SPI1_MOSI	(Supports only Full duplex)
			//Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_7 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOA, &PinCfg) ;

		}

	}
	else if(SPIx == SPI2)
	{
		//PB12	SPI2_NSS
		//PB13	SPI2_SCK
		//PB14 	SPI2_MISO
		//PB15	SPI2_MOSI

		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_Master)	//Master Mode
		{
			//PB12	SPI2_NSS

			switch(Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master / slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOB, &PinCfg) ;
				break;

			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master / NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOB, &PinCfg) ;
				break;
			}

			//PB13	SPI2_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;


			//PB14 	SPI2_MISO	(Supports only Full duplex)
			//Full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;

			//todo support half duplex and simplex

			//PB15	SPI2_MOSI	(Supports only Full duplex)
			//Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_15 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;

		}

		else //Slave Mode
		{
			//PB12	SPI2_NSS

			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master / slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12 ;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
				MCAL_GPIO_Init(GPIOB, &PinCfg) ;
			}

			//PB13	SPI2_SCK
			//Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;


			//PB14 	SPI2_MISO	(Supports only Full duplex)
			//Full duplex / slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_14 ;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP ;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;

			//todo Full duplex / slave (multi-slave) Alternate function open drain

			//PB15	SPI2_MOSI	(Supports only Full duplex)
			//Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_15 ;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO ;
			MCAL_GPIO_Init(GPIOB, &PinCfg) ;

		}

	}

}


/*
 * ================================================================
 * 							IRQ Handler
 * ================================================================
 */

void SPI1_IRQHandler(void)           			// SPI1 global interrupt
{
	struct S_IRQ_SRC irq_src ;

	irq_src.TXE = (((SPI1->SR) & (SPI_SR_TXE)) >> 1);
	irq_src.RXNE = (((SPI1->SR) & (SPI_SR_RXNE)) >> 0);
	irq_src.ERRI = (((SPI1->SR) & (SPI_SR_CRCERR)) >> 4);

	Global_SPI_Config[SPI1_INDEX]->P_IRQ_Callback(irq_src) ;

}
void SPI2_IRQHandler(void)           			// SPI2 global interrupt
{
	struct S_IRQ_SRC irq_src ;

	irq_src.TXE = (((SPI2->SR) & (SPI_SR_TXE)) >> 1);
	irq_src.RXNE = (((SPI2->SR) & (SPI_SR_RXNE)) >> 0);
	irq_src.ERRI = (((SPI2->SR) & (SPI_SR_CRCERR)) >> 4);

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_Callback(irq_src) ;

}



