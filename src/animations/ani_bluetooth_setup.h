#ifndef _ANI_BLUETOOTH_SETUP_H
#define _ANI_BLUETOOTH_SETUP_H

#include "animation.h"

class ani_bluetooth_setup : public Animation {
    public:
        ani_bluetooth_setup();
        void drawBackground(CRGB* buffer);
    private:
        int16_t counter = 0;
        CRGB color = CRGB::Yellow;
};


#endif //_ANI_WIFI_SETUP_H
