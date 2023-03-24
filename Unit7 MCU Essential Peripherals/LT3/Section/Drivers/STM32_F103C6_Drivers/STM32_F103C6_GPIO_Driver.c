/*
 * STM32_F103C6_GPIO_Driver.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Abdallah Khater
 */

#include "STM32_F103C6_GPIO_Driver.h"



uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}

/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in]	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 				 the configuration information for the specified Pin
 * @retval 		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL)(x=A..E) configures pins from 0 >> 7
	//Port configuration register high (GPIOx_CRH)(x=A..E) configures pins from 8 >> 15

	volatile uint32_t* ConfigReg = NULL;
	uint8_t PIN_Config = 0;

	ConfigReg = (PinConfig->GPIO_PinNumber < GPIO_PIN_8 )? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNF[1:0] MODE[1:0]
	(*ConfigReg) &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if pin is output
	if(	(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP))
	{
		//set CNF[1:0] MODE[1:0]
		PIN_Config = ( (((PinConfig->GPIO_MODE -4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0F );
	}
	//if pin is input
	else	//Mode = 00: Input mode (reset state)
	{
		if((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog))
		{
			//set CNF[1:0]
			PIN_Config = ( ((PinConfig->GPIO_MODE) << 2) & 0x0F );

		}
		else if((PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT))	//Consider it as input floating
		{
			PIN_Config = ( (GPIO_MODE_INPUT_FLO << 2) & 0x0F );
		}
		else //PU PD Input
		{
			PIN_Config = ( (GPIO_MODE_INPUT_PU << 2) & 0x0F );

			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//PxODR = 1 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				//PxODR = 0 Input pull-down	 :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	//Write on the CRL or CRH
	(*ConfigReg) |= (PIN_Config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}


/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-reset all the GPIO Registers
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	//	GPIOx->CRL 	= 0x44444444;
	//	GPIOx->CRH 	= 0x44444444;
	//  GPIOx->IDR   (Read-only)
	//	GPIOx->ODR 	= 0x00000000;
	//	GPIOx->BSRR = 0x00000000;
	//	GPIOx->BRR 	= 0x00000000;
	//	GPIOx->LCKR = 0x00000000;

	//Or you can use the reset controller
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and cleared by software.

	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=  (1<<2);		//Bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=  (1<<3);		//Bit 3 IOPARST: IO port B reset
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if (GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=  (1<<4);		//Bit 4 IOPARST: IO port C reset
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if (GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=  (1<<5);		//Bit 5 IOPARST: IO port D reset
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if (GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=  (1<<6);		//Bit 6 IOPARST: IO port E reset
		RCC->APB2RSTR &= ~(1<<6);
	}
}


/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-read Specified PIN value
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		-The input pin value (two values based on @ref GPIO_PIN_state)
 * Note			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	uint8_t bitstatus ;
	if(((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET )
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}


/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-read the input PORT value
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @retval 		-The input port value
 * Note			-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t port_value;
	port_value = (uint16_t)GPIOx->IDR;
	return port_value;
}


/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-write on the specified output pin
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @param [in] 	-Value: Set specified pin according to @ref GPIO_PIN_state
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t Value)
{
	if(Value != GPIO_PIN_RESET )
	{
		//GPIOx->ODR |= PinNumber;
		//or

		//Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		//Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		GPIOx->BRR  = (uint32_t)PinNumber;
	}
}


/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-write on output port
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in] 	-Value: Set specified port value
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx,uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}


/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle specified GPIO Pin
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		-none
 * Note			-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	GPIOx->ODR ^= (uint32_t)PinNumber ;
}


/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration to be frozen
 * @param [in] 	-GPIOx: where x can be (A..E according to device used) to select the GPIO peripheral
 * @param [in] 	-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 		-OK if pin config is locked or ERROR if pin not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note			-none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked.

	//Set LCKK[16]
	volatile uint32_t tmp = (1 << 16) ;
	//Set the LCKy
	tmp |= PinNumber ;

	//	Write 1
	GPIOx->LCKR = tmp ;
	//	Write 0
	GPIOx->LCKR = PinNumber ;
	//	Write 1
	GPIOx->LCKR = tmp ;
	//	Read 0
	tmp = GPIOx->LCKR ;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)GPIOx->LCKR & (1<<16))
		return GPIO_RETURN_LOCK_Enable ;
	else
		return GPIO_RETURN_LOCK_Error ;

}
