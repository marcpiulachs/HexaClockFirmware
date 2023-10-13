#ifndef HEXCLOCK_ANI_WIFI_CONNECTING_H
#define HEXCLOCK_ANI_WIFI_CONNECTING_H

#include "animation.h"

class ani_wifi_connecting : public Animation {
    public:
        ani_wifi_connecting();
        void drawBackground(CRGB* buffer);
    private:
        int16_t counter = 0;
};


#endif //HEXCLOCK_ANI_WIFI_CONNECTING_H
