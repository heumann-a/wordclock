#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

#include "utcOffset.h"
#include "ntptime.h"
#include "config.h"


int UtcOffset::getLocalizedUtcOffset() {

  time_t utctime = NTPTime::ntpClient.getUTCEpochTime();

  if (UtcOffset::CE.utcIsDST(utctime)) { 
    Config::timezone = 7200;
  } else {
    Config::timezone = 3600;
  }

  return Config::timezone; // return last known offset
}

TimeChangeRule UtcOffset::CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Central European Summer Time
TimeChangeRule UtcOffset::CET = {"CET ", Last, Sun, Oct, 3, 60};       // Central European Standard Time
Timezone UtcOffset::CE(UtcOffset::CEST, UtcOffset::CET);