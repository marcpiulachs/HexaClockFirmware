//
// Created by samuel on 10/09/2020.
//

#include "animation.h"

byte Animation::get_pixel_id_from_xy(uint8_t x, uint8_t y) {
    return pixel_map[y][x]-1;
}

void Animation::fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color) {
    for (int y = 0; y < 15; y++) {
        for (int x = 7; x >= 0; x--) {
            bool b = ((sprite[y] >> x) & 0x01);
            byte pix = get_pixel_id_from_xy(7 - x, y);
            if(pix != 255 && b)
                buffer[pix] = color;
            else if (!b)
                buffer[pix] = CRGB(0,0,0);
        }
    }
}

void Animation::fill_buffer_with_sprite_without_override(CRGB *buffer, const byte sprite[15],const CRGB& color) {
    for (int y = 0; y < 15; y++) {
        for (int x = 7; x >= 0; x--) {
            bool b = ((sprite[y] >> x) & 0x01);
            byte pix = get_pixel_id_from_xy(7 - x, y);
            if(pix != 255 && b)
                buffer[pix] = color;
        }
    }
}

