//
// Created by samuel on 15/09/2020.
//

#ifndef HEXCLOCK_ANNIMATION_MANAGER_H
#define HEXCLOCK_ANNIMATION_MANAGER_H

#include "animations/ani_startup_sequence.h"
#include "animations/ani_color_fade.h"
#include "animations/ani_breathing.h"
#include "animations/ani_christmas.h"

enum annimations {
    STARTUP_START = 0,
    STARTUP_WIFI = 1,
    COLORFADE = 2,
    BREATHING = 3,
    CHRISTMAS = 4
} typedef annimations;


class annimation_manager {
    public:
        annimation_manager();
        void setAnnimation(annimations annimation);
        void run(CRGB* buffer);
        void updateColorForCurrentAnimation(const CHSV& color);

    private:
        annimations current_animation;
        ani_startup_sequence *animation_startup;
        ani_color_fade *animation_color_fade;
        ani_breathing *animation_breathing;
        ani_christmas *animation_christmas;
};


#endif //HEXCLOCK_ANNIMATION_MANAGER_H
