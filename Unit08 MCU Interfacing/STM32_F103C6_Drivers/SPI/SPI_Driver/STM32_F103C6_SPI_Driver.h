/*
 * STM32_F103C6_SPI_Driver.h
 *
 *  Created on: Jun 18, 2023
 *      Author: Abdallah Khater
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

//-----------------------------

struct S_IRQ_SRC
{
	uint8_t TXE:1 ;			//Tx buffer empty interrupt

	uint8_t RXNE:1 ;		//Rx buffer not empty interrupt

	uint8_t ERRI:1 ;		//Error interrupt

	uint8_t Reserved:5 ;
};

//-----------------------------
//User type definitions (structures)
//-----------------------------

//Configuration structure
typedef struct
{
	uint16_t	Device_Mode ;			//Specifies the SPI operating mode (Master/Slave)
										//This parameter must be set based on @ref SPI_Device_Mode_define


	uint16_t	Communication_Mode ;	//Specifies the SPI bidirectional mode state
										//This parameter must be set based on @ref SPI_Communication_Mode_define


	uint16_t	Frame_Format ;			//Specifies LSB or MSB to be transmitted first
										//This parameter must be set based on @ref SPI_Frame_Format_define


	uint16_t	DataSize ;				//Specifies 8-bit data frame format or 16-bit data frame format
										//This parameter must be set based on @ref SPI_DataSize_define


	uint16_t	CLKPolarity	;			//Specifies the clock polarity (idle high or idle low)
										//This parameter must be set based on @ref SPI_CLKPolarity_define


	uint16_t	CLKPhase ;				//Specifies the clock phase (which clock transition [1st/2nd] is the first capture edge)
										//This parameter must be set based on @ref SPI_CLKPhase_define


	uint16_t	NSS ;					//Specifies whether the NSS signal is managed by
										//hardware (NSS Pin) or software using the SSI bit enable
										//This parameter must be set based on @ref SPI_NSS_define


	uint16_t	BAUDRATEPRESCALER ;		//Specifies the Baud rate pre-scaler value which will be used
										//to configure the transmit and receive SCK clock
										//This parameter must be set based on @ref SPI_BAUDRATEPRESCALER_define
										//@note: the communication clock is derived from the master clock.
										//the slave clock does not need to be set.
										//@note: you have to configure the RCC to enter the correct clock to APB2 >>> to SPI1 / APB1 >>> to SPI2


	uint16_t	IRQ_Enable ;			//Enable or Disable SPI IRQ
										//This parameter must be set based on @ref SPI_IRQ_Enable_define
										//You can select two or three parameters. EX: SPI_IRQ_Enable_TXIE | SPI_IRQ_Enable_RXNEIE


	void(* P_IRQ_Callback)(struct S_IRQ_SRC irq_src) ;
										//set the C function() which will be called once IRQ happens

}SPI_Config;


//-------------------------------
//====== References Macros ======
//-------------------------------

//@ref SPI_Device_Mode_define
#define SPI_Device_Mode_Master							(0x1U<<2)					//CR1. Bit 2 MSTR: 1: Master configuration
#define SPI_Device_Mode_Slave							(0)							//CR1. Bit 2 MSTR: 0: Slave configuration


//@ref SPI_Communication_Mode_define
#define SPI_DIRECTION_2LINES							(0)							//CR1. Default
#define SPI_DIRECTION_2LINES_RXONLY						(0x1U<<10)					//CR1. Bit 10 RXONLY: Receive only
#define SPI_DIRECTION_1LINE_receive_only				(0x1U<<15)					//CR1. Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_DIRECTION_1LINE_transmit_only				((0x1U<<15) | (0x1U<<14))	//CR1. Bit 15 BIDIMODE: Bidirectional data mode enable & Bit 14 BIDIOE: Output enable in bidirectional mode


//@ref SPI_Frame_Format_define
#define SPI_Frame_Format_MSB_Transmit_First				(0)							//CR1. Default
#define SPI_Frame_Format_LSB_Transmit_First				(0x1U<<7)					//CR1. Bit 7 LSBFIRST: Frame format


//@ref SPI_DataSize_define
#define SPI_DataSize_8BIT								(0)							//CR1. Default
#define SPI_DataSize_16BIT								(0x1U<<11)					//CR1. Bit 11 DFF: Data frame format


//@ref SPI_CLKPolarity_define
#define SPI_CLKPolarity_LOW_when_idle					(0)							//CR1. Default
#define SPI_CLKPolarity_HIGH_when_idle					(0x1U<<1)					//CR1. Bit1 CPOL: Clock polarity


//@ref SPI_CLKPhase_define
#define SPI_CLKPhase_1EDGE_first_data_capture_edge		(0)							//CR1. Default
#define SPI_CLKPhase_2EDGE_first_data_capture_edge		(0x1U<<0)					//CR1. Bit 0 CPHA: Clock phase


//@ref SPI_NSS_define	SPI Slave Select Management
//=======================NSS=======================
//NSS is driven by Hardware
#define SPI_NSS_Hard_Slave								(0)							//CR1. Default
#define SPI_NSS_Hard_Master_SS_output_enable			(0x1U<<2)					//CR2. Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable			(uint16_t)~(0x1U<<2)		//CR2. Bit 2 SSOE: SS output disable

//NSS is driven by Software (Master or Slave)
#define SPI_NSS_Soft_NSSInternalSoft_Reset				(0x1U<<9)					//CR1. Bit 9 SSM: Software slave management & Bit 8 SSI: default (zero)
#define SPI_NSS_Soft_NSSInternalSoft_Set				((0x1U<<9) | (0x1U<<8))		//CR1. Bit 9 SSM: Software slave management & Bit 8 SSI: Internal slave select
//=================================================


//@ref SPI_BAUDRATEPRESCALER_define
#define SPI_BAUDRATEPRESCALER_2							(0)							//CR1. Bits 5:3 BR[2:0]: 000: fPCLK/2
#define SPI_BAUDRATEPRESCALER_4							(0b001U << 3)				//CR1. Bits 5:3 BR[2:0]: 001: fPCLK/4
#define SPI_BAUDRATEPRESCALER_8							(0b010U << 3)				//CR1. Bits 5:3 BR[2:0]: 010: fPCLK/8
#define SPI_BAUDRATEPRESCALER_16						(0b011U << 3)				//CR1. Bits 5:3 BR[2:0]: 011: fPCLK/16
#define SPI_BAUDRATEPRESCALER_32						(0b100U << 3)				//CR1. Bits 5:3 BR[2:0]: 100: fPCLK/32
#define SPI_BAUDRATEPRESCALER_64						(0b101U << 3)				//CR1. Bits 5:3 BR[2:0]: 101: fPCLK/64
#define SPI_BAUDRATEPRESCALER_128						(0b110U << 3)				//CR1. Bits 5:3 BR[2:0]: 110: fPCLK/128
#define SPI_BAUDRATEPRESCALER_256						(0b111U << 3)				//CR1. Bits 5:3 BR[2:0]: 111: fPCLK/256


//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_NONE								(0)							//CR2. Default
#define SPI_IRQ_Enable_TXIE								(0x1U<<7)					//CR2. Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE							(0x1U<<6)					//CR2. Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE							(0x1U<<5)					//CR2. Bit 5 ERRIE: Error interrupt enable



enum PollingMechanism
{
	pollingEnable ,
	pollingDisable
};

/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_Set_pins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData (SPI_TypeDef* SPIx, uint16_t *pTxBuffer, enum PollingMechanism PollingEn);

void MCAL_SPI_ReceiveData (SPI_TypeDef* SPIx, uint16_t *pRxBuffer, enum PollingMechanism PollingEn);

void MCAL_SPI_TX_RX (SPI_TypeDef* SPIx, uint16_t *pTxRxBuffer, enum PollingMechanism PollingEn);



#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
