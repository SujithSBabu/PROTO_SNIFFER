/*
 * i2c_stm32.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Sujith S Babu
 */

#include "i2c_stm32.h"

USART_RegDef_Struct* pUsart22 = USART2;

/* API to handle I2c initializations  - MCAL */
void i2c_stm32_init()
{
    uint8_t mode = 0;
    uint8_t duty_cycle = 0;
    uint8_t t_rise = 0;
    uint16_t ccr_value = 0;
    uint32_t pclk   =  get_pclk_value()/1000000U;

	/* I2C1 peripheral clock enable */
	I2C1_CLK_EN();

    /* Pointer initialization */
	I2C_RegDef_Struct* pI2C1 = I2C1;

	/* I2C CR2 register initializations */
	pI2C1->I2C_CR2 &= ~(0x3F << 0);
	pI2C1->I2C_CR2 |=  ((pclk & 0x3F) << 0);

	/* I2C  ITBUFEN and  ITEVTEN interrupt enable */
	pI2C1->I2C_CR2 &= ~(1 << 10);
	pI2C1->I2C_CR2 |=  (1 << 10);
	pI2C1->I2C_CR2 &= ~(1 << 9);
	pI2C1->I2C_CR2 |=  (1 << 9);

	/* I2C_OAR1 register initializations */
	/* Interface address configuration */
	//ToDo

	/* I2C_OAR1 Bit 14 configuration */
	pI2C1->I2C_OAR1 |= (1 <<14 );//should always be kept as 1 by the sw.

    /* I2C_CCR register initialization */
	if (mode == 0)
	{
		pI2C1->I2C_CCR &= ~(1 << 15);//SM mode =0,100KHz speed,ORing with zero makes no difference
		ccr_value = (get_pclk_value()/(2*100000));
		pI2C1->I2C_CCR &= ~(0xFFF << 0);
		pI2C1->I2C_CCR |= ((ccr_value & 0xFFF) << 0);
	}
	else if ( mode == 1)
	{
		pI2C1->I2C_CCR &= ~(1 << 15);
		pI2C1->I2C_CCR |=  (1 << 15);//SM mode =1,400KHz speed
		pI2C1->I2C_CCR &= ~(1 << 14);
		if(duty_cycle == 0)
		{
			ccr_value = (get_pclk_value()/ (3*400000));//Tlow= 2*THigh


		}
		else if(duty_cycle == 1)
		{
			ccr_value = (get_pclk_value()/(25*400000));////9*Tlow= 16*THigh
			pI2C1->I2C_CCR |=  (1 << 14);
		}

		pI2C1->I2C_CCR &= ~(0xFFF << 0);
		pI2C1->I2C_CCR |= ((ccr_value & 0xFFF) << 0);

	}

	/* I2C_TRISE register initialization */
	if (mode == 0)
	{
		//SM mode
		t_rise = (get_pclk_value()/1000000U) + 1;
	}
	else if (mode == 1)
	{
		//FM mode
		t_rise = ((get_pclk_value() * 300)/1000000000U) + 1;
	}

	pI2C1->I2C_TRISE = (t_rise & 0x3F);

	/* Peripheral configuration */
	pI2C1->I2C_CR1 &= ~(1 << 0 );
	pI2C1->I2C_CR1 |=  (1 << 0);

	/* I2C CR1 register initializations */
	/* ACK configuration */
	pI2C1->I2C_CR1 &= ~(1 << 10);
	pI2C1->I2C_CR1 |=  (1 << 10);

	/* Disabled I2C Interrupt handling as its not feasible to use to capture sesnor readings */
	//I2C1_irq_enable();
}

/* API to write data from Master to Slave  - MCAL */
void i2c_stm32_master_write_data()
{
    I2C_RegDef_Struct* pI2C = I2C1;

	//1. Generate START condition
    pI2C->I2C_CR1 |= (1 << 8);

    //2. Confirm that START generation is completed by checking the "SB" flag in the SR1 register.
    //NOTE: Until SB is cleared SCL will be stretched(pulled to LOW).
    while(!(pI2C->I2C_SR1 & (1 << 0)));

    //3. Send the SLAVE Address with r/w bit set to w(0) (total 8 bits)
    uint8_t slave_address = 0x68;        // 7-bit MPU6050 address
    slave_address  = slave_address << 1; // shift left to make room for R/W bit
    slave_address  &= ~(1);              // clear bit0 → write mode (R/W = 0)
    pI2C->I2C_DR   = slave_address;      // send address

    //4. Confirm that address phase is completed by checking the Address flag in the SR1 reg.
    while(!(pI2C->I2C_SR1 & 1 << 1));

    //5. Clear the Address flag according to its sw sequence
    //NOTE: Until ADDR bit is cleared SCL will be stretched(pulled to LOW)
    uint32_t dummy_read = pI2C->I2C_SR1;
    dummy_read          = pI2C->I2C_SR2;
    (void)dummy_read;

    //6. Send the data until length becomes zero.
    pI2C->I2C_DR = 0x3B;

    //7. When len becomes zero,wait for TXE=1 and BTF=1 before generting the STOP condition
    // NOTE: TXE=1,BTF=1 ,means that both SR and DR becomes empty and next transmission should begin
    // When BTF=1 SCL will be stretched(pulled to low)
    while(!(pI2C->I2C_SR1 & (1 << 7)));
    while(!(pI2C->I2C_SR1 & (1 << 2)));

    //8. Generate STOP condition and master need not wait for the completion of STOP condition.
    //NOTE: generating STOP,automatically clears BTF
    pI2C->I2C_CR1 |= (1 << 9);
}


/* API to read data from Slave to Master - MCAL */
uint8_t i2c_stm32_master_read_data(uint8_t sensor_addr, uint8_t read_reg_addr)
{

	I2C_RegDef_Struct* pI2C = I2C1;
	uint8_t sensor_data;
	uint8_t slave_address = sensor_addr;
	uint8_t slave_write = 0;
	uint8_t slave_read  = 0;


	//1. Generate START condition
    pI2C->I2C_CR1 |= (1 << 8);

    //2. Confirm that START generation is completed by checking the "SB" flag in the SR1 register.
    //NOTE: Until SB is cleared SCL will be stretched(pulled to LOW).
    while(!(pI2C->I2C_SR1 & (1 << 0)));

    //3. Send the SLAVE Address with r/w bit set to w(0) (total 8 bits)
    // 7-bit MPU6050 address
    slave_write  = slave_address << 1; // shift left to make room for R/W bit
    slave_write  &= ~(1);              // clear bit0 → write mode (R/W = 0)
    pI2C->I2C_DR   = slave_write;      // send address


    //4. Confirm that address phase is completed by checking the Address flag in the SR1 reg.
    while(!(pI2C->I2C_SR1 & (1 << 1)));

    //5. Clear the Address flag according to its sw sequence
    //NOTE: Until ADDR bit is cleared SCL will be stretched(pulled to LOW)
    volatile uint32_t dummy_read = pI2C->I2C_SR1;
    dummy_read          = pI2C->I2C_SR2;
    (void)dummy_read;

    //6.Send register address (PWR_MGMT_1 = 0x6B)
    pI2C->I2C_DR = 0x6B;
    while (!(pI2C->I2C_SR1 & (1 << 7))); // TXE
    while (!(pI2C->I2C_SR1 & (1 << 2))); // BTF

    //7.Send data 0x00 to wake sensor
    pI2C->I2C_DR = 0x00;
    while (!(pI2C->I2C_SR1 & (1 << 7)));
    while (!(pI2C->I2C_SR1 & (1 << 2)));

    //8.STOP condition after wake-up write
    pI2C->I2C_CR1 |= (1 << 9);

    //9.Small delay to ensure wake-up
    for(volatile int i = 0; i < 10000; i++){}


    // ========== READ SENSOR DATA ==========
	//10.START condition
	pI2C->I2C_CR1 |= (1 << 8);
	while (!(pI2C->I2C_SR1 & (1 << 0)));

	//11.Send slave address (write mode)
	pI2C->I2C_DR = slave_write;
	while (!(pI2C->I2C_SR1 & (1 << 1)));
	dummy_read = pI2C->I2C_SR1;
	dummy_read = pI2C->I2C_SR2;

    //12.Send the register address.
    pI2C->I2C_DR = read_reg_addr; //0x3B;

    //13. When len becomes zero,wait for TXE=1 and BTF=1 before generting the STOP condition
    // NOTE: TXE=1,BTF=1 ,means that both SR and DR becomes empty and next transmission should begin
    // When BTF=1 SCL will be stretched(pulled to low)
    while(!(pI2C->I2C_SR1 & (1 << 7)));
    while(!(pI2C->I2C_SR1 & (1 << 2)));

    //14. Generate Repeated START condition
    pI2C->I2C_CR1 |= (1 << 8);

    //15. Confirm that Repeat START generation is completed by checking the "SB" flag in the SR1 register.
    //NOTE: Until SB is cleared SCL will be stretched(pulled to LOW).
    while(!(pI2C->I2C_SR1 & (1 << 0)));

    //16. Send the SLAVE Address with r/w bit set to R(1) (total 8 bits)
    // 7-bit MPU6050 address
    slave_read  = slave_address << 1; // shift left to make room for R/W bit
    slave_read  |= 0x1;              // set bit0 → read mode (R/W = 1)
    pI2C->I2C_DR   = slave_read;      // send address

    //17. Confirm that address phase is completed by checking the Address flag in the SR1 reg.
    while(!(pI2C->I2C_SR1 & (1 << 1)));

    //18. Disable ACK (for single byte read)
    pI2C->I2C_CR1 &= ~(1 << 10);
    (void)pI2C->I2C_SR1;
    (void)pI2C->I2C_SR2;


    //19. Generate STOP condition and master need not wait for the completion of STOP condition.
    //NOTE: generating STOP,automatically clears BTF
    pI2C->I2C_CR1 |= (1 << 9);

    //20. Wait for RXNE flag
    while(!(pI2C->I2C_SR1 & (1 << 6)));

    //21. Read data
    sensor_data = pI2C->I2C_DR;

    return sensor_data;

}

/* API to enable IrQ for I2C1 in ISER0 - MCAL */
void I2C1_irq_enable(void)
{
	NVIC_ISER0 |= (1 << 31);
}

/*API to handle I2C1 event related interrupts - MCAL*/
void I2C1_EV_IRQHandler()
{
	usart_send_string(pUsart22, "I2c1 interrupt");
}
