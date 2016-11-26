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
void settingLed();
void transfer();
void show_absolute();

#endif /* INCLUDE_DISPLAY_H_ */
