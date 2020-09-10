//
// Created by samuel on 10/09/2020.
//

#include "ani_breathing.h"

ani_breathing::ani_breathing(byte brightness, byte hue, bool inverted, byte strengh) {
    this->brightness = brightness;
    this->current_hue = hue;
    this->inverted = inverted;
    this->strengh = strengh;
}

void ani_breathing::update_brightness(byte b) {
    this->brightness = b;

}

void ani_breathing::update_settings(byte hue, bool i, byte s) {
    this->current_hue = hue;
    this->inverted = i;
    this->strengh = s;
}

void ani_breathing::set_speed(byte speed) {
    this->step_speed = speed;
}

void ani_breathing::run(CRGB *buffer) {
    for (int i = 0; i < 3; ++i) {
        byte a = this->circles_lumi_offset[i] + 20;
        if(a < 50) //NB: 100 is arbitrary just need to detect the overflow
            this->circles_lumi_offset[i+1] = 255;
        else
            this->circles_lumi_offset[i+1] = this->circles_lumi_offset[i] + 20;
    }
    Serial.printf("%d\t%d\t%d\t%d\n",this->circles_lumi_offset[0],this->circles_lumi_offset[1],this->circles_lumi_offset[2],this->circles_lumi_offset[3]);

    if(this->circles_lumi_orientation) {
        this->circles_lumi_offset[0] += this->step_speed/10;
    } else {
        this->circles_lumi_offset[0] += this->step_speed/10 * -1;
    }

    if(this->circles_lumi_offset[0]>215 || this->circles_lumi_offset[0] < (255-this->strengh))
        this->circles_lumi_orientation = !this->circles_lumi_orientation;

    for (int i = 0; i <4; ++i) {
        byte lumi = this->circles_lumi_offset[i];
        if(this->inverted)
            lumi = 255-this->circles_lumi_offset[i];

        switch (i) {
            case 3:
                fill_buffer_with_sprite_without_override(buffer,sprite_ring3,CHSV(this->current_hue, 255, qsub8(lumi,255-this->brightness )));
                break;
            case 2:
                fill_buffer_with_sprite_without_override(buffer,sprite_ring2,CHSV(this->current_hue, 255, qsub8(lumi,255-this->brightness )));
                break;
            case 1:
                fill_buffer_with_sprite_without_override(buffer,sprite_ring1,CHSV(this->current_hue, 255, qsub8(lumi,255-this->brightness )));
                break;
            case 0:
                fill_buffer_with_sprite_without_override(buffer,sprite_ring0,CHSV(this->current_hue, 255, qsub8(lumi,255-this->brightness )));
                break;
        }
    }
}
