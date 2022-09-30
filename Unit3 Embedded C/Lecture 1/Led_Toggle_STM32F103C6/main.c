/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdallah Khater
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>


#define RCC_Base   0x40021000
#define PortA_Base 0x40010800
#define RCC_APB2ENR    (RCC_Base + 0x18)
#define PortA_CRH  (PortA_Base + 0x04)
#define PortA_ODR  (PortA_Base + 0x0c)

typedef union
{
	volatile uint32_t all_ports;

	struct
	{
		volatile uint32_t pinsA:8;
		volatile uint32_t pinsB:8;
		volatile uint32_t pinsC:8;
		volatile uint32_t pinsD:8;
	}pins;

}Reg;

int main(void)
{

	volatile Reg* pAPB2ENR = (volatile Reg*)RCC_APB2ENR;
	volatile Reg* pPortA_CRH = (volatile Reg*)PortA_CRH;
	volatile Reg* pPortA_ODR = (volatile Reg*)PortA_ODR;

	pAPB2ENR->pins.pinsA |= 2;
	pPortA_CRH->pins.pinsD &= 0x0f;
	pPortA_CRH->pins.pinsD |= 0x20;

	while(1)
	{
		pPortA_ODR->pins.pinsB |= 0x10;
		for(int i = 0; i<5000;i++);
		pPortA_ODR->pins.pinsB &= ~(0x10);
		for(int i = 0; i<5000;i++);
	}

	return 0;
}
