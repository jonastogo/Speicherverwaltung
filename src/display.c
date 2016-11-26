/*
 * display.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */

#include "../include/ledbar.h"
#include "../include/speicherverwaltung.h"

void init_led(){
	com_init();
}

void settingLed(){
	int *array = absolute();
	int i;
	for(i = 0;i <10; i++){
		if(array[i] == 0){
			set_led((i+1), OFF);
		}
		else{
			set_led((i+1), FULL);
		}
	}
}

void transfer(){
	transfer_data();
}

void show_absolute(){
	com_init();
	settingLed();
	transfer();
}


