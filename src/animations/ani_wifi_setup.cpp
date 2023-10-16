#include "ani_wifi_setup.h"

ani_wifi_setup::ani_wifi_setup() : Animation ("WiFiSetup") 
{
    this->background = CRGB::Blue;
    this->foreground = CRGB::White;
}

void ani_wifi_setup::drawClock(CRGB *buffer)
{
    // No clock
}

void ani_wifi_setup::drawBackground(CRGB *buffer) 
{
    // Turn off clock backgound
    fill_solid(buffer, NUM_LEDS, this->background);

    // Draw WiFi icon to display
    fill_sprite(buffer, sprite_wifi3, this->foreground, false);
}