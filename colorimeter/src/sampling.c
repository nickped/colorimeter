/*
 * sampling.c
 *
 *  Created on: Jan 27, 2017
 *      Author: Nick
 */

#include "sampling.h"
#include "helper.h"
#include "usart.h"
#include "LCD.h"
#include "buttons.h"
#include <stdio.h>
#include <string.h>

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
sample_t readSample(sample_t *samples, uint16_t *sampleNum){
	sample_t read;
	read.red = 0;
	read.green = 0;
	read.blue = 0;
	read.room = 0;

	if((redRead() > AMBIANT_LIGHT) || (greenRead() > AMBIANT_LIGHT) || (blueRead() > AMBIANT_LIGHT) || (*sampleNum == SAMPLE_SIZE)) return read;

	GPIO_WriteBit(GPIOC, GPIO_Pin_2, 0);

	//red
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	delay_ms(15);
	read.blue = blueRead();
	//read.red = redRead();
	//clean
	/*GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	delay_ms(15);*/

	//green
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
	delay_ms(15);
	read.green = greenRead();
	//clean
	/*GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	delay_ms(15);*/

	//blue
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 1);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 1);
	delay_ms(15);
	//read.blue = blueRead();
	read.red = redRead();
	//clean
	/*GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);
	delay_ms(15);*/

	//clean
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, 0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, 0);

	read.room = getRoom();
	displaySample(read);


	samples[*sampleNum] = read;
	(*sampleNum)++;

	return read;
}

void showRoom(uint8_t x){
	lcdClear();
	lcdLine(0);
	lcdHomeX();
	string2lcd(roomName[(!x) ? ROOM_NAME_SIZE : x-1]);

	lcdLine(2);
	lcdHomeX();
	arrow2lcd();
	string2lcd(roomName[x]);

	lcdLine(4);
	lcdHomeX();
	string2lcd(roomName[((x+1) > ROOM_NAME_SIZE) ? 0 : x+1]);
}

uint8_t getRoom(){
	uint8_t x = 0;

	showRoom(x);

	while(buttonRead() & BUTTON5);
	delay_us(50);

	for(uint8_t buttonState = 0; !(buttonState & BUTTON5); buttonState = buttonRead()){
		if (buttonState) showRoom(x);

		if(buttonState & BUTTON2){ //down
			x = (x != ROOM_NAME_SIZE) ? ++x : 0;
		}
		else if(buttonState & BUTTON4){ //up
			x = (x) ? x-1 : ROOM_NAME_SIZE;
		}
	}
	return x;
}

void displaySample(sample_t read){
	char str[20];

	lcdClear();

	lcdLine(0);
	lcdHomeX();
	sprintf(str, "RED: %i", read.red);
	string2lcd(str);

	lcdLine(2);
	lcdHomeX();
	sprintf(str, "GREEN: %i", read.green);
	string2lcd(str);

	lcdLine(4);
	lcdHomeX();
	sprintf(str, "BLUE: %i", read.blue);
	string2lcd(str);

	delay_ms(500);


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
