
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h> 

#include "wifi.h"

void WLAN::setup() {
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.forceSleepWake();
    WiFi.setOutputPower(18);
    
    // Use Both to Set Hostname   
    wifi_station_set_hostname("wortuhr");
    WiFi.hostname("wortuhr");

    WiFiManager wifiManager;
    wifiManager.setHostname("wortuhr");
    // wifiManager.resetSettings(); //for debugging 
    wifiManager.autoConnect("wortuhr");
}

void WLAN::reset(){
    WiFi.disconnect(true);
}
