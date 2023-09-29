#ifndef HEXCLOCK_ANI_FIBONACCI_H
#define HEXCLOCK_ANI_FIBONACCI_H

#include "animation.h"

static const uint16_t FibonPlanarTable[]={
    256, 256, 256, 256, 256, 256, 256, 256, 247, 213, 234, 255, 256, 256, 256, 256, 256, 256, 256, 256,
    256, 256, 256, 256, 256, 239, 205, 226, 192, 256, 179, 200, 221, 242, 256, 256, 256, 256, 256, 256,
    256, 256, 256, 256, 218, 184, 256, 171, 137, 158, 124, 145, 166, 187, 208, 229, 256, 256, 256, 256,
    256, 256, 256, 252, 197, 163, 150, 116, 256, 103, 256, 111, 132, 153, 174, 195, 250, 256, 256, 256,
    256, 256, 231, 176, 142, 256, 129, 95, 82, 69, 90, 77, 98, 119, 140, 161, 216, 237, 256, 256,
    256, 244, 210, 155, 121, 108, 74, 61, 48, 256, 56, 256, 64, 85, 106, 127, 182, 203, 256, 256,
    256, 223, 189, 134, 100, 87, 53, 40, 27, 35, 256, 43, 51, 72, 93, 114, 148, 169, 224, 256,
    256, 202, 168, 113, 79, 66, 256, 32, 19, 14, 22, 30, 38, 59, 80, 256, 135, 256, 190, 245,
    236, 181, 147, 92, 256, 58, 45, 256, 11, 6, 9, 17, 25, 46, 256, 101, 256, 156, 256, 211,
    215, 160, 126, 256, 71, 256, 37, 24, 3, 256, 1, 4, 12, 33, 67, 256, 122, 256, 177, 232,
    249, 194, 139, 105, 256, 50, 29, 16, 8, 0, 2, 7, 20, 41, 54, 88, 256, 143, 198, 253,
    228, 173, 256, 118, 84, 63, 42, 21, 13, 5, 256, 15, 28, 256, 62, 75, 109, 164, 219, 256,
    256, 207, 152, 256, 97, 76, 55, 34, 26, 18, 10, 23, 36, 49, 83, 96, 130, 185, 240, 256,
    256, 241, 186, 131, 110, 89, 68, 47, 256, 39, 31, 44, 57, 70, 104, 117, 151, 206, 256, 256,
    256, 256, 220, 165, 144, 256, 256, 256, 60, 256, 52, 65, 78, 91, 125, 138, 172, 227, 256, 256,
    256, 256, 254, 199, 178, 123, 102, 81, 94, 73, 86, 256, 99, 112, 146, 159, 193, 248, 256, 256,
    256, 256, 256, 233, 212, 157, 136, 115, 128, 107, 256, 120, 133, 167, 256, 180, 214, 256, 256, 256,
    256, 256, 256, 256, 256, 191, 170, 149, 256, 162, 141, 154, 188, 256, 201, 235, 256, 256, 256, 256,
    256, 256, 256, 256, 256, 246, 225, 204, 183, 196, 175, 209, 256, 222, 256, 256, 256, 256, 256, 256,
    256, 256, 256, 256, 256, 256, 256, 238, 217, 251, 230, 256, 243, 256, 256, 256, 256, 256, 256, 256 
};

class ani_fibonacci : public Animation
{
    public:
        ani_fibonacci();
        void run(CRGB* buffer);
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
