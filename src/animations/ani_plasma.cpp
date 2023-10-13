//
// Created by samuel on 08/09/2020.
//

#include "ani_plasma.h"

ani_plasma::ani_plasma() : Animation ("Plasma") 
{

}

void ani_plasma::drawBackground(CRGB *buffer) {
    // Fill background with dim plasma
    for (int16_t x = 0; x < NUM_COLS; x++) {
        for (int16_t y = 0; y < NUM_ROWS; y++) {
            int16_t r = sin16(_plasmaTime) / 256;
            int16_t h = sin16(x * r * _plasmaXfactor + _plasmaTime) + cos16(y * (-r) * _plasmaYfactor + _plasmaTime) + sin16(y * x * (cos16(-_plasmaTime) / 256) / 2);
            buffer[get_pixel_id_from_xy(x, y)] = CHSV((uint8_t)((h / 256) + 128), 255, 255);
        }
    }
    uint16_t oldPlasmaTime = _plasmaTime;
    _plasmaTime += _plasmaShift;
    if (oldPlasmaTime > _plasmaTime)
    _plasmaShift = (random8(0, 5) * 32) + 64;
}