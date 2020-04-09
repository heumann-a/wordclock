#pragma once
#include <ESP8266WebServer.h>

class WebServer {
    public:
        static ESP8266WebServer httpwebserver;
        static String IP;

        static void setup();
        static void loop();
};