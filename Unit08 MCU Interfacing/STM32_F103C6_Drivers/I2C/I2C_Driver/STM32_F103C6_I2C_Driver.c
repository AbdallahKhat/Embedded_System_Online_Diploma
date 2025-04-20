/*
 * STM32_F103C6_I2C_Driver.c
 *
 *  Created on: Jun 24, 2023
 *      Author: Abdallah Khater
 */


#include "STM32_F103C6_I2C_Driver.h"


/*
 * ================================================================
 *                        Generic Variables
 * ================================================================
 */

I2C_InitConfig Global_I2C_Config[2];

/*
 * ================================================================
 *                         Generic Macros
 * ================================================================
 */

#define     I2C1_INDEX      0
#define     I2C2_INDEX      1

/*
 * ================================================================
 *                      API Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fn          -MCAL_I2C_Init
 * @brief       -Initializes the I2C according to specified parameters
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -I2C_InitStruct: All I2C Configuration
 * @retval      -none
 * Note         -Supports only I2C Mode, Standard Speed (SM), 7-bit slave address for now.
 *              -SMBus Mode, FM, 10-bit slave address (Not supported yet)
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx,I2C_InitConfig* I2C_InitStruct)
{
    uint16_t tmpreg = 0, freqrange = 0 ;
    uint32_t pclk1 = 8000000;
    uint16_t result = 0;

    //Enable RCC Clock
    if(I2Cx == I2C1)
    {
        Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct;
        RCC_I2C1_CLK_EN();
    }
    else if(I2Cx == I2C2)
    {
        Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct;
        RCC_I2C2_CLK_EN();
    }

    if(I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
    {
        /*----------------------- INIT Timing -----------------------*/
        //---I2C CR2. Bits 5:0 FREQ[5:0]: Peripheral clock frequency
        /* Get I2Cx CR2 Value */
        tmpreg = I2Cx->CR2 ;
        /* Clear frequency FREQ[5:0] bits */
        tmpreg &= ~(I2C_CR2_FREQ_Msk);
        /* Get pclk1 frequency value */
        pclk1 = MCAL_RCC_GetPCLK1Freq();
        /* Set frequency bits depending on pclk1 value */
        freqrange = (uint16_t)(pclk1 / 1000000);

        tmpreg |= freqrange;
        /* write to I2Cx CR2 */
        I2Cx->CR2 = tmpreg;


        //• Configure the clock control registers (I2C_CCR)
        /* Disable the selected I2C Peripheral to configure time */
        I2Cx->CR1 &= ~(I2C_CR1_PE_Msk);

        tmpreg = 0;

        /* Configure speed in standard mode */
        if(I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K || I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K)
        {
            /* Standard mode speed calculations */

            //      Tclk/2 = CRR * Tpclk1
            //      CRR = Tclk / (2 * Tpclk1)
            //      CRR = Fpclk1 / (2 * I2C_ClockFrequency)

            result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));

            tmpreg |= result;

            /* Write to I2C CCR */
            I2Cx->CCR = tmpreg;

            /*---------------------- I2C_TRISE Configuration ----------------------*/
            //For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
            //If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
            //therefore the TRISE[5:0] bits must be programmed with 09h.

            I2Cx->TRISE = freqrange + 1;
        }
        else
        {
            //Fast Speed Mode not supported yet
        }

        /*----------------------- I2Cx CR1 Configuration -----------------------*/

        /* Get the I2Cx CR1 value */
        tmpreg = I2Cx->CR1;

        //SPI ACK Control, General Call Address Detection, I2C Mode (I2C/SMBUS), Stretch mode
        tmpreg |= (uint16_t)(I2C_InitStruct->I2C_ACK_Control | I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->I2C_Mode | I2C_InitStruct->StretchMode);

        /* Write to I2Cx CR1 */
        I2Cx->CR1 = tmpreg;


        /*----------------------- I2Cx OAR1 & I2Cx OAR2 Configuration -----------------------*/
        tmpreg = 0;

        if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD == 1)
        {
            tmpreg = I2C_OAR2_ENDUAL;
            tmpreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos;

            /* Write to I2Cx OAR2 */
            I2Cx->OAR2 = tmpreg;
        }

        tmpreg = 0;
        tmpreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1;
        tmpreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_slave_mode;

        /* Write to I2Cx OAR1 */
        I2Cx->OAR1 = tmpreg;

    }
    else
    {
        //SMBus Mode, Not supported
    }

    //Interrupt Mode (Slave Mode) /* check if P_Slave_Event_CallBack != NULL */
    if(I2C_InitStruct->P_Slave_Event_CallBack != NULL)  //That Enables SLAVE IRQ States Mode
    {
        //Enable IRQ
        I2Cx->CR2 |= (I2C_CR2_ITERREN);
        I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
        I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

        if(I2Cx == I2C1)
        {
            NVIC_IRQ31_I2C1_EV_Enable();
            NVIC_IRQ32_I2C1_ER_Enable();
        }
        else if(I2Cx == I2C2)
        {
            NVIC_IRQ33_I2C2_EV_Enable();
            NVIC_IRQ34_I2C2_ER_Enable();
        }

        I2Cx->SR1 = 0;
        I2Cx->SR2 = 0;
    }


    /* Enable the selected I2C Peripheral */
    I2Cx->CR1 |= I2C_CR1_PE;

}


/**================================================================
 * @Fn          -MCAL_I2C_DeInit
 * @brief       -De-Initializes I2C Module
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @retval      -none
 * Note         -Reset the module by RCC
 */
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx)
{
    if(I2Cx == I2C1)
    {
        NVIC_IRQ31_I2C1_EV_Disable();
        NVIC_IRQ32_I2C1_ER_Disable();
        RCC_I2C1_Reset();
    }
    else if(I2Cx == I2C2)
    {
        NVIC_IRQ33_I2C2_EV_Disable();
        NVIC_IRQ34_I2C2_ER_Disable();
        RCC_I2C2_Reset();
    }
}


/**================================================================
 * @Fn          -MCAL_I2C_GPIO_Set_pins
 * @brief       -Initializes GPIO Pins
 * @param [in]  -I2Cx: where x can be (1..3 depending on device used)
 * @retval      -none
 * Note         -Should enable the corresponding ALT & GPIO in RCC Clock, also called after MCAL_I2C_Init()
 */
void MCAL_I2C_GPIO_Set_pins(I2C_TypeDef* I2Cx)
{
    GPIO_PinConfig_t PinCfg;

    if(I2Cx == I2C1)
    {
        //PB6 : I2C1_SCL
        //PB7 : I2C1_SDA

        //PB6 : I2C1_SCL
        PinCfg.GPIO_PinNumber = GPIO_PIN_6;
        PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
        PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
        MCAL_GPIO_Init(GPIOB, &PinCfg);

        //PB7 : I2C1_SDA
        PinCfg.GPIO_PinNumber = GPIO_PIN_7;
        PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
        PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
        MCAL_GPIO_Init(GPIOB, &PinCfg);

    }

    else if(I2Cx == I2C2)
    {
        //PB10 : I2C2_SCL
        //PB11 : I2C2_SDA

        //PB10 : I2C2_SCL
        PinCfg.GPIO_PinNumber = GPIO_PIN_10;
        PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
        PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
        MCAL_GPIO_Init(GPIOB, &PinCfg);

        //PB11 : I2C2_SDA
        PinCfg.GPIO_PinNumber = GPIO_PIN_11;
        PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
        PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
        MCAL_GPIO_Init(GPIOB, &PinCfg);
    }

}


/**================================================================
 * @Fn          -MCAL_I2C_Master_TX
 * @brief       -Transmits data on I2C
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -devAddr: Slave address to be addressed
 * @param [in]  -dataOut: Buffer to be transmitted on I2C
 * @param [in]  -dataLen: Data Length
 * @param [in]  -Stop: Stop condition (With_Stop /Without_Stop)
 * @param [in]  -Start: Start condition (start / repeated_start)
 * @retval      -none
 * Note         -none
 */
void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start)
{
    int i = 0;

    //todo
    //Support timeout (configure timer working for a specific duration and raise interrupt)
    //timer_interrupt(){ flag = 1 }
    //so any code exist in while (check flag || any polling condition)

    //1. Set the START bit in the I2C_CR1 register to generate a start condition
    I2C_GenerateSTART(I2Cx, ENABLE, start);

    //2. wait for EV5
    //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
    while(!I2C_GetFlagStatus(I2Cx, EV5));

    //3. Send Address by writing to DR register
    I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter);

    //4. wait for EV6
    //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
    while(!I2C_GetFlagStatus(I2Cx, EV6));

    //5.  /* TRA, BUSY, MSL, TXE flags */
    while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

    for(i = 0; i < dataLen ;i++)
    {
        /* Write in the DR register for data to be sent */
        I2Cx->DR = dataOut[i];

        //6. Wait for EV6
        //EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
        while(!I2C_GetFlagStatus(I2Cx, EV8));

    }

    //7. Wait for EV8_2
    //EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
    while(!I2C_GetFlagStatus(I2Cx, EV8_2));

    if(Stop == With_Stop)
    {
        //8. Send stop condition
        I2C_GenerateSTOP(I2Cx, ENABLE);
    }
}


/**================================================================
 * @Fn          -MCAL_I2C_Master_RX
 * @brief       -Receives data on I2C
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -devAddr: Slave address to be addressed
 * @param [in]  -dataOut: Buffer to receive data received on I2C
 * @param [in]  -dataLen: Data Length
 * @param [in]  -Stop: Stop condition (With_Stop /Without_Stop)
 * @param [in]  -Start: Start condition (start / repeated_start)
 * @retval      -none
 * Note         -none
 */
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start)
{
    uint8_t index = (I2Cx == I2C1 ? I2C1_INDEX : I2C2_INDEX) ;

    int i = 0;

    //1. Set the START bit in the I2C_CR1 register to generate a start condition
    I2C_GenerateSTART(I2Cx, ENABLE, Start);

    //2. wait for EV5
    //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
    while(!I2C_GetFlagStatus(I2Cx, EV5));

    //3. Send Address by writing to DR register
    I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Receiver);

    //4. wait for EV6
    //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
    while(!I2C_GetFlagStatus(I2Cx, EV6));

    I2C_AcknowledgeConfig(I2Cx,ENABLE);

    if(dataLen > 1) //Used for more than 1 byte reception
    {
        //read the data until data length becomes zero
        for(i=dataLen; i > 0 ; i--)
        {
            //5. wait until RXNE becomes 1
            while(!I2C_GetFlagStatus(I2Cx, EV7));
            //6. Read data from data register in to buffer
            *dataOut = I2Cx->DR;

            //The Acknowledge disable and Stop condition generation are made just before last byte transfer
            if(i-2 == 0)
            {
                I2C_AcknowledgeConfig(I2Cx,DISABLE);
                if(Stop == With_Stop)
                {
                    //7. Send stop condition
                    I2C_GenerateSTOP(I2Cx, ENABLE);
                }
            }

            //increment the buffer address
            dataOut++;
        }
    }

    if(dataLen <= 1)    //Used for 1 byte reception only
    {
        //The Acknowledge disable and Stop condition generation are made just before last byte transfer
        I2C_AcknowledgeConfig(I2Cx,DISABLE);
        if(Stop == With_Stop)
        {
            //5. Send stop condition
            I2C_GenerateSTOP(I2Cx, ENABLE);
        }

        if(dataLen == 1)
        {
            //6. wait until RXNE becomes 1
            while(!I2C_GetFlagStatus(I2Cx, EV7));
            //7. Read data from data register in to buffer
            *dataOut = I2Cx->DR;
        }
    }

    //re-enable Acknowledging

    if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
    {
        I2C_AcknowledgeConfig(I2Cx,ENABLE);
    }

}


/**================================================================
 * @Fn          -I2C_GenerateSTART
 * @brief       -Generates start condition
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -NewState: Enable or Disable start condition
 * @param [in]  -Start: Start condition (start / repeated_start)
 * @retval      -none
 * Note         -none
 */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx,FunctionalState NewState, Repeated_Start Start)
{
    //Check if start or repeated start
    if(Start != repeated_start)
    {
        //Check if the bus is idle
        while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
    }

    // Bit 8 START: Start generation
    // This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
    // In Master Mode:
    // 0: No Start generation
    // 1: Repeated start generation
    // In Slave mode:
    // 0: No Start generation
    // 1: Start generation when the bus is free

    if(NewState != DISABLE)
    {
        /* Generate a start condition */
        I2Cx->CR1 |= (I2C_CR1_START);
    }
    else
    {
        /* Disable the start condition generation */
        I2Cx->CR1 &= ~(I2C_CR1_START);
    }
}


/**================================================================
 * @Fn          -I2C_GenerateSTOP
 * @brief       -Generates stop condition
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -NewState: Enable or Disable stop condition
 * @retval      -none
 * Note         -none
 */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    // Bit 9 STOP: Stop generation
    // The bit is set and cleared by software, cleared by hardware when a Stop condition is
    // detected, set by hardware when a timeout error is detected.
    // In Master Mode:
    // 0: No Stop generation.
    // 1: Stop generation after the current byte transfer or after the current Start condition is sent.
    // In Slave mode:
    // 0: No Stop generation.
    // 1: Release the SCL and SDA lines after the current byte transfer.

    if(NewState != DISABLE)
    {
        /* Generate a stop condition */
        I2Cx->CR1 |= (I2C_CR1_STOP);
    }
    else
    {
        /* Disable the stop condition generation */
        I2Cx->CR1 &= ~(I2C_CR1_STOP);
    }
}


/**================================================================
 * @Fn          -I2C_AcknowledgeConfig
 * @brief       -Generates stop condition
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -NewState: Enable or Disable acknowledging
 * @retval      -none
 * Note         -none
 */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx,FunctionalState NewState)
{

    // Bit 10 ACK: Acknowledge enable
    // This bit is set and cleared by software and cleared by hardware when PE=0.
    // 0: No acknowledge returned
    // 1: Acknowledge returned after a byte is received (matched address or data)

    if(NewState != DISABLE)
    {
        /* Enable the acknowledgment */
        I2Cx->CR1 |= (I2C_CR1_ACK);
    }
    else
    {
        /* Disable the acknowledgment */
        I2Cx->CR1 &= ~(I2C_CR1_ACK);
    }
}


/**================================================================
 * @Fn          -I2C_GetFlagStatus
 * @brief       -Generate start condition
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -flag: flag to be checked whether SET or RESET
 * @retval      -Status of the flag (SET = 1 / RESET = 0)
 * Note         -none
 */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status flag)
{
    volatile uint32_t dummyRead;
    FlagStatus bitstatus = RESET;
    uint32_t flag1 = 0, flag2 = 0;
    uint32_t lastevent = 0;

    switch(flag)
    {
    case I2C_FLAG_BUSY:
        //Bit 1 BUSY: Bus busy
        //0: No communication on the bus
        //1: Communication ongoing on the bus
        //– Set by hardware on detection of SDA or SCL low
        //– cleared by hardware on detection of a Stop condition.
        //It indicates a communication in progress on the bus. This information is still updated when
        //the interface is disabled (PE=0).
        if((I2Cx->SR2) & (I2C_SR2_BUSY))
            bitstatus = SET;
        else
            bitstatus = RESET;
        break;

    case EV5:
        //EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
        //Bit 0 SB: Start bit (Master mode)
        //0: No Start condition
        //1: Start condition generated.
        //– Set when a Start condition generated.
        //– Cleared by software by reading the SR1 register followed by writing the DR register, or by
        //hardware when PE=0
        if((I2Cx->SR1) & (I2C_SR1_SB))
            bitstatus = SET;
        else
            bitstatus = RESET;
        break;

    case EV6:
        //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
        //Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
        if((I2Cx->SR1)&(I2C_SR1_ADDR))
            bitstatus = SET;
        else
            bitstatus = RESET;

        //to clear ADDR field : cleared by reading the SR1 register followed by reading the SR2 register
        dummyRead = I2Cx->SR2;
        break;

    case MASTER_BYTE_TRANSMITTING:
        /* Read the I2Cx status register */
        flag1 = I2Cx->SR1;
        flag2 = I2Cx->SR2;
        flag2 = flag2 << 16;
        /* Get the last event value from the I2C status register */
        lastevent = (flag1 | flag2);
        /* Check to see if the last event contains the I2C event */
        if((lastevent & flag) == (flag))
        {
            /* Success: last event is equal to I2C event */
            bitstatus = SET;
        }
        else
        {
            /* Error: last event is different from I2C event */
            bitstatus = RESET;
        }
        break;

    case EV8_1: //EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
    case EV8:   //EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register

        //  Bit 7 TxE: Data register empty (transmitters)
        //  0: Data register not empty
        //  1: Data register empty
        if((I2Cx->SR1) & (I2C_SR1_TXE))
            bitstatus = SET;
        else
            bitstatus = RESET;
        break;

    case EV8_2:   //EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition

        //  Bit 7 TxE: Data register empty (transmitters)
        //  0: Data register not empty
        //  1: Data register empty
        //  Bit 2 BTF: Byte transfer finished
        //  0: Data byte transfer not done
        //  1: Data byte transfer succeeded
        if(((I2Cx->SR1) & (I2C_SR1_TXE)) && ((I2Cx->SR1) & (I2C_SR1_BTF)))
            bitstatus = SET;
        else
            bitstatus = RESET;
        break;

    case EV7:    //EV7: RxNE=1 cleared by reading the DR register

        //  Bit 6 RxNE: Data register not empty (receivers)
        //  0: Data register empty
        //  1: Data register not empty
        //  – Set when data register is not empty in receiver mode. RxNE is not set during address phase.
        //  – Cleared by software reading or writing the DR register or by hardware when PE=0.
        //  RxNE is not set in case of ARLO event.
        //  Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
        if((I2Cx->SR1) & (I2C_SR1_RXNE))
            bitstatus = SET;
        else
            bitstatus = RESET;
        break;
    }

    return bitstatus;
}


/**================================================================
 * @Fn          -I2C_SendAddress
 * @brief       -Send the address of the slave device to be address on I2C
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -Address: Slave address to be addressed
 * @param [in]  -Direction: Read/Write (I2C_Direction_Transmitter / I2C_Direction_Receiver)
 * @retval      -none
 * Note         -Supports only 7-bit addressing mode (10-Bit Address mode not supported yet)
 */
void I2C_SendAddress(I2C_TypeDef* I2Cx,uint16_t Address, I2C_Direction Direction)
{
    Address = (Address << 1);

    if(Direction != I2C_Direction_Transmitter)
    {
        /* Set the address bit0 for read */
        Address |= (1<<0);
    }
    else
    {
        /* Set the address bit0 for write */
        Address &= ~(1<<0);
    }

    /* Send the address */
    I2Cx->DR = Address;
}


/**================================================================
 * @Fn          -MCAL_I2C_SlaveSendData
 * @brief       -Send data from slave device to master device on I2C
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @param [in]  -data: buffer to be sent from slave to master
 * @retval      -none
 * Note         -Interrupt mechanism for slave not supported yet
 */
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx,uint8_t data)
{
    I2Cx->DR = data;
}


/**================================================================
 * @Fn          -MCAL_I2C_SlaveReceiveData
 * @brief       -Read buffer received from master to slave on I2C
 * @param [in]  -I2Cx: where x can be (1..2 depending on device used)
 * @retval      -buffer received from from master to slave
 * Note         -Interrupt mechanism for slave not supported yet
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx)
{
    return (uint8_t) I2Cx->DR;
}


/*
 * ================================================================
 *                          IRQ Handler
 * ================================================================
 */

void I2C1_EV_IRQHandler(void)                  // I2C1 event interrupt
{
    //Interrupt mechanism for slave not supported yet
}

void I2C1_ER_IRQHandler(void)                  // I2C1 error interrupt
{
    //Interrupt mechanism for slave not supported yet
}

void I2C2_EV_IRQHandler(void)                  // I2C2 event interrupt
{
    //Interrupt mechanism for slave not supported yet
}

void I2C2_ER_IRQHandler(void)                  // I2C2 error interrupt
{
    //Interrupt mechanism for slave not supported yet
}
