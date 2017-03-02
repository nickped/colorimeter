/*
 * buttons.c
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"
#include "buttons.h"

void buttonInit(){
	GPIO_TypeDef portA, portB;
	uint8_t used = 0;

	//******************************************************FIXME*************
}

buttonTypeDef buttonRead(buttonDebounceTypeDef *debounceReg){
	buttonTypeDef buttonPress;

	buttonPress = buttonState();

	debounceReg->button1 = (debounceReg->button1 << 1) | ((buttonPress.button1) ? 1 : 0);
	debounceReg->button2 = (debounceReg->button2 << 1) | ((buttonPress.button2) ? 1 : 0);
	debounceReg->button3 = (debounceReg->button3 << 1) | ((buttonPress.button3) ? 1 : 0);
	debounceReg->button4 = (debounceReg->button4 << 1) | ((buttonPress.button4) ? 1 : 0);

	buttonPress.button1 = (debounceReg->button1 == BUTTON_DEBOUNCE_NUM) ? true : false;
	buttonPress.button2 = (debounceReg->button2 == BUTTON_DEBOUNCE_NUM) ? true : false;
	buttonPress.button3 = (debounceReg->button3 == BUTTON_DEBOUNCE_NUM) ? true : false;
	buttonPress.button4 = (debounceReg->button4 == BUTTON_DEBOUNCE_NUM) ? true : false;

	return buttonPress;
}

buttonTypeDef buttonState(){
	buttonTypeDef button;

	button.button1 = GPIO_ReadInputDataBit(BUTTON_1_PORT, BUTTON_1_PIN);
	button.button2 = GPIO_ReadInputDataBit(BUTTON_2_PORT, BUTTON_2_PIN);
	button.button3 = GPIO_ReadInputDataBit(BUTTON_3_PORT, BUTTON_3_PIN);
	button.button4 = GPIO_ReadInputDataBit(BUTTON_4_PORT, BUTTON_4_PIN);

	return button;
}
