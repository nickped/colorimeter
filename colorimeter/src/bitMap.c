/*
 * bitMap.c
 *
 *  Created on: Apr 12, 2017
 *      Author: Nick
 */

#include <stm32f0xx.h>
#include "bitMap.h"

uint8_t char2bit(char letter){
	if (letter <= '9' && letter >= '0') return (letter - '0');
	if( letter == '/') return ASCII_DEF_SLASH;
	return (uint8_t)letter - (uint8_t)'A' + ASCII_DEF_A;
}
