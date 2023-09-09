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

typedef enum
{
    SVC_ActivateTask,
    SVC_TerminateTask,
    SVC_TaskWaitingTime
}SVC_ID;

FIFO_buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100];
Task_ref MYRTOS_idleTask ;


__attribute ((naked)) void PendSV_Handler()
{
    //====================================
    //Save the context of the current task
    //====================================
    //Get the current task "current PSP from CPU register" as CPU Push xPSR,...,R0
    OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

    //Use this Current_PSP (Pointer) to Store (R4 to R11)
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R4" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R4
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R5" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R5
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R6" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R6
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R7" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R7
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R8" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R8
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R9" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R9
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R10" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R10
    OS_Control.CurrentTask->Current_PSP-- ;
    __asm volatile("MOV %0, R11" : "=r" (*(OS_Control.CurrentTask->Current_PSP))); //Store R11

    //Save the current value of PSP
    //Already saved in Current_PSP

    //====================================
    //Restore the context of the next task
    //====================================
    OS_Control.CurrentTask = OS_Control.NextTask ;
    OS_Control.NextTask = NULL ;

    __asm volatile("MOV R11, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R11
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R10, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R10
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R9, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R9
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R8, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R8
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R7, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R7
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R6, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R6
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R5, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R5
    OS_Control.CurrentTask->Current_PSP++ ;
    __asm volatile("MOV R4, %0" : : "r" (*(OS_Control.CurrentTask->Current_PSP))); //Read R4
    OS_Control.CurrentTask->Current_PSP++ ;

    //Update PSP and exit
    OS_SET_PSP(OS_Control.CurrentTask->Current_PSP) ;

    __asm volatile("BX LR") ;
}

void MYRTOS_Create_MainStack()
{
    OS_Control._S_MSP_Task = (unsigned int)&_estack ;
    OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize ;

    //Aligned 8 Bytes Spaces between Main Task and PSP Tasks
    OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8) ;

    //if(_E_MSP_Task < &_eheap) ERROR: Exceeded the available stack size
}

unsigned char IdleTaskLED ;
void MYRTOS_IdleTask (void)
{
    while(1)
    {
        IdleTaskLED ^= 1 ;
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

    //Update Sch. Table
    OS_Control.OSTasks[OS_Control.NoOfActiveTasks] = Tref ;
    OS_Control.NoOfActiveTasks++;

    //Task State Update -> Suspend
    Tref->TaskState = Suspend ;

    return error;

}

//Handler Mode
void BubbleSort()
{
    unsigned int i, j ,n;
    Task_ref* Temp ;
    n = OS_Control.NoOfActiveTasks ;
    for(i = 0; i < n - 1 ; i++)
    {
        //Last i elements are already in place
        for(j = 0; j < n - i - 1 ; j++)
            if(OS_Control.OSTasks[j]->Priority > OS_Control.OSTasks[j + 1]->Priority)
            {
                Temp = OS_Control.OSTasks[j] ;
                OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1] ;
                OS_Control.OSTasks[j + 1] = Temp ;
            }
    }

}

//Handler Mode
void MYRTOS_Update_Scheduler_Tables()
{
    Task_ref* temp = NULL;
    Task_ref* Ptask,* Pnexttask;
    int i = 0;

    //1- Bubble Sort SchTable OS_Control->OSTasks[100] (Priority High then Low)
    BubbleSort();
    //2- Free Ready Queue
    while(FIFO_dequeue(&Ready_QUEUE, &temp /*pointer to pointer*/) != FIFO_empty);

    //3- Update Ready Queue
    while(i < OS_Control.NoOfActiveTasks)
    {
        Ptask = OS_Control.OSTasks[i] ;
        Pnexttask = OS_Control.OSTasks[i+ 1] ;

        if(Ptask->TaskState != Suspend)
        {
            //In case we reached the end of available OS Tasks
            if(Pnexttask->TaskState == Suspend)
            {
                FIFO_enqueue(&Ready_QUEUE, Ptask) ;
                Ptask->TaskState = Ready ;
                break;
            }

            //If Ptask->Priority < Pnexttask->Priority then (Lower number means higher priority)
            if(Ptask->Priority < Pnexttask->Priority)
            {
                FIFO_enqueue(&Ready_QUEUE, Ptask) ;
                Ptask->TaskState = Ready ;
                break;
            }

            else if(Ptask->Priority == Pnexttask->Priority)
            {
                //If Ptask->Priority == Pnexttask->Priority then
                //Push Ptask to Ready state
                //Make Ptask = Pnexttask and Pnexttask++
                FIFO_enqueue(&Ready_QUEUE, Ptask) ;
                Ptask->TaskState = Ready ;
            }
            else if(Ptask->Priority > Pnexttask->Priority)
            {
                //Not allowed to happen, as the tasks have already been reordered by bubble sort
                break;
            }
        }

        i++ ;
    }
}

//Handler Mode
void Decide_whatNext()
{
    //if Ready Queue is empty && OS_Control.CurrentTask != Suspend
    if(Ready_QUEUE.counter == 0 && OS_Control.CurrentTask->TaskState != Suspend)
    {
        OS_Control.CurrentTask->TaskState = Running ;
        //add the current task again (Round Robin)
        FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask) ;
        OS_Control.NextTask = OS_Control.CurrentTask ;
    }
    else
    {
        FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask) ;
        OS_Control.NextTask->TaskState = Running ;
        //Update Ready Queue (to keep round robin Algo. happening)
        if((OS_Control.CurrentTask->Priority == OS_Control.NextTask->Priority)&&(OS_Control.CurrentTask->TaskState != Suspend))
        {
            FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask) ;
            OS_Control.CurrentTask->TaskState = Ready ;
        }
    }
}

//Handler Mode
void OS_SVC(int* stackFrame)
{
    //OS_SVC stack -> R0 -> argument 0 = StackFramePointer
    //OS_SVC stack : R0,R1,R2,R3,R12,LR,PC,xPSR

    unsigned char SVC_number  ;

    SVC_number = ((unsigned char *)stackFrame[6])[-2];

    switch(SVC_number)
    {
    case SVC_ActivateTask:      //Activate Task
    case SVC_TerminateTask:     //Terminate Task
        //Update Sch. Table
        MYRTOS_Update_Scheduler_Tables();
        //OS is in running state
        if(OS_Control.OSmodeID == OSrunning)
        {
            if(strcmp(OS_Control.CurrentTask->TaskName,"idleTask") != 0)
            {
                //Decide what's next
                Decide_whatNext();

                //Trigger OS_PendSV (Switching context save/restore)
                trigger_OS_PendSV();
            }
        }

        break;

    case SVC_TaskWaitingTime:   //Task waiting

        break;

    }

}

//Thread Mode
void MYRTOS_OS_SVC_Set(SVC_ID ID)
{
    switch(ID)
    {
    case SVC_ActivateTask:
        __asm("svc #0x00");
        break;
    case SVC_TerminateTask:
        __asm("svc #0x01");
        break;
    case SVC_TaskWaitingTime:
        __asm("svc #0x02");
        break;

    }
}

void MYRTOS_ActivateTask(Task_ref* Tref)
{
    Tref->TaskState = Waiting ;

    MYRTOS_OS_SVC_Set(SVC_ActivateTask);

}

void MYRTOS_TerminateTask(Task_ref* Tref)
{
    Tref->TaskState = Suspend ;
}

void MYRTOS_STARTOS(void)
{
    OS_Control.OSmodeID = OSrunning ;
    //Set Default "Current Task == idleTask"
    OS_Control.CurrentTask = &MYRTOS_idleTask ;
    //Activate idleTask
    MYRTOS_ActivateTask(&MYRTOS_idleTask) ;
    //Start Ticker
    Start_Ticker(); //1ms

    OS_SET_PSP(OS_Control.CurrentTask->Current_PSP) ;
    //Switch Thread Mode SP from MSP to PSP
    OS_SWITCH_SP_to_PSP;
    OS_SWITCH_to_unprivileged;
    MYRTOS_idleTask.p_TaskEntry();
}
