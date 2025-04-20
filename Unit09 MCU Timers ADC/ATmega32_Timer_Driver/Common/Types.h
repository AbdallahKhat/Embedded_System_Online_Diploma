/*
 * Types.h
 *
 * Created: 6/30/2023 7:02:49 PM
 *  Author: Abdallah Khater
 */ 


#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef unsigned char* ptr_uint8_t;
typedef char* ptr_sint8_t;

typedef void(*PTR_VoidFunVoid_t)(void);
#define NULL_PTR    ((void*)(0))

typedef unsigned char E_STATUS_t;
#define E_OK    (E_STATUS_t)(0)
#define E_NOK   (E_STATUS_t)(1)


#endif /* TYPES_H_ */