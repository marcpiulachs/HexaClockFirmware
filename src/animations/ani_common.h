#ifndef HEXCLOCK_ANI_COMMON_H
#define HEXCLOCK_ANI_COMMON_H

#include <Arduino.h>
#include <FastLED.h>

extern byte pixel_map[15][8];

byte get_pixel_id_from_xy(uint8_t x, uint8_t y);
void fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color);
void fill_buffer_with_sprite_without_override(CRGB *buffer, const byte sprite[15],const CRGB& color);

extern byte sprite_wifi[15];
extern byte sprite_ring0[15];
extern byte sprite_ring1[15];
extern byte sprite_ring2[15];
extern byte sprite_ring3[15];

//extern byte sprite[15];

#endif //HEXCLOCK_ANI_COMMON_H
