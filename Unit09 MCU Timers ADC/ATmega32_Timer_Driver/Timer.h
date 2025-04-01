/*
 * Timer.h
 *
 * Created: 6/30/2023 7:04:25 PM
 *  Author: Abdallah Khater
 */ 


#ifndef TIMER_H_
#define TIMER_H_

/******************************************************************************
*                                  INCLUDES                                   *
*******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Types.h"
#include "Utils.h"

/******************************************************************************
*                                    ENUMS                                    *
*******************************************************************************/

typedef enum
{
    NORMAL,
    CTC = 0x08
}TIMER0_MODE_t;

typedef enum
{
    NO_CLK_SRC,
    NO_PRESCALING,
    PRESCALING_CLK8,
    PRESCALING_CLK64,
    PRESCALING_CLK256,
    PRESCALING_CLK1024,
    EXT_CLK_FALLING,
    EXT_CLK_RISING
}TIMER0_CLOCK_t;

typedef enum
{
    OCIE_DISABLE,
    OCIE_ENABLE = 0x02
}OCMIE0_t;

typedef enum
{
    TOIE_DISABLE,
    TOIE_ENABLE = 0x01
}TOVFIE0_t;


/******************************************************************************
*                                    STRUCT                                   *
*******************************************************************************/

typedef struct
{
    TIMER0_MODE_t    Mode;
    TIMER0_CLOCK_t   CLK;
    OCMIE0_t         OCM_Interrupt;
    TOVFIE0_t        OVF_Interrupt;
    
}ST_TIMER0Configs_t;

/******************************************************************************
*                                     APIs                                    *
*******************************************************************************/

E_STATUS_t TIMER0_Init(ST_TIMER0Configs_t* configurations);
E_STATUS_t TIMER0_Stop(void);

E_STATUS_t TIMER0_GetCompareValue(ptr_uint8_t pu8_Ticks);
E_STATUS_t TIMER0_SetCompareValue(uint8_t u8_Ticks);

E_STATUS_t TIMER0_GetCounterValue(ptr_uint8_t pu8_Ticks);
E_STATUS_t TIMER0_SetCounterValue(uint8_t u8_Ticks);

E_STATUS_t TIMER0_GetOverflowValue(ptr_uint8_t pu8_Ticks);
E_STATUS_t TIMER0_SetOverflowValue(uint8_t u8_Ticks);

void TIMER0_SetCallback_Overflow_Interrupt(PTR_VoidFunVoid_t callback);
void TIMER0_SetCallback_CompareMatch_Interrupt(PTR_VoidFunVoid_t callback);


#endif /* TIMER_H_ */