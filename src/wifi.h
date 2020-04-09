// WIFI Connection Handling
#pragma once
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h> 

class WLAN {
    public:
        static void setup();
        static void reset();
};