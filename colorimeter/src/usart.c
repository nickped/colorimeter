/*
 * usart.c
 *
 *  Created on: Apr 12, 2017
 *      Author: Nick
 */

#include <stm32f0xx.h>
#include "usart.h"

void uart1Init(){
	USART_InitTypeDef uart;
	GPIO_InitTypeDef gpio;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	USART_StructInit(&uart);
	USART_Init(USART1, &uart);
	USART_Cmd(USART1, ENABLE);

	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &gpio);

	//Enable receiveing interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void uart1Send(char *buffer, uint32_t count){
	while (count--){
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, (uint16_t) *buffer++);
	}
}

