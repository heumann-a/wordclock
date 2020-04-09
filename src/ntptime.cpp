#include "ntptime.h"

void NTPTime::setup() {
    NTPTime::ntpClient.begin();
    NTPTime::ntpClient.update();
    // NTPTime::ntpClient.setTimeOffset();
}

void NTPTime::loop() {
    NTPTime::ntpClient.update();
    
    int h = NTPTime::ntpClient.getHours() || -1;
    int m = NTPTime::ntpClient.getMinutes() || -1;

    // Check if new Minute began
    if(m != NTPTime::minute) {
        // Check for new Hour
        if(m == 0 && h == NTPTime::hour) {
            h = (++h) % 24;
        }

        NTPTime::minute = m;
        NTPTime::hour = h;

        //Set GridTime
    }
}

int NTPTime::hour = -1;
int NTPTime::minute = -1;
WiFiUDP NTPTime::udpNTP;
NTPClient NTPTime::ntpClient = NTPClient(NTPTime::udpNTP);