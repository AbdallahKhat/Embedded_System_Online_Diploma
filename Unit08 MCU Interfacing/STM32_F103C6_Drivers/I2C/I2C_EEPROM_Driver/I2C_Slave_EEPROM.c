/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Jun 26, 2023
 *      Author: Abdallah Khater
 */


#include "I2C_Slave_EEPROM.h"


/*
 * ================================================================
 *                      API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn          -eeprom_init
 * @brief       -Initializes the EEPROM device
 * @retval      -none
 * Note         -none
 */
void eeprom_init(void)
{
    //==================I2C INIT==================
    //  PB6 :   I2C1_SCL
    //  PB7 :   I2C1_SDA

    I2C_InitConfig I2C1CFG ;

    //I2C Controller act as a Master
    I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable;
    I2C1CFG.I2C_ACK_Control = I2C_ACK_Enable;
    I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100K;
    I2C1CFG.I2C_Mode = I2C_Mode_I2C;
    I2C1CFG.P_Slave_Event_CallBack = NULL;
    I2C1CFG.StretchMode = I2C_StretchMode_enable;

    MCAL_I2C_GPIO_Set_pins(I2C1);

    MCAL_I2C_Init(I2C1, &I2C1CFG);

}


/**================================================================
 * @Fn          -eeprom_write_Nbytes
 * @brief       -Write buffer to EEPROM
 * @param [in]  -Memory_address: Memory address in EEPROM, where buffer will be stored
 * @param [in]  -bytes: buffer to be transmitted to EEPROM
 * @param [in]  -Data_Length: Data length of buffer to be transmitted to EEPROM
 * @retval      -return 0
 * Note         -none
 */
uint8_t eeprom_write_Nbytes(uint32_t Memory_address,uint8_t* bytes,uint8_t Data_Length)
{
    uint8_t i = 0;
    //MISRA C++ 2008, 18-4-1 - Dynamic heap memory allocation shall not be used
    //violate MISRA Rule
    //(unsigned char*)malloc(Data_Length+2);

    uint8_t buffer[256];
    buffer[0] = (uint8_t)(Memory_address >> 8);       //Upper byte Memory address
    buffer[1] = (uint8_t)(Memory_address & 0x00FF);  //Lower byte Memory address
    for(i = 0; i < Data_Length ; i++)
        buffer[i+2] = bytes[i];

    MCAL_I2C_Master_TX(I2C1, EEPROM_SLAVE_ADDRESS, buffer, (Data_Length + 2), With_Stop, start);

    return 0;
}


/**================================================================
 * @Fn          -eeprom_read_Nbytes
 * @brief       -Read buffer from EEPROM
 * @param [in]  -Memory_address: Memory address in EEPROM, where buffer will be read
 * @param [in]  -dataOut: buffer to receive data from EEPROM
 * @param [in]  -Data_Length: Data length of buffer to be received from EEPROM
 * @retval      -return 0
 * Note         -none
 */
uint8_t eeprom_read_Nbytes(uint32_t Memory_address,uint8_t* dataOut,uint8_t dataLen)
{
    uint8_t buffer[2];
    buffer[0] = (uint8_t)(Memory_address >> 8);       //Upper byte Memory address
    buffer[1] = (uint8_t)(Memory_address & 0x00FF);  //Lower byte Memory address


    MCAL_I2C_Master_TX(I2C1, EEPROM_SLAVE_ADDRESS, buffer, 2, Without_Stop, start); //Write Address Only

    MCAL_I2C_Master_RX(I2C1, EEPROM_SLAVE_ADDRESS, dataOut, dataLen, With_Stop, repeated_start); //Read Data

    return 0;
}
