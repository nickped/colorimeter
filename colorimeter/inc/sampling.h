/*
 * sampling.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Nick
 */

#ifndef SAMPLING_H_
#define SAMPLING_H_

#include "stm32f0xx.h"

typedef struct {
	uint32_t red,
			 green,
			 blue;
}colorStruct;

#define LED_RED 0x00 //TODO: change number
#define LED_BLUE 0x00 //TODO: change number
#define LED_GREEN 0x00 //TODO: change number

#define AMBIANT_LIGHT 0x00 //TODO: change number

#define SAMPLE_ERROR_OKAY 0x00
#define SAMPLE_ERROR_AMBIENT_LIGHT 0x01
#define SAMPLE_ERROR_READ 0x02


void sampleInit();
uint16_t readSample(uint16_t *samples, uint16_t sampleNum, uint8_t roomNum);
uint16_t redRead();
uint16_t greenRead();
uint16_t blueRead();

/*
//public functions
uint8_t readSample(colorStruct *colorVals);

//private functions
uint32_t lightRead();
void lightRed();
void lightBlue();
void lightGreen();
void lightNone();*/
#endif /* SAMPLING_H_ */
