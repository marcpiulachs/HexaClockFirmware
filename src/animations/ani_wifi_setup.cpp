//
// Created by samuel on 08/09/2020.
//

#include "ani_wifi_setup.h"

ani_wifi_setup::ani_wifi_setup() : Animation ("WiFiSetup") 
{
    this->counter = 0;
}

void ani_wifi_setup::run(CRGB *buffer) {
    switch (this->counter % 4)
    {
        case 0:
            fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(0, 0, 153));
            break;
        case 1:
            fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(0, 0, 255));
            break;
        case 2:
            fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(51, 51, 255));
            break;
        case 3:
            fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(102, 102, 255));
            break;
    }
    this->counter++;
}