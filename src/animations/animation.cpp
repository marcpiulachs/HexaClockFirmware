//
// Created by samuel on 10/09/2020.
//

#include "animation.h"

void Animation::drawClock(CRGB* buffer) 
{
    time_t time = now();
    CRGB color = CRGB::White;

    int hours = hour(time) % 24;
    int minutes =  minute(time);

    uint16_t digitHour0 = font[hours/10];
    uint16_t digitHour1 = font[hours%10];
    uint16_t digitMinutes0 = font[minutes/10];
    uint16_t digitMinutes1 = font[minutes%10];

    for(uint8_t i=0; i<10; i++) 
    {
        if((digitHour0 >> (15-i)) & 0x01)
            buffer[ font_position[0][i] ] = color;
        else
            buffer[ font_position[0][i] ] = CRGB::Black;

        if((digitHour1 >> (15-i)) & 0x01)
            buffer[ font_position[1][i] ] = color;
        else
            buffer[ font_position[1][i] ] = CRGB::Black;


        if((digitMinutes0 >> (15-i)) & 0x01)
            buffer[ font_position[2][i] ] = color;
        else
            buffer[ font_position[2][i] ] = CRGB::Black;

        if((digitMinutes1 >> (15-i)) & 0x01)
            buffer[ font_position[3][i] ] = color;
        else
            buffer[ font_position[3][i] ] = CRGB::Black;
    }
}

void Animation::drawFrame(CRGB* buffer)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        if((this->foreground_buffer[i] == CRGB::Black) || !draw_time) {
            if (draw_background) {
                buffer[i] = background_buffer[i];
            }else {
                buffer[i] = CRGB::Black;
            }
        } else {
            buffer[i] = foreground_buffer[i];
        }
    }
}

byte Animation::get_pixel_id_from_xy(uint8_t x, uint8_t y) {
    return pixel_map[y][x]-1;
}

void Animation::fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color) {
    for (int y = 0; y < NUM_ROWS ; y++) {
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

