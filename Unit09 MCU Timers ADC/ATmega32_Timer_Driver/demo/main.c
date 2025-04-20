/*
 * Timers.c
 *
 * Created: 6/30/2023 6:51:24 PM
 * Author : Abdallah Khater
 */ 

#define F_CPU 8000000UL

#include "Timer.h"

extern uint8_t u8_TOVNumber;

void TIMER_CM_CALLBACK()
{
    PORTA = ~PORTA;
}

int main(void)
{
    DDRA = 0xFF;
    sei();
    TIMER0_SetCallback_CompareMatch_Interrupt(TIMER_CM_CALLBACK);
    ST_TIMER0Configs_t config = {CTC,PRESCALING_CLK8,OCIE_ENABLE,TOIE_DISABLE};
    TIMER0_SetCompareValue(0xF0);
    TIMER0_Init(&config);
    
    while (1) 
    {
    }
}

