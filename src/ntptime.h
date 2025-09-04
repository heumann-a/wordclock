// NTP WiFi Connection
#ifndef WORDCLOCK_TIME_H
#define WORDCLOCK_TIME_H

#include "NTPClient.h"
#include <WiFiUdp.h>

class NTPTime {
    private:
        
        static int getYear(time_t &);
        static int getMonth(time_t &);
        static int getDay(time_t &);
        
    public:
        // Var to connect to NTP
        static WiFiUDP udpNTP;
        // NTP Client initalization
        static NTPClient ntpClient;

        static int year, month, day, hour, minute;


        static void setup();
        static void loop();
};

#endif