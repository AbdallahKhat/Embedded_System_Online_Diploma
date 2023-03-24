/*
 * Keypad_Driver.h
 *
 * Created: 3/7/2023 12:35:17 PM
 *  Author: Abdal
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_


#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32F103x6.h"

extern GPIO_PinConfig_t PinCfg ;


#define KEYPAD_PORT GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

void KEYPAD_INIT();
char KEYPAD_GETCHAR();

#endif /* KEYPAD_DRIVER_H_ */
