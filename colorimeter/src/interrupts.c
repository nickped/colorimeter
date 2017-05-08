/*
 * interrupts.c
 *
 *  Created on: May 3, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"


void nvicInit(){
	NVIC_InitTypeDef uartInt;


	//uart interrupt
	uartInt.NVIC_IRQChannel = USART1_IRQn;
	uartInt.NVIC_IRQChannelPriority = 0;
	uartInt.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&uartInt);
}

