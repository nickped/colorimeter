/*
 * spi.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f0xx.h"

void spi1Init();
uint8_t spi1Transfer(uint8_t dataOut);

#endif /* SPI_H_ */
