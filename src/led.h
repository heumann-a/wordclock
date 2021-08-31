#ifndef WORDCLOCK_LED_H
#define WORDCLOCK_LED_H

#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include "config.h"

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
