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
#include "animations/ani_wifi_setup.h"
#include "animations/ani_wifi_connecting.h"
#include "animations/ani_fish.h"
#include "animations/ani_wopr.h"
#include "animations/ani_bluetooth_setup.h"

#define NUM_LEDS 96
#define DATA_PIN 27

enum annimations {
    STARTUP_START = 0,
    STARTUP_WIFI = 1,
    SETUP_WIFI = 14,
    SETUP_BLUETOOTH = 16,
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
    WOPR = 15,
} typedef annimations;

class Display {
    public:
        Display();
        void setup();
        void draw();
        void setAnnimation(annimations annimation);
        void setSpeed(byte speed);
        void setBrightness(byte brightness);
        void setTime(bool value);
        void setBackground(bool value);
        void setInvert(bool value);
    private:
        annimations current_animation;
        CRGB output_buffer [NUM_LEDS];
        byte brightness = 1;
    protected:
        Animation* animation = new ani_startup_sequence();
};

#endif //_DISPLAY_H
