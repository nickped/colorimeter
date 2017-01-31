/*
 * sampling.c
 *
 *  Created on: Jan 27, 2017
 *      Author: Nick
 */

#include "sampling.h"

#define nop2() asm volatile ("nop\n\tnop")

/*public functions*/
//TODO: test
uint8_t readSample(colorStruct *colorVals){
	//checking for ambient light
	lightNone();
	nop2();
	if(lightRead() > AMBIANT_LIGHT) return SAMPLE_ERROR_AMBIENT_LIGHT;

	lightRed();
	nop2();
	colorVals->red = lightRead();
	lightGreen();
	nop2();
	colorVals->green = lightRead();
	lightBlue();
	nop2();
	colorVals->blue = lightRead();
	lightNone();


	return SAMPLE_ERROR_OKAY;
}

/*Private functions*/
//TODO: write
void lightRed(){
}

//TODO: write
void lightBlue(){
}

//TODO: write
void lightGreen(){
}

//TODO: write
void lightNone(){
}

//TODO: write
uint32_t lightRead(){
	return 0x00000000;
}
