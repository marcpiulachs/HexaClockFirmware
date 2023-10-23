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

    for (uint8_t i = 0; i < 10; i++)
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

byte Animation::XY(uint8_t x, uint8_t y) 
{
    // As a safety measure check if x,y is a valid pixel,
    // any out of bounds address maps to the first hidden pixel
    if ( (x >= NUM_COLS) || (y >= NUM_ROWS) ) {
        return DUMMY_LED;
    }

    return pixel_map[y][x]-1;
}

void Animation::fill_sprite(CRGB *buffer, const byte sprite[15],const CRGB& color, bool override) {
    for (int y = 0; y < NUM_ROWS ; y++) {
        for (int x = 7; x >= 0; x--) {
            bool b = ((sprite[y] >> x) & 0x01);
            byte pix = XY(7 - x, y);
            if(pix != 255 && b)
                buffer[pix] = color;
            else if (!b && override)
                buffer[pix] = CRGB::Black;
        }
    }
}

void Animation::fill_color_sprite(CRGB *buffer, const uint32_t sprite[120]) {
    for (int y = 0; y < NUM_ROWS ; y++) {
        for (int x = 0; x < NUM_COLS; x++) {
            uint32_t pixel = sprite[x + (NUM_COLS * y)];
            uint8_t red = (pixel >> 16) & 0xFF;
            uint8_t green = (pixel >> 8) & 0xFF;
            uint8_t blue = pixel & 0xFF;
            //Serial.printf("%d. %08X, %02X %02X %02X", x + (NUM_COLS * y), pixel, red, green, blue);
            //Serial.println();
            buffer[XY(x, y)] = CRGB(green, red, blue);
        }
  }
}

void Animation::setSpeed(byte speed)
{
    this->speed = speed;
}

int Animation::getSpeed()
{
    return this->speed;
}