#ifndef _WOPR_H
#define _WOPR_H

#include "animation.h"

class ani_wopr : public Animation {
    public:
        ani_wopr();
        void drawBackground(CRGB* buffer);
    private:
        int16_t counter = 0;
};


#endif //_WOPR_H
