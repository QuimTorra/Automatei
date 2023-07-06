#include "engine.h"

Engine::Engine(int w, int h, std::string win_title)
{
    m_width = w;
    m_height = h;
    m_win_title = win_title;

    m_renderer = new Renderer(m_width, m_height);
}

Engine::~Engine() {}

void Engine::Start(int grid_size, bool (*Update)(bool alive, int neighbors[8]))
{
    m_grid_size = grid_size;
    Grid grid = Grid(m_grid_size);
    m_renderer->SetGrid(&grid);
    m_renderer->init(m_win_title.c_str(), Update);
    std::cout << "Ended" << std::endl;
}

void Engine::Stop()
{
}

void Engine::SetBackground(Color &c)
{
    m_renderer->SetBackgroundColor(c);
}
