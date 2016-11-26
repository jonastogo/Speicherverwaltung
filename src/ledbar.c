/**
 * @file ledbar.c
 * @author Jonas Lampe
 * @date 05.11.2016
 * @brief File containing functions to send data to LED_BAR.
 *
 * This File contains functions to send data to a LED_BAR.
 * It is possible to control a single LED or the whole LED_BAR.
 * You can set the Brightness of every single LED.
 */


#define PIN_DATA 16         /* auf dem Shield PIN 15 */
#define PIN_CLOCK 27        /* auf dem Shield PIN 16 */

#include <wiringPi.h>
#include "../include/ledbar.h"

static void init_led_bar(void);
static void send_led_data(void);
static void toggle_clock(void);
static void latch_led_data(void);

static const byte REGISTER1 = 0x00;
static const byte REGISTER2 = 0x00;
static const byte EMPTY = 0x00;

byte LED_Bar_Status[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/**
 * @brief Initializes the communication with the LED_Bar.
 *
 * This function initializes the communication with the LED_Bar.
 * It is the first function, you need to call before communicate with the LED_Bar.
 */
static void init_led_bar() {
    int device_initialised = 0;

    if (!device_initialised) {
        wiringPiSetup();
        pinMode(PIN_DATA, OUTPUT);
        pinMode(PIN_CLOCK, OUTPUT);
        digitalWrite(PIN_DATA, LOW);
        digitalWrite(PIN_CLOCK, LOW);
        device_initialised = 1;
    }
}

/**
 * @brief Sends the data to the LED_Bar.
 *
 * This function sends the bytes to the LED_Bar.
 * It sends a 16bit String to control a single LED.
 */
static void send_led_data() {
	int i;
    delayMicroseconds(250);

    send_byte(REGISTER1);
    send_byte(REGISTER2);

    for (i = 0; i < 10; i++) {
        send_byte(EMPTY);
        send_byte(LED_Bar_Status[i]);
    }

    for (i = 0; i < 4; i++) {
        send_byte(EMPTY);
    }

    latch_led_data();
}

/**
 * @brief Toggles the Clock_Pin to update the DATA_PIN.
 *
 * This function toggles the CLOCK_Pin.
 * Every Time the status of the CLOCK_Pin changes, the DATA_Pin will be updated.
 */
static void toggle_clock() {
    static int clock_pin_active = 0;

    if (clock_pin_active) {
        digitalWrite(PIN_CLOCK, LOW);
        clock_pin_active = 0;
    } else {
        digitalWrite(PIN_CLOCK, HIGH);
        clock_pin_active = 1;
    }
}
/**
 * @brief Closes the communication with the LED_Bar.
 *
 * Closes the communication with the LED_Bar.
 */
static void latch_led_data() {
    int i;

    digitalWrite(PIN_DATA, LOW);
    delayMicroseconds(250);

    for (i = 0; i < 4; i++) {
        digitalWrite(PIN_DATA, HIGH);
        delayMicroseconds(1);
        digitalWrite(PIN_DATA, LOW);
        delayMicroseconds(1);
    }

    delayMicroseconds(250);
    digitalWrite(PIN_CLOCK, LOW);
}

/**
 * @brief Sends a whole byte to the LED_BAR.
 *
 * Sends a whole byte to the LED_Bar and toggles the Clock every Bit.
 * MSB first.
 * @param byte That byte will be sent
 */
void send_byte(byte byte) {
	int i;
	for(i = 0; i < 8; i ++) {
		if(byte & (0x80 >> i)) {
			digitalWrite(PIN_DATA,HIGH);
		} else {
			digitalWrite(PIN_DATA, LOW);
		}
		toggle_clock();
	}
}

/**
 * @brief Sets the brightness of a LED.
 *
 * Sets the brightness of a LED (no send).
 *
 * @param led The LED, that will be changed
 * @param brt The brightness
 * @return 1 if OK, 0 if not OK
 */
int set_led(leds led, brightness brt){
	switch(led) {
	      case LED01: LED_Bar_Status[0] = brt;
	              return 1;
	      case LED02: LED_Bar_Status[1] = brt;
	      	  	  return 1;
	      case LED03: LED_Bar_Status[2] = brt;
	      	  	  return 1;
	      case LED04: LED_Bar_Status[3] = brt;
	      	  	  return 1;
	      case LED05: LED_Bar_Status[4] = brt;
	      	  	  return 1;
	      case LED06: LED_Bar_Status[5] = brt;
	      	  	  return 1;
		  case LED07: LED_Bar_Status[6] = brt;
		  	  	  return 1;
		  case LED08: LED_Bar_Status[7] = brt;
		  	  	  return 1;
		  case LED09: LED_Bar_Status[8] = brt;
		  	  	  return 1;
		  case LED10: LED_Bar_Status[9] = brt;
		  	  	  return 1;
	}
	return 0;
}

/**
 * @brief Sets the brightness of all the LEDs.
 *
 * Sets the brightness of all the LEDs (no send).
 *
 * @param brt The brightness
 * @return 1 if OK, 0 if not OK
 */
int set_brightness(brightness brt){
	int i;
	for(i = 0; i < 10; i++){
		LED_Bar_Status[i] = brt;
	}
	return 1;
}

/**
 * @brief Gets the brightness of a LED.
 *
 * Gets the brightness of a LED.
 *
 * @param led The LED, you get the brightness of
 * @return the brightness of the LED. If failed, -1
 */
brightness get_led(leds led){
	switch(led) {
		      case LED01: return LED_Bar_Status[0];
		      case LED02: return LED_Bar_Status[1];
		      case LED03: return LED_Bar_Status[2];
		      case LED04: return LED_Bar_Status[3];
		      case LED05: return LED_Bar_Status[4];
		      case LED06: return LED_Bar_Status[5];
			  case LED07: return LED_Bar_Status[6];
			  case LED08: return LED_Bar_Status[7];
			  case LED09: return LED_Bar_Status[8];
			  case LED10: return LED_Bar_Status[9];
	}
	return -1;
}

/**
 * @brief API function for init_led_bar().
 */
void com_init(void){
	init_led_bar();
	set_brightness(OFF);
	transfer_data();
}

/**
 * @brief API function for send_led_data().
 */
void transfer_data(void){
	send_led_data();
}

/**
 * @brief Sets the LED with the Index @termin to FULL brightness
 *
 * @param termin Index of the LED
 * @return 1 if worked, 0 if failed
 */
int pruefLEDs(int termin){
	switch(termin) {
		  case 1: LED_Bar_Status[0] = FULL;
				  return 1;
		  case 2: LED_Bar_Status[1] = FULL;
				  return 1;
		  case 3: LED_Bar_Status[2] = FULL;
				  return 1;
		  case 4: LED_Bar_Status[3] = FULL;
				  return 1;
		  case 5: LED_Bar_Status[4] = FULL;
				  return 1;
		  case 6: LED_Bar_Status[5] = FULL;
				  return 1;
		  case 7: LED_Bar_Status[6] = FULL;
				  return 1;
		  case 8: LED_Bar_Status[7] = FULL;
				  return 1;
		  case 9: LED_Bar_Status[8] = FULL;
				  return 1;
		  case LED10: LED_Bar_Status[9] = FULL;
				  return 1;
		  default: return 0;
	}
	return 0;
}
