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

#include "modes.h"
#include "i2c.h"
#include "spi.h"
#include "helper.h"
#include "LCD.h"
#include "bitMap.h"

static settingsTypeDef setting;

void colorimeterInit(){
	SystemInit();
	i2c1Init();
	spi1Init();
	ledInit();
	lcdInit();

	GPIO_InitTypeDef portC;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	portC.GPIO_Mode = GPIO_Mode_IN;
	portC.GPIO_OType = GPIO_OType_PP;
	portC.GPIO_Pin = GPIO_Pin_12;
	portC.GPIO_PuPd = GPIO_PuPd_DOWN;
	portC.GPIO_Speed = GPIO_Speed_Level_2;

	GPIO_Init(GPIOC, &portC);

	setting.sleep = ON;
	setting.sleepTime = SETTINGS_SLEEPTIME_10min;
	setting.blueTooth = OFF;
}

void displayPrint(){
	static uint8_t testDisplayCnt = 0;
	lcdClear();
	lcdHomeX();
	lcdHomeY();

	char2lcd(ASCII_DEF_R);
	lcdColon();
	lcdXAxis(2);
	char2lcd((2*testDisplayCnt) % 10);
	char2lcd((3*testDisplayCnt) % 10);
	char2lcd((3*testDisplayCnt) % 10);

	lcdLine(2);
	lcdHomeX();
	char2lcd(ASCII_DEF_G);
	lcdColon();
	lcdXAxis(2);
	char2lcd((2*testDisplayCnt) % 10);
	char2lcd((1*testDisplayCnt) % 10);
	char2lcd((3*testDisplayCnt) % 10);

	lcdLine(4);
	lcdHomeX();
	char2lcd(ASCII_DEF_B);
	lcdColon();
	lcdXAxis(2);
	char2lcd((1*testDisplayCnt) % 10);
	char2lcd((9*testDisplayCnt) % 10);
	char2lcd((5*testDisplayCnt) % 10);

	testDisplayCnt++;
}

int main(void){
	colorimeterInit();
	delay_ms(10);

	uint16_t buttonStat = 0x0000;

	displayPrint();

	ledToggle();

	while(1){
		if(GPIO_ReadInputData(GPIOC) == buttonStat) delay_ms(100);
		else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == 0){
			buttonStat = GPIO_ReadOutputData(GPIOC);
			delay_ms(100);
		}
		else{
			buttonStat = GPIO_ReadOutputData(GPIOC);
			delay_ms(50);
			ledToggle();
			displayPrint();
			ledToggle();
		}
	}
}
