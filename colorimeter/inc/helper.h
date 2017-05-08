/*
 * helper.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Nick
 */

#ifndef HELPER_H_
#define HELPER_H_

#define nop2() {asm volatile ("nop" : "nop")}

#define bool _Bool
#define true 1
#define false 0

#define SAMPLE_SIZE 150

typedef struct{
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	uint8_t room;
}sample_t;

/*****************
 * Room Names
 */
#define ROOM_NAME_SIZE 4
static const char roomName [][15] = {	"BEDROOM",
										"KITCHEN",
										"BATHROOM",
										"OFFICE",
										"GARAGE"};
/*****************
 * Room names end
 */

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void ledInit();
void ledToggle();

#endif /* HELPER_H_ */
