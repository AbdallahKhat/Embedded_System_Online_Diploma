/*
 * Lifo.h
 *
 *  Created on: Feb 1, 2023
 *      Author: abdal
 */

#ifndef LIFO_H_
#define LIFO_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

//type definitions

//User Configuration
//select element type ( uint8_t , uint16_t , uint32_t)

#define element_type uint32_t

//create buffer
#define width1 5
element_type buffer1[width1];

typedef struct {
	uint32_t length	;
	uint32_t count	;
	element_type* base	;
	element_type* head	;
}LIFO_Buf_t;

typedef enum {
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null
}LIFO_status;

//APIs

LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buf , uint32_t item);
LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buf , int32_t* item);
LIFO_status LIFO_init (LIFO_Buf_t* lifo_buf , element_type* buf , uint32_t length);


#endif /* LIFO_H_ */
