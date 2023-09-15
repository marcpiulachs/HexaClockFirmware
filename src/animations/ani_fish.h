//
// Created by samuel on 16/09/2020.
//

#ifndef HEXCLOCK_ANI_FISH_H
#define HEXCLOCK_ANI_FISH_H

#include "animation.h"
#include "ani_common.h"

class ani_fish : public Animation {
    public:
        ani_fish(byte brightness, bool orientation, CHSV color, char accent_color);
        void run(CRGB* buffer);
        void set_speed(byte speed);
        void updateColor(CHSV color);

    private:
        CHSV color = CHSV(0,255,255);
        bool orientation = true;
        char accent_color = 'g';

        uint16_t stepper = 0;
        uint16_t speed = 100;
        uint8_t fish_matrix[120] = {
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
        };
        uint8_t luminance_buffer[192] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 127, 127, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25};
};


#endif //HEXCLOCK_ANI_FISH_H
