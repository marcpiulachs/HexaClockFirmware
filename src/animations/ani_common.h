#ifndef HEXCLOCK_ANI_COMMON_H
#define HEXCLOCK_ANI_COMMON_H

#include <Arduino.h>
#include <FastLED.h>

extern byte pixel_map[15][8];

byte get_pixel_id_from_xy(uint8_t x, uint8_t y);
void fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color);

/*byte sprite_wifi[96] = {
        69,84,83,85,86,94,93,95,96,92,91,89,90,78,77,76, //Top bar
        38,51,54,55,66,65,72,73,64,63,58,59,46,43,       //Bottom bar
        24,25                                            //Middle point
};*/
extern byte sprite_wifi[15];

extern byte sprite_ring0[15];
extern byte sprite_ring1[15];
extern byte sprite_ring2[15];
extern byte sprite_ring3[15];

//extern byte sprite[15];

#endif //HEXCLOCK_ANI_COMMON_H
