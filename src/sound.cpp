#include "sound.h"

Sound::Sound()
{
    pinMode(Buzzer, OUTPUT);
}

void Sound::beep() 
{
    digitalWrite(Buzzer, HIGH);
    delay(50);
    digitalWrite(Buzzer, LOW);
}