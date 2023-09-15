//
// Created by samuel on 08/09/2020.
//

#include "ani_startup_sequence.h"

ani_startup_sequence::ani_startup_sequence() : Animation ("Startup") {
}

void ani_startup_sequence::run(CRGB *buffer) {
    if(this->state == ani_startup_state::START) {
        switch ( this->counter%4 ) {
            case 0:
                fill_buffer_with_sprite(buffer,sprite_ring0, CRGB(255,255,255));
                break;
            case 1:
                fill_buffer_with_sprite(buffer,sprite_ring1, CRGB(255,255,255));
                break;
            case 2:
                fill_buffer_with_sprite(buffer,sprite_ring2, CRGB(255,255,255));
                break;
            case 3:
                fill_buffer_with_sprite(buffer,sprite_ring3, CRGB(255,255,255));
                break;
        }
    }
    if(this->state == ani_startup_state::WIFI) {
        byte c = 5*(this->counter % 25);
        if(c>63) c=127-c;
        c=(c*3)/5;
        fill_buffer_with_sprite(buffer, sprite_wifi, CRGB(100,100,100).subtractFromRGB(c));
    }
    if(this->state == ani_startup_state::WIFI_SETUP) {
        fill_buffer_with_sprite(buffer, sprite_wifi, CRGB(25,25,255));
    }
    this->counter++;
}

void ani_startup_sequence::setState(ani_startup_state state) {
    this->state = state;
    this->counter = 0;
}