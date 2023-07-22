#include "driver.h"
#include <stdint.h>
#include <stdio.h>
void Delay(int nCount)
{
	for(; nCount != 0; nCount--);
}

int getPressureVal(){
	return (GPIOA_IDR & 0xFF);
}

void Set_Alarm_actuator(int i){
	if (i == 0){
		SET_BIT(GPIOA_ODR,15);
	}
	else if (i == 1){
		RESET_BIT(GPIOA_ODR,15);
	}
}

void GPIO_INITIALIZATION (){
    SET_BIT(APB2ENR, 2);
	GPIOA_CRL &= 0xFFFFFFFF;
	GPIOA_CRL |= 0x00000000;
	GPIOA_CRH &= 0x0FFFFFFF;
	GPIOA_CRH |= 0x22222222;

}
