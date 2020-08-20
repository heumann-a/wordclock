/*
Code by Heumann
Project for Wordclock with Wifi NTP updates
- March 2020
*/


// Global HeaderFiles
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>


// Custom HeaderFiles
#include "ntptime.h"
#include "webcontroller.h"
#include "webserver.h"
#include "webgui.h"
#include "wifi.h"
#include "config.h"


// Var to initialize local AP
// IPAddress Current_IP(192,168,1,5);
// IPAddress gateway(192,168,1,10);
// IPAddress subnet(255,255,255,0);


#define NUM_LEDS_FIRST 66
#define NUM_LEDS_SECOND 55
#define NUM_LEDS NUM_LEDS_FIRST + NUM_LEDS_SECOND
#define DATA_PIN1 D4
#define DATA_PIN2 D3
CRGB leds[NUM_LEDS];

void LEDTest(){
    for(int i = 0; i < NUM_LEDS; i++) {
    int led = i;
    leds[led] = CRGB::Blue; 
    FastLED.show();
    delay(200);
    
    leds[led] = CRGB::Black;
    FastLED.show();
  }
}

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);

  // WLAN::setup();
  // NTPTime::setup();
  // WebServer::setup();
  //LED::setup();

  //Grid::setup();

  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds, 0, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds, NUM_LEDS_FIRST, NUM_LEDS);
  FastLED.setBrightness( 10 );
}

void loop() {
  // put your main code here, to run repeatedly
  NTPTime::loop();
  WebServer::loop();
  delay(1000);

  //TODO: GUI + Abhängigkeiten lösen
 
}
