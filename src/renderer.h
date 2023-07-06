#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <SDL2/SDL.h>

#include "color.h"
#include "grid.h"

class Renderer
{
public:
    Renderer(int w, int h);
    ~Renderer();

    int init(const char *title, bool (*Update)(bool alive, int neighbors[8]));

    void SetBackgroundColor(Color &c);
    void SetGrid(Grid *grid);

private:
    void RenderGrid();
    void UpdateGrid();

    std::pair<int, int> PixelToGrid(int x, int y);
    std::pair<int, int> GridToPixel(int x, int y);

    SDL_Window *m_window;
    SDL_Surface *m_surface;
    SDL_Renderer *m_renderer;

    Color m_bg = Color(0, 0, 0);
    Color m_grid_color = Color(105, 105, 105, 100);
    Grid *m_grid = new Grid(0);

    int m_width, m_height;
    int m_cell_size, m_grid_x, m_grid_y, m_grid_size;

    bool (*m_Update)(bool, int[8]);
};

#endif