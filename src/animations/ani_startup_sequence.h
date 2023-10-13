#ifndef HEXCLOCK_ANI_STARTUP_SEQUENCE_H
#define HEXCLOCK_ANI_STARTUP_SEQUENCE_H

#include "animation.h"

class ani_startup_sequence : public Animation {
    public:
        ani_startup_sequence();
        void drawBackground(CRGB* buffer);
        //void setState(ani_startup_state state);
    private:
        //ani_startup_state state = ani_startup_state::START;
        int16_t counter = 0;
};


#endif //HEXCLOCK_ANI_STARTUP_SEQUENCE_H
