/*
Code by Heumann
Project for Wordclock with Wifi NTP updates
- March 2020
*/

#include "wifi.h"
#include "ntptime.h"
#include "webserver.h"
#include "webgui.h"
#include <FastLED.h>

// Var to initialize local AP
IPAddress Current_IP(192,168,1,5);
IPAddress gateway(192,168,1,10);
IPAddress subnet(255,255,255,0);


#define NUM_LEDS 88
#define DATA_PIN D4
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // WLAN::setup();
  // NTPTime::setup();
  // WebServer::setup();
  //LED::setup();

  //Grid::setup();

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( 20 );
}

void loop() {
  // put your main code here, to run repeatedly
  // NTPTime::loop();
  // WebServer::loop();
  delay(3000);

  for(int i = 0; i < NUM_LEDS; i++) {
    int led = i;
    //Serial.print("Test");
    leds[led] = CRGB::Red; 
    FastLED.show();
    delay(500);
    
    leds[led] = CRGB::Black;
    FastLED.show();
  }
    
    // for(int i = 0; i < NUM_LEDS; i++) {
    //   int led = i;
    //   leds[led] = CRGB::White; 
      
    // }
    // FastLED.show();
    // delay(5000);

    // for(int i = 0; i < NUM_LEDS; i++) {
    //   int led = i;
    //   leds[led] = CRGB::Black; 
      
    // }

    // FastLED.show();
}
