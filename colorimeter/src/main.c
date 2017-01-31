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

#include "i2c.h"
#include "helper.h"

static volatile uint32_t mode = 0;

void colorimeterInit(){
	SystemInit();
	i2c1Init();
	ledInit();
}

int main(void){
	colorimeterInit();

	while(1){
		delay_ms(200);
		ledToggle();
	}
}
