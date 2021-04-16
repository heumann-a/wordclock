#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "ntptime.h"
#include "grid.h"
#include "utcOffset.h"

void NTPTime::setup() {
    NTPTime::ntpClient.begin();
    NTPTime::ntpClient.update();
}

void NTPTime::loop() {
    NTPTime::ntpClient.update();
    
    int h = NTPTime::ntpClient.getHours();
    int m = NTPTime::ntpClient.getMinutes();

    // Check if new Minute began
    if(m != NTPTime::minute) {
        // Check for new Hour
        if(m == 0 && h == NTPTime::hour) {
            h = (++h) % 24;
        }

        NTPTime::minute = m;
        NTPTime::hour = h;

        Grid::setTime(NTPTime::hour, NTPTime::minute);

        if (Config::automatic_timezone) {
            Config::timezone = UtcOffset::getLocalizedUtcOffset();
            NTPTime::ntpClient.setTimeOffset(Config::timezone);
        }
    }
}

int NTPTime::hour = -1;
int NTPTime::minute = -1;
WiFiUDP NTPTime::udpNTP;
NTPClient NTPTime::ntpClient = NTPClient(NTPTime::udpNTP);