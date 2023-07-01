/*
 * Timer.c
 *
 * Created: 6/30/2023 7:04:48 PM
 *  Author: Abdallah Khater
 */ 

/*
 * ================================================================
 *                             Includes                            
 * ================================================================
 */

#include "Timer.h"

/*
 * ================================================================
 *                   Global and Extern Variables                   
 * ================================================================
 */
PTR_VoidFunVoid_t Callback_OVF;
PTR_VoidFunVoid_t Callback_CM;
uint8_t u8_TOVNumber;
ST_TIMER0Configs_t* TIMER0_Configurations;

/*
 * ================================================================
 *                      API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn          -TIMER0_Init
 * @brief       -Initializes Timer0 according to specified parameters
 * @param [in]  -configurations: Timer0 configurations
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_Init(ST_TIMER0Configs_t* configurations)
{
    E_STATUS_t u8_Retval = E_NOK;
    if(NULL_PTR == configurations)
    {
        u8_Retval = E_NOK;
    }
    else
    {
        TIMER0_Configurations = configurations;
        if((NORMAL == TIMER0_Configurations->Mode) || (CTC == TIMER0_Configurations->Mode))
        {
            TCCR0 |= TIMER0_Configurations->Mode;
            u8_Retval = E_OK;
        }
        else
        {
            u8_Retval = E_NOK;
        }
        
        if((NO_CLK_SRC <= TIMER0_Configurations->CLK) && (EXT_CLK_RISING >= TIMER0_Configurations->CLK))
        {
            TCCR0 |= TIMER0_Configurations->CLK;
            u8_Retval = E_OK;
        }
        else
        {
            u8_Retval = E_NOK;
        }

        if((OCIE_DISABLE == TIMER0_Configurations->OCM_Interrupt) || (OCIE_ENABLE == TIMER0_Configurations->OCM_Interrupt))
        {
            TIMSK |= TIMER0_Configurations->OCM_Interrupt;
            u8_Retval = E_OK;
        }
        else
        {
            u8_Retval = E_NOK;
        }

        if((TOIE_DISABLE == TIMER0_Configurations->OVF_Interrupt) || (TOIE_ENABLE == TIMER0_Configurations->OVF_Interrupt))
        {
            TIMSK |= TIMER0_Configurations->OVF_Interrupt;
            u8_Retval = E_OK;
        }
        else
        {
            u8_Retval = E_NOK;
        }
    }

    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_Stop
 * @brief       -select the clock source to No clock source (Timer/Counter stopped).
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_Stop(void)
{
    E_STATUS_t u8_Retval = E_OK;
    RESET_BIT(TCCR0,CS00);
    RESET_BIT(TCCR0,CS01);
    RESET_BIT(TCCR0,CS02);

    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_GetCompareValue
 * @brief       -Get the Compare Value from the OCR0 register
 * @param [in]  -pu8_Ticks: pointer to store Compare Value from OCR0 register
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_GetCompareValue(ptr_uint8_t pu8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    *pu8_Ticks = OCR0;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_SetCompareValue
 * @brief       -Set the Compare Value in the OCR0 register
 * @param [in]  -u8_Ticks: Variable to set Compare Value in OCR0 register
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_SetCompareValue(uint8_t u8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    OCR0 = u8_Ticks;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_GetCounterValue
 * @brief       -Get the Counter Value from the TCNT0 register
 * @param [in]  -pu8_Ticks: pointer to store Counter Value from TCNT0 register
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_GetCounterValue(ptr_uint8_t pu8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    *pu8_Ticks = TCNT0;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_SetCounterValue
 * @brief       -Set the Counter Value in the TCNT0 register
 * @param [in]  -u8_Ticks: Variable to set Counter Value in TCNT0 register
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_SetCounterValue(uint8_t u8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    TCNT0 = u8_Ticks;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_GetOverflowValue
 * @brief       -Get the Overflow Value from global variable u8_TOVNumber
 * @param [in]  -pu8_Ticks: pointer to store Overflow Value from global variable u8_TOVNumber
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_GetOverflowValue(ptr_uint8_t pu8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    *pu8_Ticks = u8_TOVNumber;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_SetCounterValue
 * @brief       -Set the Overflow Value in global variable u8_TOVNumber
 * @param [in]  -u8_Ticks: Variable to set Overflow Value in global variable u8_TOVNumber
 * @retval      -Status of Function (E_OK/E_NOK)
 * Note         -none
 */
E_STATUS_t TIMER0_SetOverflowValue(uint8_t u8_Ticks)
{
    E_STATUS_t u8_Retval = E_OK;
    u8_TOVNumber = u8_Ticks;
    return u8_Retval;
}


/**================================================================
 * @Fn          -TIMER0_SetCallback_Overflow_Interrupt
 * @brief       -Set the address of callback function to be called in overflow interrupt ISR
 * @param [in]  -callback: pointer to void function return void
 * @retval      -none
 * Note         -none
 */
void TIMER0_SetCallback_Overflow_Interrupt(PTR_VoidFunVoid_t callback)
{
    Callback_OVF = callback;
}


/**================================================================
 * @Fn          -TIMER0_SetCallback_CompareMatch_Interrupt
 * @brief       -Set the address of callback function to be called in Compare Match Interrupt ISR
 * @param [in]  -callback: pointer to void function return void
 * @retval      -none
 * Note         -none
 */
void TIMER0_SetCallback_CompareMatch_Interrupt(PTR_VoidFunVoid_t callback)
{
    Callback_CM = callback;
}


/*
 * ================================================================
 *                               ISR                               
 * ================================================================
 */

ISR(TIMER0_COMP_vect)
{
    Callback_CM();
}

ISR(TIMER0_OVF_vect)
{
    u8_TOVNumber++;
    Callback_OVF();
}