/*
 * Keypad_Driver.c
 *
 * Created: 3/7/2023 12:34:56 PM
 *  Author: Abdal
 */ 

#include "Keypad_Driver.h"

static GPIO_PinConfig_t PinCfg ;

int Keypad_R[] = {R0,R1,R2,R3};
int Keypad_C[] = {C0,C1,C2,C3};

void KEYPAD_INIT()
{
	//	DataDir_KEYPARD_PORT &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	//	DataDir_KEYPARD_PORT |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	PinCfg.GPIO_PinNumber = R0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);


	PinCfg.GPIO_PinNumber = R1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = R2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = R3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = C0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = C1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = C2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	PinCfg.GPIO_PinNumber = C3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M ;
	MCAL_GPIO_Init(KEYPAD_PORT,&PinCfg);

	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}

char KEYPAD_GETCHAR()
{
	int i,j;
	for(i = 0; i < 4 ;i++)
	{
		//KEYPAD_PORT |= ((1<<Keypad_C[0]) | (1<<Keypad_C[1]) | (1<<Keypad_C[2]) | (1<<Keypad_C[3]));
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_C[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_C[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_C[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_C[3], GPIO_PIN_SET);

		MCAL_GPIO_WritePin(KEYPAD_PORT, Keypad_C[i], GPIO_PIN_RESET);
		//KEYPAD_PORT &= ~(1<<Keypad_C[i]);

		for(j = 0; j < 4 ;j++)
		{
 			if((MCAL_GPIO_ReadPin(KEYPAD_PORT, Keypad_R[j])) == 0)
			{
				while((MCAL_GPIO_ReadPin(KEYPAD_PORT, Keypad_R[j])) == 0);
				switch(i)
				{
				case 0:
					if(j == 0)	return '7';
					else if (j == 1)	return '4';
					else if (j == 2)	return '1';
					else if (j == 3)	return '!';
					break;
				case (1):
							if (j == 0) return '8';
							else if (j == 1) return '5';
							else if (j == 2) return '2';
							else if (j == 3) return '0';
				break;
				case (2):
							if (j == 0) return '9';
							else if (j == 1) return '6';
							else if (j == 2) return '3';
							else if (j == 3) return '=';
				break;
				case (3):
							if (j == 0) return '/';
							else if (j == 1) return '*';
							else if (j == 2) return '-';
							else if (j == 3) return '+';
				break;
				}
			}
		}
	}
	return 'N';
}
