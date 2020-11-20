#ifndef WORDCLOCK_CONFIG_H
#define WORDCLOCK_CONFIG_H

#include <Arduino.h>
#include "types.h"

/***********************************************
 * CONFIG START
 **********************************************/

/* Postition of first LED
 *
 * Options
 * -------
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#ifndef GRID_FIRST
  #define GRID_FIRST 2
#endif

/* Position of single minute LEDs
 *
 * Options
 * -------
 * 0: before
 * 1: after
 * 2: disabled
 */
#ifndef GRID_SINGLE_MINUTES
  #define GRID_SINGLE_MINUTES 2
#endif

/* Data PINs, where the LED strip are connected to */
#define DATA_PIN D4
#define DATA_PIN2 D3

/* Amount of LEDs per DATA_PIN and complete number*/
#define NUM_LEDS_FIRST 66
#define NUM_LEDS_SECOND 55
#define NUM_LEDS NUM_LEDS_FIRST + NUM_LEDS_SECOND


#ifndef CONSUMPTION_D1_MINI
  #define CONSUMPTION_D1_MINI 170 // 170mA in active mode
#endif

#ifndef CONSUMPTION_PER_LED
  #define CONSUMPTION_PER_LED 60 // 60mA per LED on full brightness in white.
#endif

/***********************************************
 * CONFIG END
 **********************************************/

class Config {
  public:
    static color_t color_bg;
    static color_t color_fg;
    static int power_supply;
    static double brightness;
    static bool automatic_timezone;
    static int timezone;
    static bool dnd_active;
    static clock_time_t dnd_start;
    static clock_time_t dnd_end;
    static String ntp;

    static void save();
    static void load();
};
#endif
