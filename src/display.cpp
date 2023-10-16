#include "display.h"

Display::Display() {
}

void Display::setup()
{
    // Make sure data pin is low so we don't latch up the LEDs.
    digitalWrite(DATA_PIN, LOW);

    // Setup fastled settings
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(output_buffer, NUM_LEDS);
    FastLED.setBrightness(0);
    FastLED.clear(true);
}

void Display::setTime(bool value) 
{
    if (this->animation != NULL)
        this->animation->setTime(value);
}

void Display::setSpeed(byte speed) 
{
    if (this->animation != NULL)
        this->animation->setSpeed(speed);
}

void Display::setBrightness(byte brightness)
{
    this->brightness = brightness;
}

void Display::setBackground(bool value) 
{
    if (this->animation != NULL)
        this->animation->setBackground(value);
}

void Display::setInvert(bool value) 
{
    if (this->animation != NULL)
        this->animation->setInvert(value);
}

void Display::setAnnimation(annimations annimation) 
{
    if (annimation != current_animation)
    {
        this->current_animation = annimation;
        switch (this->current_animation) 
        {
            case STARTUP:
                animation = new ani_startup_sequence();
                this->animation->setSpeed(255);
                break;
            case STARTUP_WIFI:
                this->animation = new ani_wifi_connecting();
                this->animation->setSpeed(255);
                break;
            case COLORFADE:
                this->animation = new ani_color_fade(120);
                this->animation->setSpeed(100);
                break;
            case BREATHING:
                this->animation  = new ani_breathing(255,50,false,200);
                this->animation->setSpeed(10);
                break;
            case CHRISTMAS:
                this->animation = new ani_christmas(50,CRGB(255,0,100),CRGB(200,0,20));
                this->animation->setSpeed(10);
                break;
            case FIBONACCI:
                this->animation = new ani_fibonacci();
                this->animation->setSpeed(10);
                break;
            case RAIN:
                this->animation = new ani_rain();
                this->animation->setSpeed(10);
                break;
            case FIRE:
                this->animation = new ani_fire();
                this->animation->setSpeed(10);
                break;
            case PRIDE:
                this->animation = new ani_pride();
                this->animation->setSpeed(10);
                break;
            case PLASMA:
                this->animation = new ani_plasma();
                this->animation->setSpeed(1);
                break;
            case SINE:
                this->animation = new ani_sine();
                this->animation->setSpeed(10);
                break;
            case SETUP_WIFI:
                this->animation = new ani_wifi_setup();
                this->animation->setSpeed(10);
                break;
            case SETUP_BLUETOOTH:
                this->animation = new ani_bluetooth_setup();
                this->animation->setSpeed(10);
                break;
            case FISH:
                this->animation = new ani_fish();
                this->animation->setSpeed(10);
                break;
            case WOPR:
                this->animation = new ani_wopr();
                this->animation->setSpeed(100);
                break;
        }

        Serial.println();
        Serial.print("Animation set to : ");
        Serial.print(this->animation->getType().c_str());
        Serial.println();
    }
}

void Display::draw()
{
    if (this->animation != NULL)
    {
        // Render the animation
        this->animation->run(output_buffer);

        FastLED.delay(animation->getSpeed());
        FastLED.setBrightness(this->brightness);
    }
}