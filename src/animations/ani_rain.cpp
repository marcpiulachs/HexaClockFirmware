//
// Created by samuel on 10/09/2020.
//

#include "ani_rain.h"

#define NUM_ROWS 15
#define NUM_COLS 8
#define BRIGHTNESS 255
#define NUM_LEDS NUM_ROWS * NUM_COLS

byte counter = 1;
//int speed = 1;

ani_rain::ani_rain()  : Animation("Rain") {
    raininit();
}

void ani_rain::raininit() {                               
    //init array of dots. run once
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random8(20) == 0) {
      rain[i] = 1;  //random8(20) number of dots. decrease for more dots
    }
    else {
      rain[i] = 0;
    }
  }
}

void ani_rain::changepattern () {
  int rand1 = random16 (NUM_LEDS);
  int rand2 = random16 (NUM_LEDS);
  if ((rain[rand1] == 1) && (rain[rand2] == 0) )   //simple get two random dot 1 and 0 and swap it,
  {
    rain[rand1] = 0;  //this will not change total number of dots
    rain[rand2] = 1;
  }
} //changepattern

uint16_t XY (uint8_t x, uint8_t y) {
  return (y * 96 + x);
}

void ani_rain::setBrightness(byte brightness) {
    this->brightness = brightness;
}

void ani_rain::update_settings(byte hue, bool inverted, byte strengh) {
    this->current_color.hue = hue;
    this->inverted = inverted;
    this->strengh = strengh;
}

void ani_rain::setSpeed(byte speed) {
    this->step_speed = speed;
}

void ani_rain::run(CRGB *buffer)
{
  for (byte i = 0; i < NUM_COLS; i++) {
    for (byte j = 0; j < NUM_ROWS; j++) {
      byte layer = rain[get_pixel_id_from_xy(i, ((j + speed + random8(2) + NUM_ROWS) % NUM_ROWS))];   //fake scroll based on shift coordinate
      // random8(2) add glitchy look
      if (layer) {
        buffer[get_pixel_id_from_xy((NUM_COLS - 1) - i, (NUM_ROWS - 1) - j)] = CHSV(110, 255, BRIGHTNESS);
      }
    }
  }

  speed ++;
  fadeToBlackBy(buffer, NUM_LEDS, 40);
  blurRows(buffer, NUM_COLS, NUM_ROWS, 16);      //if you want
}

void ani_rain::updateColor(CHSV color) {
    this->current_color = color;
}
