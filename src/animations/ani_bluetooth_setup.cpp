#include "ani_bluetooth_setup.h"

ani_bluetooth_setup::ani_bluetooth_setup() : Animation ("Bluetooth") 
{

}

void ani_bluetooth_setup::drawBackground(CRGB *buffer) 
{
    // Turn off clock backgound
    fill_solid(buffer, NUM_LEDS, CRGB::Blue);

    switch (this->counter % 4)
    {
        case 0:
            fill_buffer_with_sprite_without_override(buffer, sprite_bluetooth_logo, CRGB::White);
            break;
        case 1:
            fill_buffer_with_sprite_without_override(buffer, sprite_bluetooth_logo, CRGB::White);
            break;
        case 2:
            fill_buffer_with_sprite_without_override(buffer, sprite_bluetooth_logo, CRGB::White);
            break;
        case 3:
            fill_buffer_with_sprite_without_override(buffer, sprite_bluetooth_logo, CRGB::White);
            break;
    }
    this->counter++;
}