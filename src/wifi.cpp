
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h> 

#include "wifi.h"

void WLAN::setup() {
    wifi_station_set_hostname("wortuhr");
    WiFi.hostname("wortuhr");
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.forceSleepWake();
    WiFi.setOutputPower(18);

    WiFiManagerParameter custom_domain("domainname", "Wort Uhr", "wortuhr", 20);
    WiFiManager wifiManager;

    wifiManager.addParameter(&custom_domain);
    wifiManager.setHostname("wortuhr");
    // wifiManager.resetSettings(); //for debugging 
    wifiManager.autoConnect("wortuhr");

}

void WLAN::reset(){
    WiFi.disconnect(true);
}
