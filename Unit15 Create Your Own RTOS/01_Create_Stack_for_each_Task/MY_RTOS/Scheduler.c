/*
 * Scheduler.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Abdallah Khater
 */


#include "Scheduler.h"
#include "MYRTOS_FIFO.h"
#include "string.h"

struct{
    Task_ref* OSTasks[100] ;    //Scheduler Table
    unsigned int _S_MSP_Task ;
    unsigned int _E_MSP_Task ;
    unsigned int PSP_Task_Locator ;
    unsigned int NoOfActiveTasks ;
    Task_ref* CurrentTask ;
    Task_ref* NextTask ;
    enum{
        OSsuspend,
        OSrunning
    }OSmodeID;
}OS_Control;

FIFO_buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100];
Task_ref MYRTOS_idleTask ;

//To get specific OS Service
void OS_SVC(int* StackFramePointer)
{
    //OS_SVC_Set stack -> R0 -> argument 0 = StackFramePointer
    //OS_SVC_Set stack : R0,R1,R2,R3,R12,LR,PC,xPSR

    unsigned char SVC_number  ;

    SVC_number = ((unsigned char *)StackFramePointer[6])[-2];

    switch(SVC_number)
    {
    case 0: //Activate Task

        break;

    case 1: //Terminal Task
        break;

    case 2:

        break;
    case 3:

        break;
    }

}

void PendSV_Handler()
{
    /* PendSV_Handler Body */
}

void MYRTOS_Create_MainStack()
{
    OS_Control._S_MSP_Task = (unsigned int)&_estack ;
    OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize ;

    //Aligned 8 Bytes Spaces between Main Task and PSP Tasks
    OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8) ;

    //if(_E_MSP_Task < &_eheap) ERROR: Exceeded the available stack size
}

void MYRTOS_IdleTask (void)
{
    while(1)
    {
        __asm("NOP");
    }
}

MYRTOS_error_ID MYRTOS_Init()
{
    MYRTOS_error_ID error = NoError;

    //Update OS Mode (OSsuspend)
    OS_Control.OSmodeID = OSsuspend ;

    //Specify the Main Stack for OS
    MYRTOS_Create_MainStack() ;

    //Create OS Ready Queue
    if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) != FIFO_no_error)
    {
        error += Ready_Queue_init_error ;
    }

    //Configure IDLE Task
    strcpy(MYRTOS_idleTask.TaskName,"idleTask") ;
    MYRTOS_idleTask.Priority = 255 ; //Lowest priority
    MYRTOS_idleTask.p_TaskEntry = MYRTOS_IdleTask ;
    MYRTOS_idleTask.Stack_Size = 300 ;

    error += MYRTOS_Create_Task(&MYRTOS_idleTask);


    return error;

}

void MYRTOS_Create_TaskStack(Task_ref* Tref)
{
    /*Task Frame
     * ======
     * xPSR
     * PC (Next Task Instruction Which should be Run)
     * LR (Return register which is saved in CPU while Task1 running before task switching)
     * R12
     * R3
     * R2
     * R1
     * R0
     * ======
     * ======
     * R4,R5,R6,R7,R8,R9,R10,R11 (Saved/Restored) Manual
     */

    Tref->Current_PSP = (unsigned int*)Tref->_S_PSP_Task ;

    Tref->Current_PSP-- ;
    *(Tref->Current_PSP) = 0x1000000 ; //Dummy xPSR, T-bit should be = 1 to avoid Bus fault

    Tref->Current_PSP-- ;
    *(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry ; //PC

    Tref->Current_PSP-- ;
    *(Tref->Current_PSP) = 0xFFFFFFFD ; // LR = 0xFFFFFFFD (EXC_Return)Return to thread with PSP

    for(int j = 0; j < 13 ; j++) //R12 -> R0 = 0
    {
        Tref->Current_PSP-- ;
        *(Tref->Current_PSP) = 0 ;
    }
}

MYRTOS_error_ID MYRTOS_Create_Task(Task_ref* Tref)
{
    MYRTOS_error_ID error = NoError;

    //Create its own PSP Stack
    //Check if Task Stack Size exceeded PSP Stack
    Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator ;
    Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;

    // -               -
    // -  _S_PSP_Task  -
    // -   Task Stack  -
    // -  _E_PSP_Task  -
    // -               -
    // -    _eheap     -
    // -               -

    if(Tref->_E_PSP_Task < (unsigned int)&_eheap)
        return Task_Exceeded_StackSize ;

    //Aligned 8 Bytes Spaces between PSP Tasks
    OS_Control.PSP_Task_Locator = (Tref->_E_PSP_Task - 8) ;

    //Initialize PSP Task Stack
    MYRTOS_Create_TaskStack(Tref);

    //Task State Update -> Suspend
    Tref->TaskState = Suspend ;

    return error;

}
