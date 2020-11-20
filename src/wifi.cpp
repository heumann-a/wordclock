
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h> 

#include "wifi.h"

void WLAN::setup() {
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.forceSleepWake();
    WiFi.setOutputPower(18);
    
    // Use Both to Set Hostname   
    WiFi.hostname("Wortuhr");
    wifi_station_set_hostname("Wortuhr");

    WiFiManager wifiManager;
    // wifiManager.resetSettings(); //for debugging 
    wifiManager.autoConnect("Wortuhr");
}

void WLAN::reset(){
    WiFi.disconnect(true);
}
