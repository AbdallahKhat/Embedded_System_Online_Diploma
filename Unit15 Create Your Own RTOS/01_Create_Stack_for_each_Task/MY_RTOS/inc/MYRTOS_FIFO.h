/*
 * MYRTOS_FIFO_H_.h
 *
 *  Created on: Feb 1, 2023
 *      Author: Abdallah Khater
 */

#ifndef MYRTOS_FIFO_H_
#define MYRTOS_FIFO_H_

#include "stdio.h"
#include "stdint.h"
#include "Scheduler.h"

//User Configuration
//select element type ( uint8_t , uint16_t , uint32_t)
#define element_type Task_ref*

typedef struct {
	unsigned int length;
	unsigned int counter;
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

/* FIFO APIs */

FIFO_buf_status FIFO_init(FIFO_buf_t* fifo,element_type* buf,uint32_t length);
FIFO_buf_status FIFO_enqueue(FIFO_buf_t* fifo,element_type item);
FIFO_buf_status FIFO_dequeue(FIFO_buf_t* fifo,element_type* item);
FIFO_buf_status FIFO_IS_FULL(FIFO_buf_t* fifo);
void FIFO_print(FIFO_buf_t* fifo);

#endif /* MYRTOS_FIFO_H_ */
