// NTP WiFi Connection
#include <NTPClient.h>
#include <WiFiUdp.h>

class NTPTime {
    private:
        // Var to connect to NTP
        static WiFiUDP udpNTP;
        // NTP Client initalization
        static NTPClient ntpClient;
    public:
        static void setup();
        static void loop();
};