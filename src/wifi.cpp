#include "wifi.h"

void WLAN::setup() {
    WiFi.hostname("Wortuhr");

    WiFiManager wifiManager;
    wifiManager.autoConnect("Wortuhr");
}

void WLAN::reset(){
    WiFi.disconnect(true);
}