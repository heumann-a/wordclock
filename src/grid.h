
#ifndef WORDCLOCK_GRID_H
#define WORDCLOCK_GRID_H

#include "config.h"

class Grid {

	public:

        static int time_it_is[5];
        static int time_hours[12][6];

         // Switch between Viertel vor and dreiviertel
        static int *minutes;

         // Dreiviertel
        static int alt_time_minutes[12][12];
        // Viertel vor
        static int time_minutes[12][12];

	
	    static void setTime(int hour, int minute);
        static void setLanguage(bool language_alt);
};

#endif