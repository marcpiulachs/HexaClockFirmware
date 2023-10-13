#ifndef _PLASMA_H
#define _PLASMA_H

#include "animation.h"

class ani_plasma : public Animation {
    public:
        ani_plasma();
        void drawBackground(CRGB* buffer);
    private:
    uint16_t _plasmaShift = (random8(0, 5) * 32) + 64;
    uint16_t _plasmaTime = 0;
    const uint8_t _plasmaXfactor = 8;
    const uint8_t _plasmaYfactor = 8;
};


#endif //_PLASMA_H
