/*
 * CortexMX_OS_Porting.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Abdallah Khater
 */


#include "CortexMX_OS_Porting.h"


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

}
