//
// Created by samuel on 10/09/2020.
//

#ifndef HEXCLOCK_ANI_CHRISTMAS_H
#define HEXCLOCK_ANI_CHRISTMAS_H

#include "animation.h"

extern byte points_grass[22];

class ani_christmas : public Animation {
    public:
        ani_christmas(byte brightness, const CRGB& flake_colors, CRGB bg_color);
        void run(CRGB* buffer);
        void setSpeed(byte speed);
        void setBrightness(byte brightness);

    private:
        void spawn_flakes();
        void fall_flakes();

        CRGB flake_colors = CRGB(255,0,100);
        CRGB bg_color = CRGB(200,0,20);
        byte step_speed = 100;
        byte step_counter = 0;
        byte brightness = 255;
        byte snowflake_count = 0;
        bool snowflake_matrix[15][8] = {};
};

#endif //HEXCLOCK_ANI_CHRISTMAS_H
