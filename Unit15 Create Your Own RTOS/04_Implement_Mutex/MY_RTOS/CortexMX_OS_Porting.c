/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Abdallah Khater
 */


#include "CortexMX_OS_Porting.h"

unsigned char SysTickLED ;

void HardFault_Handler(void)
{
    while(1);
}
void MemManage_Handler(void)
{
    while(1);
}
void BusFault_Handler(void)
{
    while(1);
}
void UsageFault_Handler(void)
{
    while(1);
}


__attribute ((naked)) void SVC_Handler ()
{
    __asm("TST   LR,#0x04     \n\t"
          "ITE   EQ           \n\t"
          "MRSEQ R0,MSP       \n\t"
          "MRSNE R0,PSP       \n\t"
          "B OS_SVC               ");
}

void HW_Init(void)
{
    //Initialize Clock Tree (RCC -> Systick Timer & CPU) 8MHz
    //Init HW
    //Clock Tree
    //RCC Default values make CPU clock & Systick Timer clock = 8 MHz

    // 8 MHz
    // 1 Tick  ->  0.125 us
    // x Ticks ->  1 ms
    // x = 8000 Count

    //Decrease PendSV interrupt priority to be smaller than or equal Systick Timer
    //Systick Timer has priority 14
    __NVIC_SetPriority(PendSV_IRQn, 15) ;

}

void trigger_OS_PendSV()
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}

void Start_Ticker()
{
    // This Clock tree should be defined in HW_init()
    // 8MHz
    // 1 count -> 0.125 us
    // x count -> 1 ms
    // x = 8000

    SysTick_Config(8000) ;  //1ms
}

void SysTick_Handler(void)
{
    SysTickLED ^= 1 ;
    MYRTOS_Update_TasksWaitingTime();

    //Determine Pcurrent and Pnext
    Decide_whatNext();

    //Switch Context save & restore
    trigger_OS_PendSV();


}
