#include "ani_wopr.h"

ani_wopr::ani_wopr() : Animation ("Wopr") 
{

}

void ani_wopr::drawBackground(CRGB *buffer) 
{
    switch (this->counter % 4)
    {
        case 0:
            fill_sprite(buffer, sprite_wopr0, CRGB::Orange, true);
            break;
        case 1:
            fill_sprite(buffer, sprite_wopr1, CRGB::Orange, true);
            break;
        case 2:
            fill_sprite(buffer, sprite_wopr2, CRGB::Orange, true);
            break;
        case 3:
            fill_sprite(buffer, sprite_wopr3, CRGB::Orange, true);
            break;
    }
 
    // Increment the sprite counter
    this->counter++;
}