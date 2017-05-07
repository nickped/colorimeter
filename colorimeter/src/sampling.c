/*
 * sampling.c
 *
 *  Created on: Jan 27, 2017
 *      Author: Nick
 */

#include "sampling.h"
#include "helper.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/*extern uint16_t *samples,
				sampleNum;
extern uint8_t roomNum;*/

/*public functions*/

void sampleInit(){
	GPIO_InitTypeDef portC;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	portC.GPIO_Mode = GPIO_Mode_OUT;
	portC.GPIO_OType = GPIO_OType_PP;
	portC.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	portC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	portC.GPIO_Speed = GPIO_Speed_Level_2;

	GPIO_Init(GPIOC, &portC);

	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_2, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_4, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, 0);

}
//msb is set if sample is taken
uint16_t readSample(uint16_t *samples, uint16_t sampleNum, uint8_t roomNum){
	uint16_t 	red = 0,
				green = 0,
				blue = 0;

	uint16_t 	read = 0;

	char test[20];

	if((redRead() > AMBIANT_LIGHT) || (greenRead() > AMBIANT_LIGHT) || (blueRead() > AMBIANT_LIGHT)) return 0;

	GPIO_WriteBit(GPIOC, GPIO_Pin_2, 0);

	//red
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	delay_us(50);
	red = redRead();

	//green
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
	delay_us(50);
	green = greenRead();

	//blue
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
	delay_us(50);
	blue = blueRead();

	//clean
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);

	if((red > green) && (red > blue)) read |= 1<<1;
	else if((green > red) && (green > blue)) read |= 1<<2;
	else read |= 1<<3;

	read |= 1;
	read |= roomNum<<4;
	//TODO: add randomVar


	//********************************************************************************************
	//TODO: modify circuit board
	//OPAMP to MCU
	//********************************************************************************************
	sprintf(test, "R=%i\n", red);
	uart1Send(test, strlen(test));
	sprintf(test, "G=%i\n", green);
	uart1Send(test, strlen(test));
	sprintf(test, "B=%i\n", blue);
	uart1Send(test, strlen(test));
	samples[sampleNum] = read;
	sampleNum++;

	return read;
}


uint16_t redRead(){
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_4, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, 0);

	ADC_StartOfConversion(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

uint16_t greenRead(){
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_4, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, 0);

	ADC_StartOfConversion(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

uint16_t blueRead(){
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_4, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, 0);

	ADC_StartOfConversion(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
