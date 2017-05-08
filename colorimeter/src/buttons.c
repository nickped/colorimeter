/*
 * buttons.c
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"
#include "buttons.h"
#include "usart.h"

//static uint32_t buttonDebounce = 0;

void buttonInit(){
	GPIO_InitTypeDef portC;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	portC.GPIO_Mode = GPIO_Mode_IN;
	portC.GPIO_OType = GPIO_OType_PP;
	portC.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	portC.GPIO_PuPd = GPIO_PuPd_DOWN;
	portC.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &portC);
}

//doesn't debounce. adds delay if buttons are pressed
uint8_t buttonRead(){
	uint8_t currentButtonState =	(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) << 0) |
									(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) << 1) |
									(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) << 2) |
									(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) << 3) |
									(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) << 4) ;

	if(currentButtonState) delay_ms(100);
	return currentButtonState;


/*	buttonDebounce = (buttonDebounce >> 1) | GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
	if(buttonDebounce > 3) buttonDebounce = 0;
	return (buttonDebounce) ? 1 : 0;*/

	//buttonDebounce = (buttonDebounce >> 1) | GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
	/*buttonDebounce = buttonDebounce >> 1;
	buttonDebounce &= ~((1>>BUTTON1) | (1>>BUTTON2) | (1>>BUTTON3) | (1>>BUTTON4) | (1>>BUTTON5));
	buttonDebounce |= 	(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) >> BUTTON1) |
						(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) >> BUTTON2) |
						(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) >> BUTTON3) |
						(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) >> BUTTON4) |
						(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) >> BUTTON5) ;

	return ((buttonDebounce & (0x3F >>BUTTON1)) == (BUTTON_DEBOUNCE_NUM >> BUTTON1) ? 1 : 0);*/

	/*return 	(((buttonDebounce<<BUTTON1) == BUTTON_DEBOUNCE_NUM) ? (1>>BUTTON1) : (0>>BUTTON1)) |
			(((buttonDebounce<<BUTTON2) == BUTTON_DEBOUNCE_NUM) ? (1>>BUTTON2) : (0>>BUTTON2)) |
			(((buttonDebounce<<BUTTON3) == BUTTON_DEBOUNCE_NUM) ? (1>>BUTTON3) : (0>>BUTTON3)) |
			(((buttonDebounce<<BUTTON4) == BUTTON_DEBOUNCE_NUM) ? (1>>BUTTON4) : (0>>BUTTON4)) |
			(((buttonDebounce<<BUTTON5) == BUTTON_DEBOUNCE_NUM) ? (1>>BUTTON5) : (0>>BUTTON5)) ;*/
}
