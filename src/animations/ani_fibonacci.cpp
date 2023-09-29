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
    return (FibonPlanarTable[y * NUM_COLS + x]);
}

void ani_fibonacci::run(CRGB *buffer)
{
    uint16_t ms = millis();
    for (byte j = 0; j < NUM_COLS; j++)
    {
        for (byte i = 0; i < NUM_ROWS; i++)
        {
            buffer[XY_fibon(i, j)] = CHSV(i * 8 + j * 8 + ms / 16, 255, 255); // with palette
            //buffer[XY_fibon(i, j)] = CHSV(sin8((i << 4) + ms / 6) / 2 + sin8((j << 4) + ms / 6) / 2, ~0, ~0);
        }
    }
}

/*
void ani_fibonacci::updateColor(CHSV color) {
    this->current_color = color;
}*/
