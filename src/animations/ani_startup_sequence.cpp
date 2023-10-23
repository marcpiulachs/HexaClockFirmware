#include "ani_startup_sequence.h"

ani_startup_sequence::ani_startup_sequence() : Animation ("Startup") 
{

}

void ani_startup_sequence::drawClock(CRGB *buffer)
{
    // No clock
}

void ani_startup_sequence::setSpeed(byte speed)
{
    this->speed = map(speed, 0, 255, 0, 1024);
}

void ani_startup_sequence::drawBackground(CRGB *buffer) 
{
    switch (this->counter % 4)
    {
        case 0:
            fill_sprite(buffer, sprite_ring0, CRGB::Yellow, true);
            break;
        case 1:
            fill_sprite(buffer, sprite_ring1, CRGB::Green, true);
            break;
        case 2:
            fill_sprite(buffer, sprite_ring2, CRGB::Orange, true);
            break;
        case 3:
            fill_sprite(buffer, sprite_ring3, CRGB::Red, true);
            break;
    }
    this->counter++;
 
    /*
    if(this->state == ani_startup_state::WIFI) {
        byte c = 5*(this->counter % 25);
        if(c>63) c=127-c;
        c=(c*3)/5;
        fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(100,100,100).subtractFromRGB(c));
    }
    if(this->state == ani_startup_state::WIFI_SETUP) {
        fill_buffer_with_sprite(buffer, sprite_wifi0, CRGB(25,25,255));
    }*/
}