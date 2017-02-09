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

static settingsTypeDef setting;

void colorimeterInit(){
	SystemInit();
	i2c1Init();
	spi1Init();
	ledInit();

	setting.sleep = ON;
	setting.sleepTime = SETTINGS_SLEEPTIME_10min;
	setting.blueTooth = OFF;
}

int main(void){
	colorimeterInit();

	while(1){
		delay_ms(200);
		ledToggle();
	}
}
