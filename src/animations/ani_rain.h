#ifndef HEXCLOCK_ANI_RAIN_H
#define HEXCLOCK_ANI_RAIN_H

#include "animation.h"

#define NUM_ROWS 15
#define NUM_COLS 8
#define BRIGHTNESS 255
//#define NUM_LEDS NUM_ROWS * NUM_COLS

class ani_rain : public Animation
{
    public:
        ani_rain();
        void drawBackground(CRGB* buffer);
        void setSpeed(byte speed);
        //void setBrightness(byte brightness);
        void update_settings(byte hue, bool inverted, byte strengh);
        void updateColor(CHSV color);

    private:
        void changepattern ();
        uint16_t updaterain();
        void raininit();
        byte rain[NUM_LEDS];
        CHSV current_color = CHSV(50,255,255);
        //byte current_hue = 50;
        byte step_speed = 100;
        byte strengh = 180;
        byte brightness = 255;
        bool inverted = false;

        byte circles_lumi_offset[4] = {120,140,150,160};
        bool circles_lumi_orientation = false;
};


#endif //HEXCLOCK_ANI_RAIN_H
