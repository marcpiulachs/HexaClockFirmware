#include "ani_bluetooth_setup.h"

ani_bluetooth_setup::ani_bluetooth_setup() : Animation ("Bluetooth") 
{
    this->background = CRGB::Blue;
    this->foreground = CRGB::White;
}

void ani_bluetooth_setup::drawClock(CRGB *buffer)
{
    // No clock
}

void ani_bluetooth_setup::drawBackground(CRGB *buffer)
{
    // Turn off clock backgound
    fill_solid(buffer, NUM_LEDS, this->background);

    // Draw Bluetooth logo
    fill_sprite(buffer, sprite_bluetooth_logo, this->foreground, false);
}