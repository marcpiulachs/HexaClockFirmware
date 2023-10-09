//
// Created by samuel on 10/09/2020.
//

#include "ani_proton.h"

#define NUM_ROWS 12
#define NUM_COLS 8
#define BRIGHTNESS 255
#define NUM_LEDS NUM_ROWS * NUM_COLS

ani_proton::ani_proton()  : Animation("Proton") {
  
}

void ani_proton::setBrightness(byte brightness) {
    this->brightness = brightness;
}


// Color correction for the SmartMatrix
#define COLOR_CORRECTION CRGB(255,110,178)

void ani_proton::run(CRGB *buffer)
{
   static uint8_t counter = 0 ;
  // Apply some blurring to whatever's already on the matrix
  // Note that we never actually clear the matrix, we just constantly
  // blur it repeatedly.  Since the blurring is 'lossy', there's
  // an automatic trend toward black -- by design.
  if( counter % 3 == 0 ) {
    uint8_t blurAmount = beatsin8(2, 100, 150);
    blur2d( buffer, kMatrixWidth, kMatrixHeight, blurAmount);
    // Serial.println(blurAmount);
  }
  counter++;

  // Use two out-of-sync sine waves
  uint8_t  i = beatsin8( 27, kBorderWidth, kMatrixHeight - kBorderWidth);
  uint8_t  j = beatsin8( 41, kBorderWidth, kMatrixWidth - kBorderWidth);

  // Also calculate some reflections
  uint8_t ni = (kMatrixWidth - 1) - i;
  uint8_t nj = (kMatrixWidth - 1) - j;

  // The color of each point shifts over time, each at a different speed.
  uint16_t ms = millis();
  buffer[get_pixel_id_from_xy( i, j)] += CHSV( ms / 11, 255, 255);
  buffer[get_pixel_id_from_xy( j, i)] += CHSV( ms / 13, 255, 255);
  buffer[get_pixel_id_from_xy(ni, nj)] += CHSV( ms / 17, 255, 255);
  buffer[get_pixel_id_from_xy(nj, ni)] += CHSV( ms / 29, 255, 255);
  buffer[get_pixel_id_from_xy( i, nj)] += CHSV( ms / 37, 255, 255);
  buffer[get_pixel_id_from_xy(ni, j)] += CHSV( ms / 41, 255, 255);
}
