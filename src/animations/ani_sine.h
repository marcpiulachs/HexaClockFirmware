#ifndef HEXCLOCK_ANI_SINE_H
#define HEXCLOCK_ANI_SINE_H

#include "animation.h"

class ani_sine : public Animation
{
    public:
        ani_sine();
        void drawBackground(CRGB* buffer);
        void setSpeed(byte speed);
        //void setBrightness(byte brightness);
        void update_settings(byte hue, bool inverted, byte strengh);
        void updateColor(CHSV color);

    private:
        CHSV current_color = CHSV(50,255,255);
        //byte current_hue = 50;
        byte step_speed = 100;
        byte strengh = 180;
        byte brightness = 255;
        bool inverted = false;

        byte circles_lumi_offset[4] = {120,140,150,160};
        bool circles_lumi_orientation = false;
};


#endif //HEXCLOCK_ANI_SINE_H
