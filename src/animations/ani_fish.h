//
// Created by samuel on 16/09/2020.
//

#ifndef HEXCLOCK_ANI_FISH_H
#define HEXCLOCK_ANI_FISH_H

#include "animation.h"

class ani_fish : public Animation {
    public:
        ani_fish();
        void drawBackground(CRGB* buffer);
    private:
        uint8_t hue = 0;
};


#endif //HEXCLOCK_ANI_FISH_H
