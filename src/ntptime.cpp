#include "ntptime.h"

void NTPTime::setup() {
    NTPTime::ntpClient.begin();
    NTPTime::ntpClient.update();
}

void NTPTime::loop() {
    NTPTime::ntpClient.update();
    // ...
}


WiFiUDP NTPTime::udpNTP;
NTPClient NTPTime::ntpClient = NTPClient(NTPTime::udpNTP);