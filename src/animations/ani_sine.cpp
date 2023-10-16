//
// Created by samuel on 10/09/2020.
//

#include "ani_sine.h"

ani_sine::ani_sine()  : Animation("Sine") {

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

void ani_sine::drawBackground(CRGB *buffer)
{
  t = millis() / 15;
  u = t * 2;
  for (i = 13; i--;)
    buffer[XY(sin8(t + i * 20) >> 4, sin8(u + i * 20) >> 4)].setHue(i * 19);
}