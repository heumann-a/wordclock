#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

#include "utcOffset.h"
#include "config.h"

int UtcOffset::getLocalizedUtcOffset() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://worldtimeapi.org/api/ip");
  int responseCode = http.GET();

  // Only accept Successfull Responses
  if ( (responseCode >= 200) && (responseCode <= 299)) {
    String payload = http.getString();

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload);

    int utcOffset = doc["raw_offset"].as<int>();
    int dstOffset = doc["dst_offset"].as<int>();

    http.end();
    return utcOffset + dstOffset;
  }
  http.end();

  return Config::timezone; // return last known offset
}
