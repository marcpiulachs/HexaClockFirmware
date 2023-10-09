#ifndef HEXCLOCK_ANI_PROTON_H
#define HEXCLOCK_ANI_PROTON_H

#include "animation.h"

class ani_proton : public Animation
{
    public:
        ani_proton();
        void run(CRGB* buffer);
        void setspeed(byte speed);
        void setBrightness(byte brightness);
        void update_settings(byte hue, bool inverted, byte strengh);
        void updateColor(CHSV color);

    private:
    uint16_t XY(uint8_t x, uint8_t y) {
  if (x >= kMatrixWidth) return NUM_LEDS;
  if (y >= kMatrixHeight) return NUM_LEDS;
  return y * kMatrixWidth + x;
}
        const uint8_t kMatrixWidth  = 12;
        const uint8_t kMatrixHeight = 8;
        const uint8_t kBorderWidth = 0;

        CHSV current_color = CHSV(50,255,255);
        //byte current_hue = 50;
        byte step_speed = 100;
        byte strengh = 180;
        byte brightness = 255;
        bool inverted = false;

        byte circles_lumi_offset[4] = {120,140,150,160};
        bool circles_lumi_orientation = false;
};


#endif //HEXCLOCK_ANI_PROTON_H
