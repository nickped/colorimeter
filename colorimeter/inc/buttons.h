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

#define BUTTON_DEBOUNCE_NUM 0x1F //number of debounce cycles. Can't be more than 5 bits. (eg. 0x04 = 3 debounce cycles)

#define BUTTON1 0   //PC10
#define BUTTON2 1   //PC11
#define BUTTON3 2   //PC12
#define BUTTON4 3   //PC13
#define BUTTON5 4   //PC14

void buttonInit();
uint8_t buttonRead();

#endif /* BUTTONS_H_ */
