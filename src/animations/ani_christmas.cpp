//
// Created by samuel on 10/09/2020.
//

#include "ani_christmas.h"

byte point_grass[22] = { 21,20,18,19,17,16,14,15,13,28,7,8,9,10,11,12,6,5,4,3,2,1};

ani_christmas::ani_christmas(byte brightness, const CRGB& flake_colors, const CRGB bg_color) : Animation ("Christmas") {
    this->brightness = brightness;
    this->flake_colors = flake_colors;
    this->bg_color = bg_color;
}

void ani_christmas::setSpeed(byte speed) {
    this->step_speed = speed;
}

void ani_christmas::setBrightness(byte brightness) {
    this->brightness = brightness;
}

void ani_christmas::spawn_flakes() {
    byte x = random8(7);
    byte y = 0;
    while(pixel_map[y][x] == 0)
        y++;
    if(this->snowflake_matrix[y][x] == true)
        this->spawn_flakes();
    else {
        this->snowflake_matrix[y][x] = true;
        this->snowflake_count ++;
    }
}

void ani_christmas::fall_flakes() {
    for (int y = 12; y > 0; y--) {
        for (int x = 0; x < 8; ++x) {
            if(this->snowflake_matrix[y-1][x] == true) {
                this->snowflake_matrix[y-1][x] = false;
                if(y<12)
                    this->snowflake_matrix[y][x] =true;
                else
                    this->snowflake_count--;

            }
        }
    }
}

//TODO: Add brightness control
void ani_christmas::run(CRGB *buffer) {
    //CRGB color_diff = CRGB(255-this->brightness,255-this->brightness,255-this->brightness);
    for (int i = 0; i < 22; ++i) {
        buffer[point_grass[i]-1] = CRGB(0,150,0);
    }

    while(this->snowflake_count<4)
        this->spawn_flakes();

    if(this->step_counter>100) {
        this->fall_flakes();
        this->step_counter = 0;
    }

    this->step_counter += this->step_speed;

    for (int y = 0; y < 12; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(this->snowflake_matrix[y][x] == true)
                buffer[pixel_map[y][x]-1] = this->flake_colors;
            else
                buffer[pixel_map[y][x]-1] = this->bg_color;
        }
    }
}