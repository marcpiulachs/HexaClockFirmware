#include "display.h"

Display::Display() {
}

void Display::setAnnimation(annimations annimation) 
{
    if (annimation != current_animation)
    {
        this->current_animation = annimation;
        switch (this->current_animation) {
            case STARTUP_START:
                animation = new ani_startup_sequence();
                break;
            case STARTUP_WIFI:
                this->animation = new ani_wifi_connecting();
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
                this->animation->setSpeed(10);
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
                this->animation->setSpeed(10);
                break;
        }

        Serial.print("Animation set to : ");
        Serial.print(this->animation->getType().c_str());
        Serial.println();
    }
}

void Display::run(CRGB* buffer) {
    if (this->animation != NULL)
        this->animation->drawBackground(buffer);
}
