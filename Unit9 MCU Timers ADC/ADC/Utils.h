/*
 * Utils.h
 *
 * Created: 6/30/2023 6:57:06 PM
 *  Author: Abdallah Khater
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(REG,BIT)       (REG |= (1 << BIT))
#define CLR_BIT(REG,BIT)       (REG &= ~(1 << BIT))
#define TOGGLE_BIT(REG,BIT)    (REG ^= (1 << BIT))
#define READ_BIT(REG,BIT)      ((REG >> BIT) & 0x01)

#endif /* UTILS_H_ */