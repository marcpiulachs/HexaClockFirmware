//
// Created by samuel on 10/09/2020.
//

#include "ani_color_fade.h"

ani_color_fade::ani_color_fade(byte brightness) {
    this->brightness = brightness;
}

void ani_color_fade::run(CRGB *buffer) {
    this->current_hue += this->step_speed/100.0;
    if (this->current_hue>255 ) this->current_hue=0;
    fill_solid(buffer,96,CHSV((byte)this->current_hue, 255, this->brightness));
}

void ani_color_fade::set_speed(byte speed) {
    this->step_speed = speed;
}
