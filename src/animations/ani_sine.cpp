//
// Created by samuel on 10/09/2020.
//

#include "ani_sine.h"

#define NUM_ROWS 15
#define NUM_COLS 8
#define BRIGHTNESS 255
#define NUM_LEDS NUM_ROWS * NUM_COLS

//byte counter = 1;
//int speed = 1;

ani_sine::ani_sine()  : Animation("Sine") {

}

void ani_sine::setBrightness(byte brightness) {
    this->brightness = brightness;
}

void ani_sine::update_settings(byte hue, bool inverted, byte strengh) {
    this->current_color.hue = hue;
    this->inverted = inverted;
    this->strengh = strengh;
}

void ani_sine::setSpeed(byte speed) {
    this->step_speed = speed;
}

byte i,t,u;

void ani_sine::run(CRGB *buffer)
{
  t = millis() / 15;
  u = t * 2;
  for (i = 13; i--;)
    buffer[get_pixel_id_from_xy(sin8(t + i * 20) >> 4, sin8(u + i * 20) >> 4)].setHue(i * 19);
  blur2d(buffer, 16, 16, 32);
}

void ani_sine::updateColor(CHSV color) {
    this->current_color = color;
}
