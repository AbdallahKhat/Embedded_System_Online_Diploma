/*
 * MemMap.h
 *
 * Created: 3/1/2023 4:17:16 PM
 *  Author: abdal
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

#define DDRA *((volatile unsigned char *)0x3A)
#define PORTA *((volatile unsigned int *)0x3B)
#define PINA *((volatile unsigned int *)0x39)

#define PINC *((volatile unsigned char *)0x33)
#define DDRC *((volatile unsigned char *)0x34)
#define PORTC *((volatile unsigned int *)0x35)


#endif /* MEMMAP_H_ */