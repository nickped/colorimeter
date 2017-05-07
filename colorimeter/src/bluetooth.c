/*
 * bluetooth.c
 *
 *  Created on: May 3, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"
#include "usart.h"

static const unsigned char btMessege[] = "hello";
void USART1_IRQHandler(){
	volatile char i = USART_ReceiveData(USART1);
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	delay_ms(200);
	uart1Send(btMessege, 5);
}
