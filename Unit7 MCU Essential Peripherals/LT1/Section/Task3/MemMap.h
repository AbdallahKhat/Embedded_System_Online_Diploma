/*
 * MemMap.h
 *
 * Created: 3/1/2023 10:16:15 AM
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

#define PORTD *((volatile unsigned int *)0x32)
#define DDRD *((volatile unsigned char *)0x31)
#define PIND *((volatile unsigned int *)0x30)


#endif /* MEMMAP_H_ */