//
// Created by samuel on 10/09/2020.
//

#include "ani_color_fade.h"

ani_color_fade::ani_color_fade(byte brightness) : Animation ("Fade") {
    this->brightness = brightness;
}

void ani_color_fade::drawBackground(CRGB *buffer) 
{
    this->hue += this->step_speed / 100.0;
    
    if (this->hue > 255)
        this->hue = 0;

    fill_solid(buffer, NUM_LEDS, CHSV(this->hue, 255, this->brightness));
}

void ani_color_fade::setSpeed(byte speed) {
    this->step_speed = speed;
}
