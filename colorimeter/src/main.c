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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "modes.h"
#include "i2c.h"
#include "spi.h"
#include "helper.h"
#include "LCD.h"
#include "bitMap.h"
#include "usart.h"
#include "interrupts.h"
#include "buttons.h"
#include "sampling.h"
#include "adc.h"

#define SAMPLE_SIZE 255

static settingsTypeDef setting;


static uint16_t *samples;  // bit0=valid, bit1=red, bit2=green, bit3=blue, bit4-7=room, bit8-15=randomVal
static uint16_t sampleNum = 0;
static uint8_t roomNum = 0;

#define MAIN_MENU_SIZE 3 //size -1
static char mainMenu[][15] = {	"SAMPLE",
								"MEMORY",
								"BLUETOOTH",
								"SLEEP"};

/*****************
 * Sub Menu
 *
 * Sub menu number goes in the same order here starting at 0 (e.g. submenu 1 is memory)
 */

#define SAMPLE_MENU_SIZE 1 //size -1
static char sampleMenu[][15] = {	"FAST SAMPLE",
									"NAME SAMPLE"};

#define MEMORY_MENU_SIZE 2 //size -1
static char memoryMenu[][15] = {	"DISPLAY LAST",
									"ERASE LAST",
									"ERASE ALL"};

#define BLUETOOTH_MENU_SIZE 1 //size -1
static char bluetoothMenu [][15] = {	"ENABLE/DISABLE",
										"SCAN"};

#define SLEEP_MENU_SIZE 2 //size -1
static char sleepMenu [][15] = {		"ENABLE/DISABLE",
										"15 SECONDS",
										"30 SECONDS"};
/*****************
 * Sub Menu End
 */

/*****************
 * Room Names
 */
#define ROOM_NAME_SIZE 5
static char roomName [][15] = {	"BEDROOM",
								"KITCHEN",
								"BATHROOM",
								"OFFICE",
								"LIVING ROOM"};
/*****************
 * Room names end
 */

void colorimeterInit(){
	SystemInit();
	i2c1Init();
	spi1Init();
	ledInit();
	lcdInit();
	uart1Init();
	buttonInit();
	sampleInit();
	adcInit();

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

	samples = calloc(SAMPLE_SIZE, sizeof(uint16_t));

	nvicInit();
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

bool displayMenu(uint32_t subMenuLevel, uint32_t subMenu, uint32_t y){
	lcdClear();
	lcdHomeX();
	lcdHomeY();

	switch(subMenuLevel){
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
		case(1):
				switch(subMenu){
					case(0): //sample menu
							string2lcd(sampleMenu[(!y) ? SAMPLE_MENU_SIZE : y-1]);

							lcdLine(2);
							lcdHomeX();
							arrow2lcd();
							string2lcd(sampleMenu[y]);

							lcdLine(4);
							lcdHomeX();
							string2lcd(sampleMenu[((y+1) > SAMPLE_MENU_SIZE) ? 0 : y+1]);
							break;
					case(1): //memory menu
							string2lcd(memoryMenu[(!y) ? MEMORY_MENU_SIZE : y-1]);

							lcdLine(2);
							lcdHomeX();
							arrow2lcd();
							string2lcd(memoryMenu[y]);

							lcdLine(4);
							lcdHomeX();
							string2lcd(memoryMenu[((y+1) > MEMORY_MENU_SIZE) ? 0 : y+1]);
							break;
					case(2): //bluetooth menu
						string2lcd(bluetoothMenu[(!y) ? BLUETOOTH_MENU_SIZE : y-1]);

						lcdLine(2);
						lcdHomeX();
						arrow2lcd();
						string2lcd(bluetoothMenu[y]);

						lcdLine(4);
						lcdHomeX();
						string2lcd(bluetoothMenu[((y+1) > BLUETOOTH_MENU_SIZE) ? 0 : y+1]);
						break;
					case(3): //sleep menu
						string2lcd(sleepMenu[(!y) ? SLEEP_MENU_SIZE : y-1]);

						lcdLine(2);
						lcdHomeX();
						arrow2lcd();
						string2lcd(sleepMenu[y]);

						lcdLine(4);
						lcdHomeX();
						string2lcd(sleepMenu[((y+1) > SLEEP_MENU_SIZE) ? 0 : y+1]);
						break;

					default:
						return 1;
				}
				break;
		default:
				return 1;
	}
	return 0;
}

int main(void){
	colorimeterInit();
	delay_ms(10);

	uint8_t menuLevel = 0,
			subMenu = 0,
			menueLoc;


//	uint16_t buttonStat = 0x0000;

	ledToggle();

	uint8_t temp = 0;
	uart1Send("Start", 5);
	char val[10];
	while(1){
		displayMenu(1, 3, temp);
		temp++;
		if(temp > SLEEP_MENU_SIZE) temp = 0;
		delay_ms(100);
		ADC_StartOfConversion(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

		//while(!(buttonRead()));
		readSample(samples, sampleNum, roomNum);
		sprintf(val, "%i\n", ADC_GetConversionValue(ADC1));
		uart1Send(val, strlen(val));

	}

	while(1){

	}
}
