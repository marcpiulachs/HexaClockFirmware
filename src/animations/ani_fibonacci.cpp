//
// Created by samuel on 10/09/2020.
//

#include "ani_fibonacci.h"

ani_fibonacci::ani_fibonacci()  : Animation("Fibonacci") {

}

void ani_fibonacci::update_brightness(byte brightness) {
    this->brightness = brightness;
}

void ani_fibonacci::update_settings(byte hue, bool inverted, byte strengh) {
    this->current_color.hue = hue;
    this->inverted = inverted;
    this->strengh = strengh;
}

void ani_fibonacci::set_speed(byte speed) {
    this->step_speed = speed;
}

void ani_fibonacci::run(CRGB *buffer)
{
    uint16_t ms = millis();
    for (byte j = 0; j < NUM_COLS; j++)
    {
        for (byte i = 0; i < NUM_ROWS; i++)
        {
            buffer[XY_fibon(i, j)] = CHSV(i * 8 + j * 8 + ms / 16, 255, 255); // with palette
        }
    }
}

void ani_fibonacci::updateColor(CHSV color) {
    this->current_color = color;
}
