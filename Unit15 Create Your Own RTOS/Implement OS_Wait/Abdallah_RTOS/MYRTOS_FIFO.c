/*
 * MYRTOS_FIFO.c
 *
 *  Created on: Feb 1, 2023
 *      Author: Abdallah Khater
 */


#include <MYRTOS_FIFO.h>

//FIFO APIs

FIFO_buf_status FIFO_init(FIFO_buf_t* fifo,element_type* buf,uint32_t length)
{
	if(buf == NULL)			//Concerning dynamic allocation
		return FIFO_Null;

	fifo->base = buf ;
	fifo->tail = buf ;
	fifo->head = buf ;
	fifo->length = length ;
	fifo->counter = 0;
	return FIFO_no_error;
}
FIFO_buf_status FIFO_enqueue(FIFO_buf_t* fifo,element_type item)
{
	//check FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	//check FIFO is full
	if(FIFO_IS_FULL(fifo) == FIFO_full)
		return FIFO_full;
	//enqueue
	*(fifo->head) = item ;
	fifo->counter++ ;
	if(fifo->head == (fifo->base + fifo->length))	// Circular FIFO
		fifo->head = fifo->base ;

	else
		fifo->head++ ;


	return FIFO_no_error;



}
FIFO_buf_status FIFO_dequeue(FIFO_buf_t* fifo,element_type* item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	//check FIFO is empty
	if(fifo->counter == 0)
		return FIFO_empty;

	*item = *(fifo->tail);
	fifo->counter--;

	if(fifo->tail == (fifo->base + fifo->length))	// Circular FIFO
		fifo->tail = fifo->base ;

	else
		fifo->tail++ ;

	return FIFO_no_error;

}
FIFO_buf_status FIFO_IS_FULL(FIFO_buf_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	if(fifo->counter == fifo->length)
		return FIFO_full;

	return FIFO_no_error;

}
void FIFO_print(FIFO_buf_t* fifo)
{

//	element_type* temp;
//	int i;
//
//	if(fifo->counter == 0)
//		printf("FIFO is empty\n");
//	else
//	{
//		temp = fifo->tail;
//		printf("\n=========FIFO_PRINT=========\n");
//		for(i=0; i < fifo->counter ; i++)
//            {
//			printf("\t %x \n",*temp);
//            temp++;
//            }
//	}
//	printf("\n============Done============\n");
}
