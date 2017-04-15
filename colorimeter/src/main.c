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
#include "usart.h"

static settingsTypeDef setting;

#define MAIN_MENU_SIZE 3
static char mainMenu[][10] = {	"SAMPLE",
								"MEMORY",
								"BLUETOOTH",
								"SLEEP"};

void colorimeterInit(){
	SystemInit();
	i2c1Init();
	spi1Init();
	ledInit();
	lcdInit();
	uart4Init();

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

void RGB2LCD(uint32_t red, uint32_t green, uint32_t blue){
	uint32_t timer = 0;
	uint32_t temp = 0;
	lcdClear();
	lcdHomeX();
	lcdHomeY();

	timer = 1;
	char2lcd(char2bit('R'));
	lcdColon();
	lcdXAxis(2);
	if(red){
		while(red / timer)
			timer *= 10;

		timer /= 10;
		while(timer){
			temp = red / timer;
			temp = temp % 10;
			char2lcd(temp);
			timer /= 10;
		}
	}
	else
		char2lcd(0);

	timer = 1;
	lcdLine(2);
	lcdHomeX();
	char2lcd(char2bit('G'));
	lcdColon();
	lcdXAxis(2);
	if(green){
		while(green / timer)
			timer *= 10;

		timer /= 10;
		while(timer){
			temp = green / timer;
			temp = temp % 10;
			char2lcd(temp);
			timer /= 10;
		}
	}
	else
		char2lcd(0);

	timer = 1;
	lcdLine(4);
	lcdHomeX();
	char2lcd(char2bit('B'));
	lcdColon();
	lcdXAxis(2);
	if(blue){
		while(blue / timer)
			timer *= 10;

		timer /= 10;
		while(timer){
			temp = blue / timer;
			temp = temp % 10;
			char2lcd(temp);
			timer /= 10;
		}
	}
	else
		char2lcd(0);
}

bool displayMenu(uint32_t x, uint32_t y){
	lcdClear();
	lcdHomeX();
	lcdHomeY();

	switch(x){
		case(0):
				string2lcd(mainMenu[(!y) ? MAIN_MENU_SIZE : y-1]);

				lcdLine(2);
				lcdHomeX();
				arrow2lcd();
				string2lcd(mainMenu[y]);

				lcdLine(4);
				lcdHomeX();
				string2lcd(mainMenu[((y+1) > MAIN_MENU_SIZE) ? 0 : y+1]);
				break;
		default:
				return 1;
	}
	return 0;
}

int main(void){
	colorimeterInit();
	delay_ms(10);

//	uint16_t buttonStat = 0x0000;

	ledToggle();

/*	uint32_t red = 0,
			 green = 0,
			 blue = 0;*/
	uint8_t temp = 0;
	while(1){
		displayMenu(0,temp);
		temp++;
		if(temp > MAIN_MENU_SIZE) temp = 0;
		delay_ms(1000);
		/*RGB2LCD(red, green, blue);
		red += 1;
		green += 3;
		blue += 5;
		delay_ms(500);*/
	}
}
