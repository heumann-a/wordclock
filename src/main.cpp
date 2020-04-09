/*
Code by Heumann
Project for Wordclock with Wifi NTP updates
- March 2020
*/

#include "wifi.h"
#include "ntptime.h"
#include "webserver.h"
#include "webgui.h"

// Var to initialize local AP
IPAddress Current_IP(192,168,1,5);
IPAddress gateway(192,168,1,10);
IPAddress subnet(255,255,255,0);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WLAN::setup();
  NTPTime::setup();
  WebServer::setup();
  //LED::setup();

  //Grid::setup();
}

void loop() {
  // put your main code here, to run repeatedly
  NTPTime::loop();
  WebServer::loop();
  delay(3000);
}
