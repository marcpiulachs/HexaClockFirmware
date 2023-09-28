#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <iostream>
#include <string>

using namespace std;

#include <Arduino.h>
#include <FastLED.h>

#define NUM_ROWS 15
#define NUM_COLS 8

#define NUM_LEDS NUM_ROWS * NUM_COLS

extern byte pixel_map[NUM_ROWS][NUM_COLS];

byte get_pixel_id_from_xy(uint8_t x, uint8_t y);
void fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color);
void fill_buffer_with_sprite_without_override(CRGB *buffer, const byte sprite[15],const CRGB& color);

extern byte sprite_wifi0[15];
extern byte sprite_wifi1[15];
extern byte sprite_wifi2[15];
extern byte sprite_wifi3[15];

extern byte sprite_ring0[15];
extern byte sprite_ring1[15];
extern byte sprite_ring2[15];
extern byte sprite_ring3[15];

class Animation
{
    private:
        string type;

    public:
        Animation(const char *type) 
        {
             type = type; 
        }

        virtual void run(CRGB* buffer);
        
        virtual void set_speed(byte speed)
        {
            // Empty implementation
        }

        virtual void update_brightness(byte brightness)
        {
            // Empty implementation
        }

        // declare virtual function
        virtual string getType()
        {
            return type;
        }
};

#endif