#ifndef WORDCLOCK_LED_H
#define WORDCLOCK_LED_H

#include <FastLED.h>

// Split LEDS to 2 Pins because got error with one
#define NUM_LEDS_FIRST 66
#define NUM_LEDS_SECOND 55
// TODO: Add 4 LEDs for minutes 
#define NUM_LEDS NUM_LEDS_FIRST + NUM_LEDS_SECOND 
#define DATA_PIN1 D4
#define DATA_PIN2 D3
// Necessary for Code
#define GRID_COLS 11
#define GRID_ROWS 11


class Led {
  public:
    static CRGB ids[];

    static int getLedId(int id);
    static void setup();
    static double getMaxBrightnessPercnt();
    static int getMaxNumberIlluminatedLeds();
    static void LEDTest();
    static void BlackLed();
};

#endif
