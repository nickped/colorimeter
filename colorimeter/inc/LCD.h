/*
 * LCD.h
 *
 *  Created on: Mar 9, 2017
 *      Author: Nick
 */

#include "stm32f0xx.h"

#ifndef LCD_H_
#define LCD_H_

#define LCDWIDTH 84
#define LCDHEIGHT 48

#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80

#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80

void lcdControl(uint8_t byte);
void lcdInit();
void char2lcd(uint8_t byte);
void lcdLine(uint8_t line);
void byte2lcd(uint8_t byte);
void lcdColon();
void lcdClear();
void lcdHomeX();
void lcdHomeY();
void lcdXAxis(uint8_t loc);
void string2lcd(char *str);
void arrow2lcd();
void space2lcd();

#endif /* LCD_H_ */
