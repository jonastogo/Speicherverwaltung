/*
 * display.h
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */

#ifndef INCLUDE_DISPLAY_H_
#define INCLUDE_DISPLAY_H_

#include "ledbar.h"
#include <wiringPi.h>

void init_led();
void set_led(leds led);
void transfer();

#endif /* INCLUDE_DISPLAY_H_ */
