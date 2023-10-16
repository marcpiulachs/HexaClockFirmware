#include "ani_wifi_connecting.h"

ani_wifi_connecting::ani_wifi_connecting() : Animation ("WiFiConnecting") 
{
    this->counter = 0;
}

void ani_wifi_connecting::drawBackground(CRGB *buffer) {
    static uint8_t frame = 0;
    if( frame % 50 == 0 ) 
    {
        switch (this->counter % 4)
        {
            case 0:
                fill_sprite(buffer, sprite_wifi0, CRGB::Blue, true);
                break;
            case 1:
                fill_sprite(buffer, sprite_wifi1, CRGB::Blue, true);
                break;
            case 2:
                fill_sprite(buffer, sprite_wifi2, CRGB::Blue, true);
                break;
            case 3:
                fill_sprite(buffer, sprite_wifi3, CRGB::Blue, true);
                break;
        }
        this->counter++;
    }
    frame++;
}