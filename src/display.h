#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "animations/ani_startup_sequence.h"
#include "animations/ani_color_fade.h"
#include "animations/ani_breathing.h"
#include "animations/ani_christmas.h"
#include "animations/ani_fibonacci.h"
#include "animations/ani_pride.h"
#include "animations/ani_rain.h"
#include "animations/ani_fire.h"
#include "animations/ani_plasma.h"
#include "animations/ani_sine.h"
#include "animations/ani_swirl.h"
#include "animations/ani_wifi_setup.h"
#include "animations/ani_wifi_connecting.h"
#include "animations/ani_fish.h"
#include "animations/ani_wopr.h"
#include "animations/ani_proton.h"

enum annimations {
    STARTUP_START = 0,
    STARTUP_WIFI = 1,
    SETUP_WIFI = 14,
    COLORFADE = 2,
    BREATHING = 3,
    CHRISTMAS = 4,
    FIBONACCI = 5,
    FIRE = 6,
    FISH= 7,
    PLASMA = 8,
    PRIDE = 9,
    RAIN = 10,
    SINE = 12,
    SWIRL = 13,
    WOPR = 15,
    PROTON = 16
} typedef annimations;


class Display {
    public:
        Display();
        void setAnnimation(annimations annimation);
        void run(CRGB* buffer);
        void updateColor(const CHSV& color);

    private:
        annimations current_animation;
    protected:
        Animation* animation = new ani_startup_sequence();
        /*
        ani_startup_sequence *animation_startup;
        ani_color_fade *animation_color_fade;
        ani_breathing *animation_breathing;
        ani_christmas *animation_christmas;*/
};


#endif //_DISPLAY_H
