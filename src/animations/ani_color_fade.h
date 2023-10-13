#ifndef HEXCLOCK_ANI_COLOR_FADE_H
#define HEXCLOCK_ANI_COLOR_FADE_H

#include "animation.h"

class ani_color_fade : public Animation {
    public:
        ani_color_fade(byte brghtness);
        void drawBackground(CRGB* buffer);
        void setSpeed(byte speed);

    private:
        byte hue = 0.0;
        byte step_speed = 100;
        byte brightness = 100;
};


#endif //HEXCLOCK_ANI_COLOR_FADE_H
