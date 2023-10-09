//
// Created by samuel on 08/09/2020.
//

#include "ani_wopr.h"

ani_wopr::ani_wopr() : Animation ("Wopr") 
{

}

void ani_wopr::run(CRGB *buffer) {
    switch (this->counter % 4)
    {
        case 0:
            fill_buffer_with_sprite(buffer, sprite_wopr0, CRGB::Orange);
            break;
        case 1:
            fill_buffer_with_sprite(buffer, sprite_wopr1, CRGB::Orange);
            break;
        case 2:
            fill_buffer_with_sprite(buffer, sprite_wopr2, CRGB::Orange);
            break;
        case 3:
            fill_buffer_with_sprite(buffer, sprite_wopr3, CRGB::Orange);
            break;
    }
    this->counter++;
}