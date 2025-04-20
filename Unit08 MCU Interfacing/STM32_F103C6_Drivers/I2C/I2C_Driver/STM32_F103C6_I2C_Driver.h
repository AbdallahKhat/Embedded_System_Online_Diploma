/*
 * STM32_F103C6_I2C_Driver.h
 *
 *  Created on: Jun 24, 2023
 *      Author: Abdallah Khater
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"


//-----------------------------
//User structures
//-----------------------------

//Slave address structure
struct S_I2C_Slave_Device_Address
{
    uint16_t    Enable_Dual_ADD;            //1-Enable    0-Disable

    uint16_t    Primary_slave_address;      //Primary Slave address

    uint16_t    Secondary_slave_address;    //Secondary Slave address

    uint32_t    I2C_Addressing_slave_mode;  //Specifies the Addressing slave mode (7-bit/10-bit slave address)
                                            //This parameter must be set based on @ref I2C_Addressing_slave_define
};

//Slave state enum
typedef enum
{
    I2C_EV_Stop,
    I2C_Error_AF,
    I2C_EV_ADDR_Matched,
    I2C_EV_DATA_REQ,        //the APP layer should send the data (I2C_SlaveSendData) in this state
    I2C_EV_DATA_RCV         //the APP layer should read the data (I2C_SlaveReceiveData) in this state
}Slave_State;


//Configuration structure
typedef struct
{
	uint32_t        I2C_ClockSpeed;         //Specifies the clock frequency
	                                        //This parameter must be set based on @ref I2C_SCLK_define


	uint32_t        StretchMode;            //Specifies whether to enable/disable clock stretching in slave mode
	                                        //This parameter must be set based on @ref I2C_StretchMode_define


	uint32_t        I2C_Mode;               //Specifies the I2C Mode (I2C mode / SMBus mode)
	                                        //This parameter must be set based on @ref I2C_Mode_define


	struct S_I2C_Slave_Device_Address I2C_Slave_Address;
	                                        //SPecifies (dual slave add. EN/DIS),(Primary & Secondary slave add.),(7-bit/10-bit slave address)


	uint32_t        I2C_ACK_Control;        //Enables or disables the acknowledgment
	                                        //This parameter must be set based on @ref I2C_ACK_define


	uint32_t        General_Call_Address_Detection;
	                                        //Enables or disables General call
	                                        //This parameter must be set based on @ref I2C_ENGC_define


	void(* P_Slave_Event_CallBack)(Slave_State state);
	                                        //set the C function() which will be called once IRQ happens
}I2C_InitConfig;


//-------------------------------
//====== References Macros ======
//-------------------------------

//@ref I2C_SCLK_define
//– Standard Speed (up to 100 kHz)
//– Fast Speed (up to 400 kHz)
//• To configure the clock before enabling the peripheral
//-- I2C CR2. Bits 5:0 FREQ[5:0]: Peripheral clock frequency
//• Configure the clock control registers
//               SM or FM
//SM:      T_high = CCR * TPCLK1
//• Configure the rise time register I2C_TRISE
//----
#define I2C_SCLK_SM_50K            (50000U)
#define I2C_SCLK_SM_100K           (100000U)
#define I2C_SCLK_FM_200K           (200000U)  //Fast Mode Not Supported yet
#define I2C_SCLK_FM_400K           (400000U)  //Fast Mode Not Supported yet


//@ref I2C_StretchMode_define
//I2C CR1.
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_StretchMode_enable     (0)
#define I2C_StretchMode_disable    (I2C_CR1_NOSTRETCH)


//@ref I2C_Mode_define
//I2C CR1.
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C               (0)
#define I2C_Mode_SMBus             (I2C_CR1_SMBUS)


//@ref I2C_Addressing_slave_define
//I2C OAR1.
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_slave_7Bit  (0)
#define I2C_Addressing_slave_10Bit (uint16_t)(1<<15)


//@ref I2C_ACK_define
//I2C CR1.
//Bit 10 ACK: Acknowledge enable
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable             (I2C_CR1_ACK)
#define I2C_ACK_Disable            (0)


//@ref I2C_ENGC_define
//I2C CR1.
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_ENGC_Enable            (I2C_CR1_ENGC)
#define I2C_ENGC_Disable           (0)

/* ============================================== */

typedef enum
{
    With_Stop,
    Without_Stop
}Stop_Condition;

typedef enum
{
    start,
    repeated_start
}Repeated_Start;

typedef enum
{
    DISABLE,
    ENABLE
}FunctionalState;

typedef enum
{
    RESET,
    SET
}FlagStatus;

typedef enum
{
    I2C_Direction_Transmitter=0,
    I2C_Direction_Receiver=1
}I2C_Direction;


typedef enum
{
    I2C_FLAG_BUSY=0,
    EV5,    //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
    EV6,    //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
    EV8,    //EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
    EV8_1,  //EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
    EV8_2,  //EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
    EV7,    //EV7: RxNE=1 cleared by reading the DR register
    MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080)  /* TRA, BUSY, MSL, TXE flags */

}Status;

/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

void MCAL_I2C_Init(I2C_TypeDef* I2Cx,I2C_InitConfig* I2C_InitStruct);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx);

void MCAL_I2C_GPIO_Set_pins(I2C_TypeDef* I2Cx);


//Master Polling Mechanism
void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);


//Slave Interrupt Mechanism
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx,uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx);


//Generic APIs
void I2C_GenerateSTART(I2C_TypeDef* I2Cx,FunctionalState NewState, Repeated_Start Start);

void I2C_GenerateSTOP(I2C_TypeDef* I2Cx,FunctionalState NewState);

void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx,FunctionalState NewState);

FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status flag);

void I2C_SendAddress(I2C_TypeDef* I2Cx,uint16_t Address, I2C_Direction Direction);











#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
