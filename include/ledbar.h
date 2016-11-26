
/**
 * @file ledbar.h
 * @author Jonas Lampe
 * @date 05.11.2016
 * @brief File containing all visible functions from ledbar.c and some typedefs.
 *
 * This File contains all visible functions from ledbar.c
 * It also contains an enum with all the LEDs, aswell as an enum with all possible brightness.
 * Contains typedef of byte.
 */

/**
 * @brief typedef of a byte.
 *
 * Typedef of a byte. A byte is an unsigned char.
 */
typedef unsigned char byte;

/**
 * @brief Enum of all LEDS.
 *
 * Enum of all LEDs and their indexes.
 */
typedef enum LEDS {LED01=1, LED02=2, LED03=3, LED04=4, LED05=5, LED06=6, LED07=7, LED08=8, LED09=9, LED10=10} leds;

/**
 * @brief Enum of all possible brightnesses.
 *
 * Enum of all possible brighnesses and their values.
 */
typedef enum BRIGHTNESS {OFF=0x00, LOWMED=0x42, MED=0x7B, HIGHMED=0xBD,FULL=0xFF} brightness;


/**
 * @brief Doc in lebbar.c
 */
void com_init();

/**
 * @brief Doc in lebbar.c
 */
void transfer_data();

/**
 * @brief Doc in lebbar.c
 */
int set_led(leds led, brightness brt);

/**
 * @brief Doc in lebbar.c
 */
int set_brightness(brightness brt);

/**
 * @brief Doc in lebbar.c
 */
brightness get_led(leds led);
