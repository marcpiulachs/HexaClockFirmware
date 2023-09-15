//
// Created by samuel on 10/09/2020.
//

#include "animation.h"

byte pixel_map[15][8] = {
        {0 ,0 ,0 ,95,96,0 ,0 ,0 },
        {0 ,0 ,94,93,92,91,0 ,0 },
        {0 ,85,86,87,88,89,90,0 },
        {84,83,82,81,80,79,78,77},
        {69,70,71,72,73,74,75,76},
        {68,67,66,65,64,63,62,61},
        {53,54,55,56,57,58,59,60},
        {52,51,50,49,48,47,46,45},
        {37,38,39,40,41,42,43,44},
        {36,35,34,33,32,31,30,29},
        {21,22,23,24,25,26,27,28},
        {20,19,18,17,16,15,14,13},
        {0 ,7 ,8 ,9 ,10,11,12,0 },
        {0 ,0 ,6 ,5 ,4 ,3 ,0 ,0 },
        {0 ,0 ,0 ,1 ,2 ,0 ,0 ,0 },
};

byte get_pixel_id_from_xy(uint8_t x, uint8_t y) {
    return pixel_map[y][x]-1;
}

void fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color) {
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

void fill_buffer_with_sprite_without_override(CRGB *buffer, const byte sprite[15],const CRGB& color) {
    for (int y = 0; y < 15; y++) {
        for (int x = 7; x >= 0; x--) {
            bool b = ((sprite[y] >> x) & 0x01);
            byte pix = get_pixel_id_from_xy(7 - x, y);
            if(pix != 255 && b)
                buffer[pix] = color;
        }
    }
}

