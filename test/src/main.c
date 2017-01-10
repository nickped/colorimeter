/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0xx_nucleo.h"

void ledInit(GPIO_InitTypeDef *led){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //enable clock on portA

	led->GPIO_Mode = GPIO_Mode_OUT;
	led->GPIO_OType = GPIO_OType_PP;
	led->GPIO_Pin = GPIO_Pin_5;
	led->GPIO_PuPd = GPIO_PuPd_DOWN;
	led->GPIO_Speed = GPIO_Speed_Level_3;

	GPIO_Init(GPIOA, led);
}


void ledToggle(){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5) == Bit_SET) GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	else GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void usbInit(USART_InitTypeDef *usb){
	GPIO_InitTypeDef usbGpio;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //enable clock for usart2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //enable clock for usart1

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_0);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_0);

	USART_StructInit(usb); //sets the default uart structure
	USART_Init(USART1, usb); //initializes uart
	USART_Cmd(USART1, ENABLE); //enables uart1

	/*USART_StructInit(usb);
	USART_Init(USART2, usb);
	USART_Cmd(USART2, ENABLE);*/


	//GPIO
	usbGpio.GPIO_Mode = GPIO_Mode_AF;
	usbGpio.GPIO_OType = GPIO_OType_PP;
	usbGpio.GPIO_Pin = /*GPIO_Pin_2 | GPIO_Pin_3 |*/ GPIO_Pin_9 | GPIO_Pin_10;
	usbGpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	usbGpio.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &usbGpio);
}

void uart1Putc(uint8_t data){
	//if(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	//else GPIO_SetBits(GPIOA, GPIO_Pin_5);


	//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	USART_SendData(USART1, data);

	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == SET);
}

int main(void){
	SystemInit();

	GPIO_InitTypeDef portA;
	USART_InitTypeDef usb;

	ledInit(&portA);
	usbInit(&usb);

	uint32_t cnt = 0;


	while(1){
		ledToggle();
		if(cnt > 9) cnt = 0;
		uart1Putc('9' - cnt);
		cnt++;
		for(uint32_t i = 0; i < 0x007B8200; i++); //delay ~1s
	}
}
