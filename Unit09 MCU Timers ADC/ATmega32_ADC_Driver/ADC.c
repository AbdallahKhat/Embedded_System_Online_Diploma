/*
 * ADC.c
 *
 * Created: 7/3/2023 10:01:39 AM
 *  Author: Abdallah Khater
 */ 

/*
 * ================================================================
 *                             Includes                            
 * ================================================================
 */

#include "ADC.h"


/*
 * ================================================================
 *                      API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn          -ADC_Init
 * @brief       -Initializes ADC according to specified parameters
 * @param [in]  -Vref: Reference volt to be used
 * @param [in]  -Scaler: determine the division factor between the XTAL frequency and the input clock to the ADC. 
 * @retval      -none
 * Note         -none
 */
void ADC_Init(ADC_Vref_type Vref,ADC_Scaler_type Scaler)
{
	/* Select the voltage reference for the ADC */
	
	switch (Vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VRED_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	 /* Select the division factor between the XTAL frequency and the input clock to the ADC (prescaler) */
	 
	 ADCSRA &= 0XF8;          //Clearing ADC Prescaler Selection bits
	 ADCSRA |= Scaler;       //Setting the Prescaler Selection bits from ADC_Scaler_type
	 
	 
	 /* Enable ADC Peripheral */
	 SET_BIT(ADCSRA,ADEN);
	 
}


/**================================================================
 * @Fn          -ADC_Read
 * @brief       -Reads The ADC Data Register – ADCL and ADCH depending on ADLAR register 
 * @param [in]  -Channel: Selected channel (Supports for now: Single Ended Input)
 * @retval      -Value stored in the data register
 * Note         -none
 */
uint16_t ADC_Read(ADC_Channel_type Channel)
{
	/* Selects which Channel of analog input are connected to the ADC */
	
	ADMUX &= 0XE0;          //Clearing ADC MUX4:0 bits
	ADMUX |= Channel;      //Setting ADC MUX4:0 bits from ADC_Channel_type
	
	
	/* ADC Start Conversion */
	SET_BIT(ADCSRA,ADSC);
	
	
	/* ADSC will read as one as long as a conversion is in progress */
	while(READ_BIT(ADCSRA,ADSC));
	
	/* Return ADC Data Register */
	return ADC;
	
}
