/*
 * Lifo.c
 *
 *  Created on: Feb 1, 2023
 *      Author: abdal
 */

#include "lifo.h"

LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buf , uint32_t item)
{
	//check if Lifo is valid
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_Null;

	//check if Lifo is full
	if(lifo_buf->length == lifo_buf->count)
		return LIFO_full;

	//add item
	*(lifo_buf->head) = item;
	lifo_buf->head++;
	lifo_buf->count++;
	return LIFO_no_error;

}
LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buf , int* item)
{
	//check if Lifo is valid
	if(!lifo_buf->base || !lifo_buf->head)
		return LIFO_Null;

	//check if Lifo is empty
	if(lifo_buf->count == 0)
		return LIFO_empty;

	//get item
	lifo_buf->head--;
	*item = *(lifo_buf->head);
	lifo_buf->count--;
	return LIFO_no_error;

}
LIFO_status LIFO_init (LIFO_Buf_t* lifo_buf , element_type* buf , uint32_t length)
{
	if(buf == NULL)
		return LIFO_Null;

	lifo_buf->base = buf;
	lifo_buf->head = buf;
	lifo_buf->length = length;
	lifo_buf->count = 0;
	return LIFO_no_error;
}
