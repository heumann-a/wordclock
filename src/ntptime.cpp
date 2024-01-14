#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "ntptime.h"
#include "grid.h"
#include "utcOffset.h"
#include "config.h"

void NTPTime::setup() {
    NTPTime::ntpClient.begin();
    NTPTime::ntpClient.setTimeOffset(Config::timezone);
    NTPTime::ntpClient.update();
}

void NTPTime::loop() {
    NTPTime::ntpClient.update();
    
    int h = NTPTime::ntpClient.getHours();
    int m = NTPTime::ntpClient.getMinutes();

    time_t rawtime = NTPTime::ntpClient.getEpochTime();
   
    // Check if new Minute began
    if(m != NTPTime::minute) {
        // Check for new Hour
        if(m == 0 && h == NTPTime::hour) {
            h = (++h) % 24;
        }

        NTPTime::minute = m;
        NTPTime::hour = h;

        NTPTime::month = NTPTime::getMonth(rawtime); 
        NTPTime::day = NTPTime::getDay(rawtime);

        if (Config::automatic_timezone) {
            Config::timezone = UtcOffset::getLocalizedUtcOffset();
            NTPTime::ntpClient.setTimeOffset(Config::timezone);
        }
    }

    Grid::setTime(NTPTime::month, NTPTime::day, NTPTime::hour, NTPTime::minute);
}

int NTPTime::getYear(time_t &epochtime) {
  struct tm * ti;
  ti = localtime (&epochtime);
  int year = ti->tm_year + 1900;
  
  return year;
}

int NTPTime::getMonth(time_t &epochtime) {
  struct tm * ti;
  ti = localtime (&epochtime);
  int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1);
  
  return month;
}

int NTPTime::getDay(time_t &epochtime) {
  struct tm * ti;
  ti = localtime (&epochtime);
  int day = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
  
  return day;
}

int NTPTime::hour = -1;
int NTPTime::minute = -1;
int NTPTime::day = 0;
int NTPTime::month = 0;
int NTPTime::year = 0;
WiFiUDP NTPTime::udpNTP;
NTPClient NTPTime::ntpClient = NTPClient(NTPTime::udpNTP);