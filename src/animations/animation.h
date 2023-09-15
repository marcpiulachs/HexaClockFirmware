#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <iostream>
#include <string>

#include "ani_common.h"

using namespace std;

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