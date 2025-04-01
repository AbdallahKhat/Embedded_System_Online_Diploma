/*
 * CortexMX_OS_Porting.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Abdallah Khater
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"
#include "Scheduler.h"

extern unsigned int _estack ;
extern unsigned int _eheap ;

//Main stack size
#define MainStackSize 3072  //3kb

#define OS_SET_PSP(add)         __asm volatile("MSR PSP, %[in0] " : : [in0] "r" (add))
#define OS_GET_PSP(add)         __asm volatile("MRS %[out0], PSP" : [out0] "=r" (add))

#define OS_SWITCH_SP_to_PSP     __asm volatile("MRS R3, CONTROL \n\t ORR R3, R3, #0x02 \n\t MSR CONTROL, R3")
#define OS_SWITCH_SP_to_MSP     __asm volatile("MRS R3, CONTROL \n\t ORR R3, R3, #0x02 \n\t EOR R3, R3, #0x02 \n\t MSR CONTROL, R3")

//Clear bit 0 CONTROL Register
#define OS_SWITCH_to_privileged       __asm("MRS R3, CONTROL   \n\t"\
                                            "LSR R3, R3, #0x1  \n\t"\
                                            "LSL R3, R3, #0x1  \n\t"\
                                            "MSR CONTROL, R3       ")
//Set bit 0 CONTROL Register
#define OS_SWITCH_to_unprivileged     __asm("MRS R3, CONTROL   \n\t"\
                                            "ORR R3, R3, #0x1  \n\t"\
                                            "MSR CONTROL, R3       ")




void HW_Init(void);

void trigger_OS_PendSV(void);

void Start_Ticker(void);


#endif /* INC_CORTEXMX_OS_PORTING_H_ */
