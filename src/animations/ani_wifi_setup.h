#ifndef _ANI_WIFI_SETUP_H
#define _ANI_WIFI_SETUP_H

#include "animation.h"

class ani_wifi_setup : public Animation {
    public:
        ani_wifi_setup();
        void drawBackground(CRGB* buffer);
        virtual void drawClock(CRGB* buffer);
    private:
        int16_t counter = 0;
};


#endif //_ANI_WIFI_SETUP_H
