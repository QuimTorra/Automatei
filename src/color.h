#ifndef COLOR_H_
#define COLOR_H_

#include <SDL2/SDL.h>

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    };
    Color(Uint8 r, Uint8 g, Uint8 b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1;
    }
};

#endif