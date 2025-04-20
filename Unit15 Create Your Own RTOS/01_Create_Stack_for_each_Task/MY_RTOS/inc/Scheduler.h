/*
 * Scheduler.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Abdallah Khater
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "CortexMX_OS_Porting.h"

typedef enum{
    NoError,
    Ready_Queue_init_error,
    Task_Exceeded_StackSize,

}MYRTOS_error_ID;

typedef struct{
    unsigned int Stack_Size ;
    unsigned char Priority ;
    void (*p_TaskEntry)(void) ; //Pointer to Task C Function
    unsigned char AutoStart ;
    unsigned int _S_PSP_Task ;  // Not entered by user
    unsigned int _E_PSP_Task ;  // Not entered by user
    unsigned int* Current_PSP ; // Not entered by user
    char TaskName[30] ;
    enum{
        Suspend,
        Running,
        Waiting,
        Ready
    }TaskState ;                // Not entered by user
    struct{
        enum{
            Enable,
            Disable
        }Blocking ;
        unsigned int Ticks_Count ;
    }TimingWaiting ;
}Task_ref;

//APIs
MYRTOS_error_ID MYRTOS_Init();
MYRTOS_error_ID MYRTOS_Create_Task(Task_ref* Tref);

#endif /* INC_SCHEDULER_H_ */
