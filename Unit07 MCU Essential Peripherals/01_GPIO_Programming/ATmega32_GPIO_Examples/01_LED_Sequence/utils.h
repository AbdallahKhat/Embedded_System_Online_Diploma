/*
 * utils.h
 *
 * Created: 3/1/2023 4:17:01 PM
 *  Author: abdal
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg,bit)	reg |= (1 << bit)
#define ClearBit(reg,bit)	reg &= ~(1 << bit)
#define ToggleBit(reg,bit)	reg ^= (1 << bit)
#define ReadBit(reg,bit)	((reg>>bit) & 1)


#endif /* UTILS_H_ */