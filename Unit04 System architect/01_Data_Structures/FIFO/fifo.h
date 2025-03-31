/*
 * fifo.h
 *
 *  Created on: Feb 1, 2023
 *      Author: abdal
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"
//User Configuration
//select element type ( uint8_t , uint16_t , uint32_t)

#define element_type uint8_t

//create buffer1
#define width1 5
element_type uart_buffer[width1];

typedef struct {
	unsigned int length;
	unsigned int count;
	element_type* head;
	element_type* tail;
	element_type* base;
}FIFO_buf_t;

typedef enum {
	FIFO_no_error,
	FIFO_empty,
	FIFO_full,
	FIFO_Null
}FIFO_buf_status;

//FIFO APIs

FIFO_buf_status FIFO_init(FIFO_buf_t* fifo,element_type* buf,uint32_t length);
FIFO_buf_status FIFO_enqueue(FIFO_buf_t* fifo,element_type item);
FIFO_buf_status FIFO_dequeue(FIFO_buf_t* fifo,element_type* item);
FIFO_buf_status FIFO_IS_FULL(FIFO_buf_t* fifo);
void FIFO_print(FIFO_buf_t* fifo);

#endif /* FIFO_H_ */
