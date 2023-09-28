//
// Created by samuel on 08/09/2020.
//

#include "ani_wifi_connecting.h"

ani_wifi_connecting::ani_wifi_connecting() : Animation ("WiFiConnecting") 
{
    this->counter = 0;
}

void ani_wifi_connecting::run(CRGB *buffer) {
    switch (this->counter % 4)
    {
        case 0:
            fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(255, 255, 255));
            break;
        case 1:
            fill_buffer_with_sprite(buffer, sprite_wifi1, CRGB(255, 255, 255));
            break;
        case 2:
            fill_buffer_with_sprite(buffer, sprite_wifi2, CRGB(255, 255, 255));
            break;
        case 3:
            fill_buffer_with_sprite(buffer, sprite_wifi3, CRGB(255, 255, 255));
            break;
    }
    this->counter++;
}