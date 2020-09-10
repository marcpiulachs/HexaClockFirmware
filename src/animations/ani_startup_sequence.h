#ifndef HEXCLOCK_ANI_STARTUP_SEQUENCE_H
#define HEXCLOCK_ANI_STARTUP_SEQUENCE_H

#include "ani_common.h"

enum ani_startup_state {
    START,
    WIFI,
    WIFI_SETUP
} typedef ani_startup_state;

class ani_startup_sequence {
    public:
        void run(CRGB* buffer);
        void setState(ani_startup_state state);
    private:
        ani_startup_state state = ani_startup_state::START;
        int16_t counter = 0;
};


#endif //HEXCLOCK_ANI_STARTUP_SEQUENCE_H
