/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "STM32F103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_EXTI_Driver.h"
#include "lcd_driver.h"
#include "Keypad_Driver.h"


unsigned int IRQ_Flag = 0;

void my_wait(int x)
{
	unsigned int i , j;
	for(i = 0; i < x ; i++)
		for(j = 0; j < 255 ;j++);
}

void EXTI9_Callback(void)
{
	IRQ_Flag = 1 ;
	LCD_WRITE_STRING("IRQ EXTI9 has happened _|-");
	my_wait(1000);
}

int main(void)
{
	//Enable clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	LCD_INIT();
	LCD_clear_screen();


	EXTI_PinConfig_t EXTI_CFG ;
	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Trigger_Case = EXTI_Trigger_RISING ;
	EXTI_CFG.P_IRQ_Callback = EXTI9_Callback ;
	EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable ;

	MCAL_EXTI_GPIO_Init(&EXTI_CFG);

	IRQ_Flag = 1;

	/* Loop forever */
	while(1)
	{
		if(IRQ_Flag)
		{
			LCD_clear_screen();
			IRQ_Flag = 0 ;
		}

	}
}
