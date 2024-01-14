#ifndef WORDCLOCK_OTA_H
#define WORDCLOCK_OTA_H

#include <ArduinoOTA.h>

class OTAUpdate {
    public:
        static ArduinoOTAClass ArduinoOTA;

        static void setup();
        static void loop();
};

#endif