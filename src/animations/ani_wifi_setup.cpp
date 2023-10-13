#include "ani_wifi_setup.h"

ani_wifi_setup::ani_wifi_setup() : Animation ("WiFiSetup") 
{
    this->counter = 0;
    this->color = CRGB(25,25,255);
}

void ani_wifi_setup::drawClock(CRGB *buffer)
{
    Serial.println("No clock");
}

void ani_wifi_setup::drawBackground(CRGB *buffer) 
{
    // Turn off clock backgound
    fill_solid(buffer, NUM_LEDS, CRGB::Blue);

    // Draw WiFi icon to display
    fill_buffer_with_sprite(buffer, sprite_wifi3, CRGB::White);
}