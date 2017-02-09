/*
 * modes.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Nick
 */

#ifndef MODES_H_
#define MODES_H_

#include "stm32f0xx.h"
#include "helper.h"

/*#define MODE_TYPE_HOME 		0x0000
#define MODE_TYPE_SAMPLING 	0x0001
#define MODE_TYPE_SETTINGS	0x0002
#define MODE_TYPE_USB		0x0004
typedef struct{
	uint16_t type;
	uint16_t settings;
}modeTypeDef;*/


#define ON true
#define OFF false
#define SETTINGS_SLEEPTIME_5min 0x01
#define SETTINGS_SLEEPTIME_10min 0x02
typedef struct{
	bool sleep;
	uint8_t sleepTime;
	bool blueTooth;
}settingsTypeDef;

#endif /* MODES_H_ */
