/*
 * i2c.c
 *
 *  Created on: Jan 19, 2017
 *      Author: Nick
 */

#include "i2c.h"
#include "stm32f0xx.h"

//TODO:test
void i2c1Init(){
	I2C_InitTypeDef i2c;
	GPIO_InitTypeDef i2cGpio;

	//Enabling clock for peripherals
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	//configuring pinB8 and pinB9 for alternative function
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_1);

	//setting i2c settings
	I2C_StructInit(&i2c);
	i2c.I2C_Timing = 0x0070D8FF;
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE); //enabling i2c

	//changing transfer speed
	RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK); //~100kHz
	//RCC_I2CCLKConfig(RCC_I2C1CLK_HSI); //~14kHz

	//turning on auto ack
	I2C_AcknowledgeConfig(I2C1, ENABLE);

	//Setting gpio settings
	i2cGpio.GPIO_Mode = GPIO_Mode_AF;
	i2cGpio.GPIO_OType = GPIO_OType_OD;
	i2cGpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	//i2cGpio.GPIO_PuPd = GPIO_PuPd_NOPULL; ************************************
	i2cGpio.GPIO_PuPd = GPIO_PuPd_UP;


	i2cGpio.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOB, &i2cGpio);
}

//TODO:test
uint32_t i2cWriteData(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t numBytes){
	if(!numBytes) return I2C_ERROR_OKAY;

	//waits for I2Cx bus to be empty
	for(uint32_t timeout = I2C_TIMEOUT; I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY) == SET; timeout--)
		if(!timeout) return I2C_ERROR_TIMEOUT;

	//init transfer
	I2C_TransferHandling(I2Cx, addr, numBytes, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

	uint8_t cnt = 0;
	//transfering bytes
	while(numBytes){
		//waiting till tx buffer is empty
		for(uint32_t timeout = I2C_TIMEOUT; I2C_GetFlagStatus(I2Cx, I2C_FLAG_TXE) == RESET; timeout--)
			if(!timeout) return I2C_ERROR_TIMEOUT;

		I2C_SendData(I2Cx, data[cnt]);

		cnt++;
		numBytes--;
	}

	return I2C_ERROR_OKAY;
}

//TODO: test
uint32_t i2cReadData(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t numBytes){
	if(!numBytes) return I2C_ERROR_OKAY;

	for(uint32_t timeout = I2C_TIMEOUT; I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY) == SET; timeout--)
		if(!timeout) return I2C_ERROR_TIMEOUT;

	//init transfer
	I2C_TransferHandling(I2Cx, addr, numBytes, I2C_SoftEnd_Mode, I2C_Generate_Start_Read);

	uint8_t cnt = 0;
	//transfering bytes
	while(numBytes){
		//waiting till tx buffer is empty
		for(uint32_t timeout = I2C_TIMEOUT; I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE) == RESET; timeout--)
			if(!timeout) return I2C_ERROR_TIMEOUT;

		data[cnt] = I2C_ReceiveData(I2Cx);

		cnt++;
		numBytes--;
	}

	return I2C_ERROR_OKAY;
}
