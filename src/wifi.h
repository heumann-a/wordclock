// WIFI Connection Handling
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <Arduino.h>

class WLAN {
    public:
        static void setup();
        static void reset();
};