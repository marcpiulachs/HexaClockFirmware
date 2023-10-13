//
// Created by samuel on 16/09/2020.
//

#include "ani_fish.h"

ani_fish::ani_fish() : Animation ("Rainbow") {
}

void ani_fish::drawBackground(CRGB *buffer) {
  for (int i = 0; i < NUM_LEDS; i++) {
    buffer[i] = CHSV(hue + (i * 10), 255, 255);
  }

  EVERY_N_MILLISECONDS(15){
    hue++;
  }
}

