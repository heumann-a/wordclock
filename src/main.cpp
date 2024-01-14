/*
Code by Heumann
Project for Wordclock with Wifi NTP updates
- March 2020
*/


// Global HeaderFiles
#include <LittleFS.h>


// Custom HeaderFiles
#include "ntptime.h"
#include "controller.h"
#include "webserver.h"
#include "webgui.h"
#include "wifi.h"
#include "ota.h"
#include "config.h"
#include "grid.h"
#include "types.h"
#include "color.h"
#include "dnd.h"
#include "led.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  LittleFS.begin();

  Serial.println("Init-Step Load Config");
  Config::load();
  Serial.println("Init-Step LED");
  Led::setup();
  Led::LEDTest();

  Serial.println("Init-Step WLAN");
  WLAN::setup();
  Serial.println("Init-Step WebServer");
  WebServer::setup();
  Serial.println("Init-Step NTPTime");
  NTPTime::setup();
  Serial.println("Init-Step OTA");
  OTAUpdate::setup();

  Grid::setLanguage(Config::language_de_alt);
  Grid::setTime(NTPTime::month, NTPTime::day, NTPTime::hour, NTPTime::minute);
  Serial.println("Init-Finished");
}

void loop() {
  NTPTime::loop();
  WebServer::loop();  
  OTAUpdate::loop();
}