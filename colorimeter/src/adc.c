/*
 * adc.c
 *
 *  Created on: Apr 17, 2017
 *      Author: Nick
 */

#include"adc.h"
#include<stm32f0xx.h>

void adcInit(){
	ADC_InitTypeDef adc;
	GPIO_InitTypeDef gpio;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO; //I don't know what this is
	adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ScanDirection = ADC_ScanDirection_Upward; //I think this is the one I want
	ADC_Init(ADC1, &adc);

	ADC_ChannelConfig(ADC1, ADC_Channel_7, ADC_SampleTime_13_5Cycles);
	ADC_Cmd(ADC1, ENABLE);


	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Pin = GPIO_Pin_7;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &gpio);
}



