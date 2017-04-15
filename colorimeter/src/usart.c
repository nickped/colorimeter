/*
 * usart.c
 *
 *  Created on: Apr 12, 2017
 *      Author: Nick
 */

#include <stm32f0xx.h>
#include "usart.h"

void uart4Init(){
	USART_InitTypeDef uart;
	GPIO_InitTypeDef gpio;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART4, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	USART_StructInit(&uart);
	USART_Init(GPIOC, &uart);
	USART_Cmd(GPIOC, ENABLE);

	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOC, &gpio);
}
