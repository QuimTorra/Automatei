#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "renderer.h"

class Engine
{
public:
    bool quit;

    Engine(int w, int h, std::string win_title);
    ~Engine();

    void Start(int grid_size, bool (*Update)(bool alive, int neighbors[8]));
    void Stop();

    void SetBackground(Color &c);

private:
    int m_width, m_height;
    int m_grid_size;
    std::string m_win_title;

    Renderer *m_renderer;
};

#endif