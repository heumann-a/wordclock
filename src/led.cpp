#include "grid.h"
#include "led.h"
#include "config.h"

// Necessary for Code
#define GRID_COLS 11
#define GRID_ROWS 11

int Led::getLedId(int id) {
  int col = id % GRID_COLS;
  int row = (floor)(id / GRID_COLS);
  int led = 0;

  if(GRID_FIRST == 3) {
    led = (row % 2 != GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 2) {
    led = (row % 2 == GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 1) {
    led = (row % 2 == 0) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  } else if(GRID_FIRST == 0) {
    led = (row % 2 == 1) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  }

  if(GRID_SINGLE_MINUTES == 0) {
    led += 4;
  }

  return led;
}

void Led::setup() {
  FastLED.addLeds<WS2812B, DATA_PIN1, GRB>(Led::ids, 0, NUM_LEDS_FIRST);
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(Led::ids, NUM_LEDS_FIRST, NUM_LEDS_SECOND);
  FastLED.setBrightness(10);

  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i].setRGB(0, 0, 0);
  }

  FastLED.show();
}

double Led::getMaxBrightnessPercnt() {
  const int max_consumption = getMaxNumberIlluminatedLeds() * CONSUMPTION_PER_LED;
  const double brightness_percnt = (Config::power_supply - CONSUMPTION_D1_MINI) / (double) max_consumption;

  return (brightness_percnt >= 1.0) ? 1.0 : brightness_percnt;
}

int Led::getMaxNumberIlluminatedLeds() {

  int max_time_it_is = sizeof(Grid::time_it_is)/sizeof(Grid::time_it_is[0]);
  int max_time_minutes = sizeof(Grid::time_minutes[0])/sizeof(Grid::time_minutes[0][0]);
  int max_time_hours = sizeof(Grid::time_hours[0])/sizeof(Grid::time_hours[0][0]);

  return max_time_it_is + max_time_minutes + max_time_hours;
}

void Led::LEDTest(){
  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i] = CRGB::Blue; 
    FastLED.show();
    delay(25);
    
    Led::ids[i] = CRGB::Black;
    FastLED.show();
  }
}

void Led::BlackLed(){
  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i] = CRGB::Black;
    FastLED.show();
  }
  
}

CRGB Led::ids[NUM_LEDS];
