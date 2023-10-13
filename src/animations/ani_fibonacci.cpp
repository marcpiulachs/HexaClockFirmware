//
// Created by samuel on 10/09/2020.
//

#include "ani_fibonacci.h"

ani_fibonacci::ani_fibonacci()  : Animation("Fibonacci") {

}

/*
void ani_fibonacci::update_brightness(byte brightness) {
    this->brightness = brightness;
}*/
/*
void ani_fibonacci::update_settings(byte hue, bool inverted, byte strengh) {
    this->current_color.hue = hue;
    this->inverted = inverted;
    this->strengh = strengh;
}*/

void ani_fibonacci::setSpeed(byte speed) {
    this->step_speed = speed;
}

uint16_t XY_fibon(byte x, byte y)
{
    uint8_t physicalToFibonacci[NUM_LEDS] = { 0, 13, 26, 39, 52, 57, 44, 31, 18, 5, 10, 23, 36, 49, 62, 54, 41, 28, 15, 2, 7, 20, 33, 46, 59, 51, 38, 25, 12, 4, 17, 30, 43, 56, 61, 48, 35, 22, 9, 1, 14, 27, 40, 53, 58, 45, 32, 19, 6, 11, 24, 37, 50, 63, 55, 42, 29, 16, 3, 8, 21, 34, 47, 60 };

    int led = (y*15+x);
    if (led > NUM_LEDS)
     return 0;

    return physicalToFibonacci[led];
}

void ani_fibonacci::drawBackground(CRGB *buffer)
{
    uint16_t ms = millis();
    for (byte j = 0; j < NUM_ROWS; j++)
    {
        for (byte i = 0; i < NUM_COLS; i++)
        {
            buffer[XY_fibon(j, i)] = CHSV(i * 8 + j * 8 + ms / 16, 255, 255); // with palette
        }
    }
}