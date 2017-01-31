/*
 * helper.c
 *
 *  Created on: Jan 24, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"
#include "helper.h"

/* arg1: the number of microseconds
 * output:
 * purpose: delay arg1 microsecond
 * note: arg1 is not the exact number of microseconds delayed. (us = 10 measures 10.1 microseconds)
 */
void delay_us(uint32_t us){
	while(us){
		for(uint32_t i = 0; i < 17; i++) {asm volatile ("nop");  asm volatile ("nop");}
		us--;
	}
}

/* arg1: the number of milliseconds
 * output:
 * purpose: delay arg1 millisecond
 * note: arg1 is not the exact number of milliseconds delayed. (ms = 10 measures 9.988 milliseconds)
 */
void delay_ms(uint32_t ms){
	while(ms){
		delay_us(1169);
		ms--;
	}
}

void ledInit(void){
	GPIO_InitTypeDef led;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //enable clock on portA

	led.GPIO_Mode = GPIO_Mode_OUT;
	led.GPIO_OType = GPIO_OType_PP;
	led.GPIO_Pin = GPIO_Pin_5;
	led.GPIO_PuPd = GPIO_PuPd_DOWN;
	led.GPIO_Speed = GPIO_Speed_Level_3;

	GPIO_Init(GPIOA, &led);
}

void ledToggle(){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5) == Bit_SET) GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	else GPIO_SetBits(GPIOA, GPIO_Pin_5);
}
