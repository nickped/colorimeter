/*
 * i2c.h
 *
 *  Created on: Jan 19, 2017
 *      Author: Nick
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f0xx.h"

#define I2C_ERROR_OKAY 		0x00
#define I2C_ERROR_TIMEOUT 	0x01

#define I2C_TIMEOUT 0x0000FFFF

void i2c1Init();
uint32_t i2cWriteData(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t numBytes);
uint32_t i2cReadData(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t numBytes);


#endif /* I2C_H_ */
