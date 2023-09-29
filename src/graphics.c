#include <Arduino.h>

uint8_t font_position[4][10] = {
    {93,92,85,86,81,80,70,71,65,64},
    {91,90,87,88,79,78,72,73,63,62},
    {33,32,22,23,17,16, 7, 8, 5, 4},
    {31,30,24,25,15,14, 9,10, 3, 2}
};

uint16_t font[10] = {
    0B1111001111000000, //0
    0B0101010101000000, //1
    0B1101111011000000, //2
    0B1101110111000000, //3
    0B0011110101000000, //4
    0B1110110111000000, //5
    0B1110111111000000, //6
    0B1111010101000000, //7
    0B1111111111000000, //8
    0B1111110111000000  //9
};

byte sprite_wifi0[15] = {
        0B00011000,
        0B00111100,
        0B01100110,
        0B11000011,
        0B10011001,
        0B00111100,
        0B01100110,
        0B01000010,
        0B01000010,
        0B00000000,
        0B00011000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};

byte sprite_wifi1[15] = {
        0B00011000,
        0B00111100,
        0B01100110,
        0B11000011,
        0B10011001,
        0B00111100,
        0B01100110,
        0B01000010,
        0B01000010,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};

byte sprite_wifi2[15] = {
        0B00011000,
        0B00111100,
        0B01100110,
        0B11000011,
        0B10000001,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};

byte sprite_wifi3[15] = {
        0B00011000,
        0B00111100,
        0B01100110,
        0B11000011,
        0B10011001,
        0B00111100,
        0B01100110,
        0B01000010,
        0B01011010,
        0B00111100,
        0B01100110,
        0B01000010,
        0B01000010,
        0B00000000,
        0B00011000,
};

byte sprite_ring0[15] = {
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00011000,
        0B00011000,
        0B00011000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};

byte sprite_ring1[15] = {
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00011000,
        0B00111100,
        0B00100100,
        0B00100100,
        0B00100100,
        0B00111100,
        0B00011000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};

byte sprite_ring2[15] = {
        0B00000000,
        0B00000000,
        0B00011000,
        0B00111100,
        0B01100110,
        0B01000010,
        0B01000010,
        0B01000010,
        0B01000010,
        0B01000010,
        0B01100110,
        0B00111100,
        0B00011000,
        0B00000000,
        0B00000000,
};

byte sprite_ring3[15] = {
        0B00011000,
        0B00111100,
        0B01100110,
        0B11000011,
        0B10000001,
        0B10000001,
        0B10000001,
        0B10000001,
        0B10000001,
        0B10000001,
        0B10000001,
        0B11000011,
        0B01100110,
        0B00111100,
        0B00011000,
};
/*
byte sprite[15] = {
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
        0B00000000,
};*/