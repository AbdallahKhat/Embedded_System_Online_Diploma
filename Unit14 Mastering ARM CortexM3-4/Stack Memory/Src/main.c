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


uint8_t TaskA_Flag, TaskB_Flag, IRQ_Flag;

#define TaskA_Stack_Size 100 //100 Bytes
#define TaskB_Stack_Size 100 //100 Bytes

extern unsigned int _estack;

//Main stack
unsigned int _S_MSP = (unsigned int)&_estack;
unsigned int _E_MSP ;

//Process stack Task A
unsigned int _S_PSP_TA ;
unsigned int _E_PSP_TA ;

//Process stack Task B
unsigned int _S_PSP_TB ;
unsigned int _E_PSP_TB ;


#define OS_SET_PSP(add)         __asm volatile("MSR PSP, %[in0]" : :[in0] "r" (add))
#define OS_SWITCH_SP_to_PSP     __asm volatile("MRS R3, CONTROL \n\t ORR R3, R3, #0x02 \n\t MSR CONTROL, R3")
#define OS_SWITCH_SP_to_MSP     __asm volatile("MRS R3, CONTROL \n\t ORR R3, R3, #0x02 \n\t EOR R3, R3, #0x02 \n\t MSR CONTROL, R3")

#define OS_Generate_Exception   __asm volatile("SVC #0x03")

#define SWITCH_CPU_AccessLevel_privileged       __asm("MRS R3, CONTROL   \n\t"\
                                                      "LSR R3, R3, #0x1  \n\t"\
                                                      "LSL R3, R3, #0x1  \n\t"\
                                                      "MSR CONTROL, R3")

#define SWITCH_CPU_AccessLevel_unprivileged     __asm("MRS R3, CONTROL   \n\t"\
                                                      "ORR R3, R3, #0x1  \n\t"\
                                                      "MSR CONTROL, R3");



void SVC_Handler ()
{
    SWITCH_CPU_AccessLevel_privileged;
}

void EXTI9_Callback(void)
{
    if(IRQ_Flag == 0)
    {
        TaskA_Flag = 1 ;
        IRQ_Flag = 1 ;
    }
    else if (IRQ_Flag == 1)
    {
        TaskB_Flag = 1 ;
        IRQ_Flag = 0 ;
    }
}

int TaskA(int a, int b, int c)
{
    return a + b + c ;
}

int TaskB(int a, int b, int c, int d)
{
    return a + b + c + d;
}


void mainOS()
{
    _E_MSP = (_S_MSP - 512) ;

    _S_PSP_TA = (_E_MSP - 8) ;
    _E_PSP_TA = (_S_PSP_TA - TaskA_Stack_Size) ;

    _S_PSP_TB = (_E_PSP_TA - 8) ;
    _E_PSP_TB = (_S_PSP_TB - TaskB_Stack_Size) ;

    while(1)
    {
        __asm("NOP");

        if(TaskA_Flag == 1)
        {
            //Set PSP Register = _S_PSP_TA
            OS_SET_PSP(_S_PSP_TA);
            //SP -> PSP
            OS_SWITCH_SP_to_PSP;
            //Switch from privileged -> unprivileged
            SWITCH_CPU_AccessLevel_unprivileged;

            TaskA_Flag = TaskA(1, 2, 3);

            //Switch from unprivileged -> privileged
            OS_Generate_Exception;

            //SP -> MSP
            OS_SWITCH_SP_to_MSP;
        }
        else if(TaskB_Flag == 1)
        {
            //Set PSP Register = _S_PSP_TB
            OS_SET_PSP(_S_PSP_TB);
            //SP -> PSP
            OS_SWITCH_SP_to_PSP;
            //Switch from privileged -> unprivileged
            SWITCH_CPU_AccessLevel_unprivileged;


            TaskB_Flag = TaskB(1, 2, 3, 4);

            //Switch from unprivileged -> privileged
            OS_Generate_Exception;
            //SP -> MSP
            OS_SWITCH_SP_to_MSP;
        }

    }

}

int main(void)
{
    //Enable clock
    RCC_GPIOB_CLK_EN();
    RCC_AFIO_CLK_EN();

    //Set EXTI Configurations
    EXTI_PinConfig_t EXTI_CFG ;
    EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
    EXTI_CFG.Trigger_Case = EXTI_Trigger_RISING ;
    EXTI_CFG.P_IRQ_Callback = EXTI9_Callback ;
    EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable ;
    MCAL_EXTI_GPIO_Init(&EXTI_CFG);



    mainOS();
    IRQ_Flag = 1;

    /* Loop forever */
    while(1)
    {
        if(IRQ_Flag)
        {
            IRQ_Flag = 0 ;
        }
        else{/* MISRA */}

    }
}
