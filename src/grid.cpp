#include <Arduino.h>

#include "grid.h"

#include "config.h"
#include "dnd.h"
#include "led.h"


void Grid::setTime(int month, int day, int hour, int minute) {

    if(hour == -1 || minute == -1) {
        return;
    }

    if(DND::active(hour, minute)) {
        for(int i = 0; i < NUM_LEDS; i++) {
            Led::ids[i].setRGB(0, 0, 0);
        }

        FastLED.show();
        return;
    }

    int singleMinute = minute % 5;
    int hourLimit = 6;
    
    minute = (minute - (minute % 5));
    
    if (Config::language_de_alt) {
        if(minute >= 15) {
            hour += 1;
        }
    } else {
        if(minute >= 25) {
	        hour += 1;
        }
    }


    minute = minute / 5;
    hour = hour % 12;

    for(int i = 0; i < NUM_LEDS; i++) {
        Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
    }
    
    for(int i = 0; i < 5; i++) {
        Led::ids[Led::getLedId(Grid::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    }

    for(int m = 0; m < 12; m++) {
        if ( *(Grid::minutes + ( minute * 12) + m) >= 0) {
            Led::ids[Led::getLedId( *(Grid::minutes + ( minute * 12) + m) )].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
        }
    }

    if(hour == 1 && minute == 0) {
        hourLimit = 3;
    }
    
    for(int h = 0; h < hourLimit; h++) {  
        if(Grid::time_hours[hour][h] >= 0) {
            Led::ids[Led::getLedId(Grid::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
        }
    }

    // 2 disable Single Minutes
    if(GRID_SINGLE_MINUTES < 2){
        if(GRID_SINGLE_MINUTES == 1) {
            // Single Minutes at the END
            for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
                Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
            }
        } else {
            // Single Minutes at the BEGINNING
            for(int s = 0; s < singleMinute; s++) {
                Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
            }
        }
    }

    FastLED.setBrightness(Config::brightness * 255);
    FastLED.show();
}

void Grid::setLanguage(bool language_alt) {

    if ( language_alt ) {
        Grid::minutes = &Grid::alt_time_minutes[0][0];
    } else {
        Grid::minutes = &Grid::time_minutes[0][0];
    }
}


int Grid::time_it_is[5] = {0, 1, 3, 4, 5}; // es ist
	
int Grid::alt_time_minutes[12][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  -1,  -1,  -1,  -1,  -1}, // viertel
  { 11,  12,  13,  14,  39,  40,  41,  44,  45,  46,  47,  -1}, // zehn vor halb
  {  7,   8,   9,  10,  39,  40,  41,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  35,  36,  37,  38,  44,  45,  46,  47}, // fünf nach halb
  { 11,  12,  13,  14,  35,  36,  37,  38,  44,  45,  46,  47}, // zehn nach halb
  { 22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  -1}, // dreiviertel	
  { 11,  12,  13,  14,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid::time_minutes[12][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  35,  36,  37,  38,  -1}, // viertel nach
  { 15,  16,  17,  18,  19,  20,  21,  35,  36,  37,  38,  -1}, // zwanzig nach
  {  7,   8,   9,  10,  39,  40,  41,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  35,  36,  37,  38,  44,  45,  46,  47}, // fünf nach halb
  { 15,  16,  17,  18,  19,  20,  21,  39,  40,  41,  -1,  -1}, // zwanzig vor
  { 26,  27,  28,  29,  30,  31,  32,  39,  40,  41,  -1,  -1}, // viertel vor
  { 11,  12,  13,  14,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid::time_hours[12][6] = {
  { 49,  50,  51,  52,  53,  -1}, // zwölf
  { 57,  58,  59,  60,  -1,  -1}, // eins
  { 55,  56,  57,  58,  -1,  -1}, // zwei
  { 67,  68,  69,  70,  -1,  -1}, // drei
  { 84,  85,  86,  87,  -1,  -1}, // vier
  { 73,  74,  75,  76,  -1,  -1}, // fünf
  {100, 101, 102, 103, 104,  -1}, // sechs
  { 60,  61,  62,  63,  64,  65}, // sieben
  { 89,  90,  91,  92,  -1,  -1}, // acht
  { 80,  81,  82,  83,  -1,  -1}, // neun
  { 93,  94,  95,  96,  -1,  -1}, // zehn
  { 77,  78,  79,  -1,  -1,  -1}  // elf
};

int *Grid::minutes = &Grid::alt_time_minutes[0][0];