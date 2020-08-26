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
#include <LittleFS.h>


// Custom HeaderFiles
#include "ntptime.h"
#include "controller.h"
#include "webserver.h"
#include "webgui.h"
#include "wifi.h"
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

  Serial.println("Init-Step WLAN");
  WLAN::setup();
  Serial.println("Init-Step WebServer");
  WebServer::setup();
  Serial.println("Init-Step LED");
  Led::setup();
  Serial.println("Init-Step NTPTime");
  NTPTime::setup();

  Grid::setTime(NTPTime::hour, NTPTime::minute);

  Led::LEDTest();
}

void loop() {
  // put your main code here, to run repeatedly
  NTPTime::loop();
  WebServer::loop();  
}
