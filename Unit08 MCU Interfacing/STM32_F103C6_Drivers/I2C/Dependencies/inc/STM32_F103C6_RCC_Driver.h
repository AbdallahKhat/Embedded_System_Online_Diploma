/*
 * STM32_F103C6_RCC_Driver.h
 *
 *  Created on: June 15, 2023
 *      Author: Abdallah Khater
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

//Macros for oscillator frequencies
#define HSE_Clock					(uint32_t)16000000
#define HSI_RC_CLK					(uint32_t)8000000	//Freq: 8MHz

uint32_t MCAL_RCC_GetSYS_CLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
