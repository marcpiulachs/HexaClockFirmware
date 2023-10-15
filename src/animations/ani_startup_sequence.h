#ifndef HEXCLOCK_ANI_STARTUP_SEQUENCE_H
#define HEXCLOCK_ANI_STARTUP_SEQUENCE_H

#include "animation.h"

class ani_startup_sequence : public Animation {
    public:
        ani_startup_sequence();
        void drawBackground(CRGB* buffer);
        virtual void drawClock(CRGB* buffer);
    private:
        int16_t counter = 0;
};


#endif //HEXCLOCK_ANI_STARTUP_SEQUENCE_H
