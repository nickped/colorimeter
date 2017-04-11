/*
 * spi.c
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */
#include "spi.h"
#include "stm32f0xx.h"

//TODO: TEST
void spi1Init(){
	GPIO_InitTypeDef spiGpio;
	SPI_InitTypeDef spi;

	//enable clock for peripherals
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	//configure PA5, PA6, and PA7 for alternative function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CRCPolynomial = 7;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &spi);
	SPI_Cmd(SPI1, ENABLE);

	spiGpio.GPIO_Mode = GPIO_Mode_AF;
	spiGpio.GPIO_OType = GPIO_OType_PP;
	spiGpio.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	spiGpio.GPIO_PuPd = GPIO_PuPd_UP;
	spiGpio.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOB, &spiGpio);
}

//TODO: Test
uint8_t spi1Transfer(uint8_t dataOut){
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	SPI_SendData8(SPI1, dataOut);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	return SPI_ReceiveData8(SPI1);
}
