//
// Created by samuel on 15/09/2020.
//

#include "display.h"

Display::Display() {
    this->animation_startup    = new ani_startup_sequence();
    this->animation_color_fade = new ani_color_fade(120);
    this->animation_breathing  = new ani_breathing(255,50,false,200);
    this->animation_christmas  = new ani_christmas(50,CRGB(255,0,100),CRGB(200,0,20));

    this->current_animation = annimations::STARTUP_START;
    this->animation_startup->setState(ani_startup_state::START);
}

void Display::setAnnimation(annimations annimation) {
    this->current_animation = annimation;
    switch (this->current_animation) {
        case STARTUP_START:
            this->animation_startup->setState(ani_startup_state::START);
            break;
        case STARTUP_WIFI:
            this->animation_startup->setState(ani_startup_state::WIFI);
            break;
        case COLORFADE:
            this->animation_color_fade->set_speed(100);
            break;
        case BREATHING:
            this->animation_breathing->set_speed(10);
            break;
        case CHRISTMAS:
            this->animation_christmas->set_speed(10);
            break;
    }
}

void Display::updateColor(const CHSV& color) {
    switch (this->current_animation) {
        case STARTUP_START:
        case STARTUP_WIFI:
            break;
        case COLORFADE:
            break;
        case BREATHING:
            this->animation_breathing->updateColor(color);
            break;
        case CHRISTMAS:
            break;
    }
}

void Display::run(CRGB * buffer) {
    switch (this->current_animation) {
        case STARTUP_START:
        case STARTUP_WIFI:
            this->animation_startup->run(buffer);
            break;
        case COLORFADE:
            this->animation_color_fade->run(buffer);
            break;
        case BREATHING:
            this->animation_breathing->run(buffer);
            break;
        case CHRISTMAS:
            this->animation_christmas->run(buffer);
            break;
    }
}
