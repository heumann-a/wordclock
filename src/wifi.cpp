
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h> 

#include "wifi.h"

void WLAN::setup() {
    WiFi.hostname("Wortuhr");

    WiFiManager wifiManager;
    // wifiManager.resetSettings(); //for debugging 
    wifiManager.autoConnect("Wortuhr");
}

void WLAN::reset(){
    WiFi.disconnect(true);
}