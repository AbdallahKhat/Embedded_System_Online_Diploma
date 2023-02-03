/*
 * main.c
 *
 *  Created on: Feb 1, 2023
 *      Author: abdal
 */


#include "fifo.h"

int main()
{
	element_type i , temp;
	FIFO_buf_t FIFO_UART;

	if(FIFO_init(&FIFO_UART,uart_buffer,width1) == FIFO_no_error)
		printf("FIFO init.. done\n");

	for(i=0;i<7;i++)
	{
		printf("FIFO enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error)
			printf("\t FIFO enqueue.. done \n");
		else
			printf("\t FIFO enqueue.. failed \n");

	}

	FIFO_print(&FIFO_UART);

	if(FIFO_dequeue(&FIFO_UART,&temp) == FIFO_no_error)
		printf("\t FIFO dequeue (%x) done \n",temp);
	if(FIFO_dequeue(&FIFO_UART,&temp) == FIFO_no_error)
		printf("\t FIFO dequeue (%x) done \n",temp);

	FIFO_print(&FIFO_UART);

	return 0;
}
