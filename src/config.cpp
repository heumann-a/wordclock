#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config.h"
#include "ntptime.h"
#include "types.h"
#include "led.h"
#include "utcOffset.h"


void Config::save() {
  File file = LittleFS.open("/wordclock_config.json", "w");

  if(!file) {
    Serial.println("Can't open wordclock_config.json for writing");
    return;
  }

  NTPTime::ntpClient.setPoolServerName(Config::ntp.c_str());
  NTPTime::ntpClient.setTimeOffset(Config::timezone);

  StaticJsonDocument<1024> doc;
  doc["color_bg_r"] = Config::color_bg.r;
  doc["color_bg_g"] = Config::color_bg.g;
  doc["color_bg_b"] = Config::color_bg.b;
  doc["color_fg_r"] = Config::color_fg.r;
  doc["color_fg_g"] = Config::color_fg.g;
  doc["color_fg_b"] = Config::color_fg.b;
  doc["power_supply"] = Config::power_supply;
  doc["brightness"] = Config::brightness;
  doc["tz_auto"] = Config::automatic_timezone;
  doc["timezone"] = Config::timezone;
  doc["language_alt"] = Config::language_de_alt;
  doc["dnd_active"] = Config::dnd_active;
  doc["dnd_start_hour"] = Config::dnd_start.hour;
  doc["dnd_start_minute"] = Config::dnd_start.minute;
  doc["dnd_end_hour"] = Config::dnd_end.hour;
  doc["dnd_end_minute"] = Config::dnd_end.minute;
  doc["ntp"] = Config::ntp;

  serializeJson(doc, file);

  file.close();
  Serial.println("Config saved.");
}

void Config::load() {

  // Load Default Values
  Config::color_bg.r = 0;
  Config::color_bg.g = 0;
  Config::color_bg.b = 0;

  Config::color_fg.r = 255;
  Config::color_fg.g = 255;
  Config::color_fg.b = 255;

  Config::power_supply = 500; // default: 500mA (USB 2.0 specification)
  Config::brightness = 0.5;

  Config::automatic_timezone = true;
  Config::timezone = 3600; // in Seconds  -  1 hours Offset for Germany WinterTime

  Config::language_de_alt = true; // defaulting to alternative Spelling (dreiviertel)

  Config::dnd_active = false;
  Config::dnd_start.hour = -1;
  Config::dnd_start.minute = -1;
  Config::dnd_end.hour = -1;
  Config::dnd_end.minute = -1;
  Config::ntp = "europe.pool.ntp.org";

  // Open saved Config from File
  File file = LittleFS.open("/wordclock_config.json", "r");

  if(!file) {
    Serial.println("Failed to open config file.");
    Config::save();
    return;
  }

  Serial.println("Load config.");

  StaticJsonDocument<1024> doc;
  deserializeJson(doc, file);

  // Colour Settings
  // Background Color
  Config::color_bg.r = doc["color_bg_r"].as<int>();
  Config::color_bg.g = doc["color_bg_g"].as<int>();
  Config::color_bg.b = doc["color_bg_b"].as<int>();
  //Foreground Color
  Config::color_fg.r = doc["color_fg_r"].as<int>();
  Config::color_fg.g = doc["color_fg_g"].as<int>();
  Config::color_fg.b = doc["color_fg_b"].as<int>();

  // Power Supply Power
  if(doc["power_supply"]) {
    Config::power_supply = doc["power_supply"].as<int>();
  }

  if(doc["brightness"]) {
    Config::brightness =
      (doc["brightness"].as<double>() > Led::getMaxBrightnessPercnt()) ? Led::getMaxBrightnessPercnt() : doc["brightness"].as<double>();
  }

  // AutoTimezone Active 
  if (doc["tz_auto"]) {
    Config::automatic_timezone = doc["tz_auto"].as<bool>();
  }

  if (Config::automatic_timezone) {
    Config::timezone = UtcOffset::getLocalizedUtcOffset();
  } else {
    Config::timezone = doc["timezone"].as<int>();
  }

  Config::language_de_alt = doc["language_alt"].as<bool>();


  // Do Not Disturb Settings
  Config::dnd_active = doc["dnd_active"].as<bool>();
  Config::dnd_start.hour = doc["dnd_start_hour"].as<int>();
  Config::dnd_start.minute = doc["dnd_start_minute"].as<int>();
  Config::dnd_end.hour = doc["dnd_end_hour"].as<int>();
  Config::dnd_end.minute = doc["dnd_end_minute"].as<int>();

  // NTP Pool 
  if(doc["ntp"]) {
    Config::ntp = doc["ntp"].as<String>();
  }

  NTPTime::ntpClient.setPoolServerName(Config::ntp.c_str());
  NTPTime::ntpClient.setTimeOffset(Config::timezone);
  
  file.close();
  Serial.println("Config loaded.");
}

color_t Config::color_bg{};
color_t Config::color_fg{};
int Config::power_supply{};
double Config::brightness{};
bool Config::automatic_timezone{};
bool Config::language_de_alt{};
int Config::timezone{};
bool Config::dnd_active{};
clock_time_t Config::dnd_start{};
clock_time_t Config::dnd_end{};
String Config::ntp{};
