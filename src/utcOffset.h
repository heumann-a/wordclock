#ifndef WORDCLOCK_UTC_OFFSET_H
#define WORDCLOCK_UTC_OFFSET_H
#include <Timezone.h>

class UtcOffset {
  private:

    static TimeChangeRule CEST;     // Central European Summer Time
    static TimeChangeRule CET;       // Central European Standard Time
    static Timezone CE;

  public:
    static int getLocalizedUtcOffset();
};

#endif
