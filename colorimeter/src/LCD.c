/*
 * LCD.c
 *
 *  Created on: Mar 9, 2017
 *      Author: Nick
 */

#include "LCD.h"
#include "stm32f0xx.h"
#include "spi.h"
#include "bitMap.h"
#include "helper.h"
#include <string.h>

void lcdInit(){
	GPIO_InitTypeDef portA, portB;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*
	 * DC  -> PA15
	 * RST -> PA8
	 * CE  -> PB10
	 */

	portA.GPIO_Mode = GPIO_Mode_OUT;
	portA.GPIO_OType = GPIO_OType_PP;
	portA.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_15;
	portA.GPIO_PuPd = GPIO_PuPd_NOPULL;
	portA.GPIO_Speed = GPIO_Speed_Level_2;

	portB.GPIO_Mode = GPIO_Mode_OUT;
	portB.GPIO_OType = GPIO_OType_PP;
	portB.GPIO_Pin = GPIO_Pin_10;
	portB.GPIO_PuPd = GPIO_PuPd_NOPULL;
	portB.GPIO_Speed = GPIO_Speed_Level_2;

	GPIO_Init(GPIOA, &portA);
	GPIO_Init(GPIOB, &portB);

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	delay_ms(11);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);

	lcdControl(0b00100001);
	lcdControl(0b10000000); // x placement
	//lcdControl(0b01000010); // y placement
	lcdControl(0b00100000);
	lcdControl(0b00001100);

	lcdClear();
}

void lcdColon(){
	byte2lcd(0x12);
	byte2lcd(0x00);
}

void lcdControl (uint8_t byte){
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	spi1Transfer(byte);
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}

void lcdLine(uint8_t line){
	lcdControl(0x40 | (line & 0x07));
}

void lcdXAxis(uint8_t loc){
	lcdControl(0x80 | ((loc * 4) & 0x7F));
}

void lcdHomeX(){
	lcdControl(0x80);
}

void lcdHomeY(){
	lcdLine(0);
}

void byte2lcd(uint8_t byte){
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);

	spi1Transfer(byte);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}

void lcdClear(){
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);

	for(uint16_t i = 0; i < (6 * 84); i++)
		spi1Transfer(0x00);

	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}

void char2lcd(uint8_t byte){
	for(uint8_t i = 0; i < CHAR_WIDTH; i++)
		byte2lcd(ascii[byte][i]);
	byte2lcd(0x00);
}

void string2lcd(char *str){
	uint8_t length = strlen(str);
	for(uint8_t i = 0; i < length; i++){
		if(str[i] == ' ') space2lcd();
		else if(str[i] == ':') lcdColon();
		else char2lcd(char2bit(str[i]));
	}
}

void arrow2lcd(){
	byte2lcd(0x41);
	byte2lcd(0x22);
	byte2lcd(0x14);
	byte2lcd(0x08);
	byte2lcd(0x00);
}

void space2lcd(){
	byte2lcd(0x00);
	byte2lcd(0x00);
	byte2lcd(0x00);
	byte2lcd(0x00);
	byte2lcd(0x00);
}

void str2lcdEndLine(char *str){
	uint8_t count = strlen(str);

	lcdXAxis(20-count);
	for(uint8_t i = 0; i < count; i++){
		if(str[i] == ' ') space2lcd();
		else char2lcd(char2bit(str[i]));
	}
}
