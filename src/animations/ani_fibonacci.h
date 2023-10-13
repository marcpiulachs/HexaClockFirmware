#ifndef HEXCLOCK_ANI_FIBONACCI_H
#define HEXCLOCK_ANI_FIBONACCI_H

#include "animation.h"

static const uint16_t FibonPlanarTable[]={
     205, 226, 192, 256, 179, 200, 221, 242,
     256, 171, 137, 158, 124, 145, 166, 187, 
     150, 116, 256, 103, 256, 111, 132, 153,
     129, 95, 82, 69, 90, 77, 98, 119, 
     74, 61, 48, 256, 56, 256, 64, 85, 
     53, 40, 27, 35, 256, 43, 51, 72, 
     256, 32, 19, 14, 22, 30, 38, 59,
     45, 256, 11, 6, 9, 17, 25, 46, 
     37, 24, 3, 256, 1, 4, 12, 33, 
     29, 16, 8, 0, 2, 7, 20, 41, 
     42, 21, 13, 5, 256, 15, 28, 256, 
     55, 34, 26, 18, 10, 23, 36, 49, 
      8, 47, 256, 39, 31, 44, 57, 70, 
     256, 256, 60, 256, 52, 65, 78, 91, 
     102, 81, 94, 73, 86, 256, 99, 112,
};

class ani_fibonacci : public Animation
{
    public:
        ani_fibonacci();
        void drawBackground(CRGB* buffer);
        void setSpeed(byte speed);
        //void update_brightness(byte brightness);
        //void update_settings(byte hue, bool inverted, byte strengh);
        //void updateColor(CHSV color);

    private:
        CHSV current_color = CHSV(50,255,255);
        //byte current_hue = 50;
        byte step_speed = 100;
        byte strengh = 180;
        //byte brightness = 255;
        bool inverted = false;

        byte circles_lumi_offset[4] = {120,140,150,160};
        bool circles_lumi_orientation = false;
};


#endif //HEXCLOCK_ANI_FIBONACCI_H
