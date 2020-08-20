// NTP WiFi Connection
#ifndef WORDCLOCK_TIME_H
#define WORDCLOCK_TIME_H

#include <NTPClient.h>
#include <WiFiUdp.h>

class NTPTime {
    public:
        // Var to connect to NTP
        static WiFiUDP udpNTP;
        // NTP Client initalization
        static NTPClient ntpClient;

        static int hour;
        static int minute;

        static void setup();
        static void loop();
};

#endif