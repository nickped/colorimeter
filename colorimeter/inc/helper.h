/*
 * helper.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Nick
 */

#ifndef HELPER_H_
#define HELPER_H_

#define nop2() {asm volatile ("nop" : "nop")}

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void ledInit();
void ledToggle();

#endif /* HELPER_H_ */
