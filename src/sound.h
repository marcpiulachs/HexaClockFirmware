#ifndef _SOUND_H
#define _SOUND_H

#include <Arduino.h>

class Sound {
    public:
        Sound ();
        void beep();
        const int Buzzer = GPIO_NUM_4;
    private:
};

#endif //_SOUND_H