/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Jun 26, 2023
 *      Author: Abdallah Khater
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_


#include "STM32_F103C6_I2C_Driver.h"

// E2PROM is an I2C SLAVE
// Idle Mode: device is in high impedance state and wait for data.
// Master Transmitter Mode: the device transmits data to a slave receiver.
// Master Receiver Mode: the device receives data from a slave transmitter.

#define EEPROM_SLAVE_ADDRESS    0x2A

//----------------APIS----------------

void eeprom_init(void);
uint8_t eeprom_write_Nbytes(uint32_t Memory_address,uint8_t* bytes,uint8_t Data_Length);
uint8_t eeprom_read_Nbytes(uint32_t Memory_address,uint8_t* dataOut,uint8_t dataLen);




#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
