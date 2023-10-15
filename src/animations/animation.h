#ifndef _ANIMATION_H
#define _ANIMATION_H

//#define FASTLED_ALL_PINS_HARDWARE_SPI

#include <iostream>
#include <string>
#include <Arduino.h>
#include <FastLED.h>
#include <TimeLib.h>
#include "graphics.h"

using namespace std;

#define NUM_ROWS 15
#define NUM_COLS 8
#define NUM_LEDS 96

//extern byte pixel_map[NUM_ROWS][NUM_COLS];

class Animation
{
    private:
        char type[64];

    protected:
        byte speed      = 100;
        byte brightness = 255;
        CRGB background = CRGB::Black;
        CRGB foreground = CRGB::White;

        CRGB foreground_buffer  [NUM_LEDS];
        CRGB background_buffer  [NUM_LEDS];

        bool draw_time = true;
        bool draw_background = true;
        bool draw_inverted = true;

        byte pixel_map[NUM_ROWS][NUM_COLS] = 
        {
            {0 ,0 ,0 ,1 ,2 ,0 ,0 ,0 },
            {0 ,0 ,6 ,5 ,4 ,3 ,0 ,0 },
            {0 ,7 ,8 ,9 ,10,11,12,0 },
            {20,19,18,17,16,15,14,13},
            {21,22,23,24,25,26,27,28}, 
            {36,35,34,33,32,31,30,29},
            {37,38,39,40,41,42,43,44},
            {52,51,50,49,48,47,46,45}, 
            {53,54,55,56,57,58,59,60}, 
            {68,67,66,65,64,63,62,61}, 
            {69,70,71,72,73,74,75,76},
            {84,83,82,81,80,79,78,77},
            {0 ,85,86,87,88,89,90,0 },
            {0 ,0 ,94,93,92,91,0 ,0 },
            {0 ,0 ,0 ,95,96,0 ,0 ,0 },  
         };

        byte get_pixel_id_from_xy(uint8_t x, uint8_t y);
        void fill_buffer_with_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color);
        void fill_buffer_with_sprite_without_override(CRGB *buffer, const byte sprite[15],const CRGB& color);

    public:
        Animation(const char *type)
        {
             strncpy(this->type , type, sizeof(this->type));

             // Initialize foreground and background to off/black pixels
             fill_solid(foreground_buffer, NUM_LEDS, CRGB::Black);
             fill_solid(background_buffer, NUM_LEDS, CRGB::Black);
        }

        virtual void run(CRGB* buffer)
        {
            EVERY_N_MILLISECONDS(1) 
            {
                drawBackground(background_buffer);
                drawClock(foreground_buffer);
                drawFrame(buffer);
            }
        }

        void drawFrame(CRGB* buffer);

        virtual void drawClock(CRGB* buffer);

        virtual void drawBackground(CRGB* buffer)
        {

        }

        virtual void setInvert(bool value)
        {
            this->draw_inverted = value;
        }
        
        virtual void setTime(bool value)
        {
            this->draw_time = value;
        }

        virtual void setBackground(bool value)
        {
           this->draw_background = value;
        }

        virtual void setSpeed(byte speed)
        {
           this->speed = speed;
        }

        virtual void setBrightness(byte brightness)
        {
            this->brightness = brightness;
        }

        virtual CRGB getBackcolor ()
        {
            return background;
        }

        virtual CRGB getForecolor ()
        {
            return foreground;
        }

        void setForegroundColor(CHSV color)
        {
            this->foreground = color;
        }

        void setBackgroundColor(CHSV color)
        {
            this->background = color;
        }

        virtual string getType()
        {
            return type;
        }
};

#endif