/*
 * bitMap.c
 *
 *  Created on: Apr 12, 2017
 *      Author: Nick
 */

#include <stm32f0xx.h>
#include "bitMap.h"

uint8_t char2bit(char letter){
	return (uint8_t)letter - (uint8_t)'A' + ASCII_DEF_A;
}
