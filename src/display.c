/*
 * display.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */

#include "../include/ledbar.h"

void init_led(){
	com_init();
}

void set_led(leds led){
	set_led(led, FULL);
}

void transfer(){
	transfer_data();
}


