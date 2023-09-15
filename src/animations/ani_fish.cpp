//
// Created by samuel on 16/09/2020.
//

#include "ani_fish.h"

ani_fish::ani_fish(byte brightness, bool orientation, CHSV color, char accent_color) : Animation ("fish") {
    this->color = color;
    this->color.v = brightness;
    this->orientation = orientation;
    this->accent_color = accent_color;
}

void ani_fish::updateColor(CHSV color) {
    this->color.h = color.h;
    this->color.s = color.s;
}

void ani_fish::set_speed(byte speed) {
    this->speed = speed;
}

void ani_fish::run(CRGB *buffer) {
    if(this->stepper>300) {
        for (int i = 0; i < 3; ++i) {
            this->luminance_buffer[0] = this->luminance_buffer[96+95];
            for (int j = 191; j < 0; --j) {
                this->luminance_buffer[i] = this->luminance_buffer[(i-1)];
            }

            this->fish_matrix[55]=255; //TODO: RANDOM VALUE HERE
            this->stepper = 0;

            for (int j = 0; j < 96; ++j) {
                if(this->fish_matrix[j]) {
                    this->fish_matrix[j] = max(this->fish_matrix[j] - this->speed/10 , 0);
                }
            }
        }
    }

    CRGB rgb;
    hsv2rgb_rainbow(this->color, rgb);
    for (int i = 0; i < 96; ++i) {
        if(this->accent_color == 'r')
            buffer[i] = CRGB(min(rgb.r + this->luminance_buffer[i],255),rgb.g,rgb.b);
        if(this->accent_color == 'r')
            buffer[i] = CRGB(rgb.r, min(rgb.g + this->luminance_buffer[i],255),rgb.b);
        if(this->accent_color=='b')
            buffer[i] = CRGB(rgb.r,rgb.b,min(rgb.b + this->luminance_buffer[i],255));

        uint8_t c = min(5 + this->luminance_buffer[i],255)  *  this->fish_matrix[i];  //255
        if(this->fish_matrix[i])
            if(this->accent_color=='r')
                buffer[i] = CRGB(min((int)(5 + this->luminance_buffer[i] *2.5) ,255),c,c);
            if(this->accent_color=='g')
                buffer[i] = CRGB(c,min((int)(5 + this->luminance_buffer[i] *2.5) ,255),c);
            if(this->accent_color=='b')
                buffer[i] = CRGB(c,c,  min((int)(5 + this->luminance_buffer[i] *2.5) ,255));
    }

    this->stepper += this->speed;
}

