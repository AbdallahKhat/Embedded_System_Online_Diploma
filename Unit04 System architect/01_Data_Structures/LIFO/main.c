/*
 * main.c
 *
 *  Created on: Feb 1, 2023
 *      Author: abdal
 */

#include "lifo.h"


int main()
{
	int i , temp;

	LIFO_Buf_t uart_lifo , I2C_lifo;
	//static allocation
	LIFO_init(&uart_lifo, buffer1 ,5);
	//dynamic allocation
	element_type* buffer2 = (element_type*)malloc(5 * sizeof(element_type));
	LIFO_init(&I2C_lifo, buffer2 ,5);

	for(i = 0 ; i < 5 ; i++)
	{
		if ( LIFO_Add_item(&uart_lifo,i) == LIFO_no_error )
			printf("UART_LIFO add : %d \n",i);
	}
	for(i = 0 ; i < 5 ; i++)
	{
		if ( LIFO_get_item(&uart_lifo,&temp) == LIFO_no_error )
			printf("UART_LIFO get : %d \n",temp);
	}
	return 0;
}
