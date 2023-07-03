/*
 * ADC.h
 *
 * Created: 7/3/2023 10:01:48 AM
 *  Author: Abdallah Khater
 */ 


#ifndef ADC_H_
#define ADC_H_


/******************************************************************************
*                                  INCLUDES                                   *
*******************************************************************************/

#include <avr/io.h>
#include "Types.h"
#include "Utils.h"

/******************************************************************************
*                                   MACROS                                    *
*******************************************************************************/

#define VoltRef    5000
#define Res        1024

/******************************************************************************
*                                    ENUMS                                    *
*******************************************************************************/

typedef enum
{
	VREF_AREF,
	VRED_AVCC,
	VREF_256
}ADC_Vref_type;


typedef enum
{
	ADC_SCALER_2 = 0,
	ADC_SCALER_4 = 2,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Scaler_type;

typedef enum
{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;


/******************************************************************************
*                                     APIs                                    *
*******************************************************************************/

void ADC_Init(ADC_Vref_type Vref,ADC_Scaler_type Scaler);

uint16_t ADC_Read(ADC_Channel_type Channel);




#endif /* ADC_H_ */