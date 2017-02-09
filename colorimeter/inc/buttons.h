/*
 * buttons.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "stm32f0xx.h"
#include "helper.h"

#define BUTTON_DEBOUNCE_NUM 0x00FF //number of ones on the lsb side is the amount of debounce cycles

//All ports has to either be PORTA or PORTB
#define BUTTON_1_PORT GPIOB
#define BUTTON_2_PORT GPIOB
#define BUTTON_3_PORT GPIOB
#define BUTTON_4_PORT GPIOB

#define BUTTON_1_PIN 0
#define BUTTON_2_PIN 1
#define BUTTON_3_PIN 2
#define BUTTON_4_PIN 3

typedef struct{
	uint16_t button1;
	uint16_t button2;
	uint16_t button3;
	uint16_t button4;
}buttonDebounceTypeDef;

typedef struct{
	bool button1;
	bool button2;
	bool button3;
	bool button4;
}buttonTypeDef;

//Public functions
void buttonInit();
buttonTypeDef buttonRead(buttonDebounceTypeDef *debounceReg);

//Private functions
buttonTypeDef buttonState();


#endif /* BUTTONS_H_ */
