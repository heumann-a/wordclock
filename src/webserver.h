#include <ESP8266WebServer.h>

class WebServer {
    private:
        ESP8266WebServer httpwebserver;
        static String IP;
    public:
        static void setup();
        static void loop();
};