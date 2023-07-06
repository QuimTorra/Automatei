#include "renderer.h"

Renderer::Renderer(int w, int h)
{
    m_width = w;
    m_height = h;
}

int Renderer::init(const char *title, bool (*Update)(bool alive, int neighbors[8]))
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width, m_height,
                                0);
    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    m_surface = SDL_GetWindowSurface(m_window);
    if (!m_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!m_renderer)
    {
        std::cout << "Failed to create the renderer for the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }
    // Set the the window as the target
    SDL_SetRenderTarget(m_renderer, NULL);

    m_Update = Update;

    bool keep_window_open = true;
    while (keep_window_open)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::pair<int, int> coords = PixelToGrid(e.button.x, e.button.y);
                if (coords.first == -1 || coords.second == -1)
                    break;
                if (e.button.button == SDL_BUTTON_LEFT)
                    m_grid->SetCell(coords.first, coords.second, true);
                else if (e.button.button == SDL_BUTTON_RIGHT)
                    m_grid->SetCell(coords.first, coords.second, false);
                break;
            }
            SDL_UpdateWindowSurface(m_window);
        }

        SDL_SetRenderDrawColor(m_renderer, m_bg.r, m_bg.g, m_bg.b, m_bg.a);
        SDL_RenderClear(m_renderer);

        UpdateGrid();
        RenderGrid();

        SDL_RenderPresent(m_renderer);
    }

    return 0;
}

void Renderer::SetBackgroundColor(Color &c)
{
    m_bg = c;
}

void Renderer::SetGrid(Grid *grid)
{
    m_grid = grid;

    int padding = 10;
    // This doesn't take into account that the grid lines are 1px in width
    m_cell_size = (m_height - padding) / m_grid->get_size();
    m_grid_size = (m_cell_size)*m_grid->get_size();
    m_grid_x = (m_width / 2) - (m_grid_size / 2);
    m_grid_y = (m_height / 2) - (m_grid_size / 2);
}

// PRIVATE

void Renderer::RenderGrid()
{
    if (m_grid->get_size() == 0)
        return;

    SDL_SetRenderDrawColor(m_renderer, m_grid_color.r, m_grid_color.g, m_grid_color.b, m_grid_color.a);

    for (int i = 1; i < m_grid->get_size(); i++)
    {
        int x1 = m_grid_x + m_cell_size * i;
        int x2 = x1;
        int y1 = m_grid_y;
        int y2 = y1 + m_grid_size;
        SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);

        x1 = m_grid_x;
        x2 = x1 + m_grid_size;
        y1 = m_grid_y + m_cell_size * i;
        y2 = y1;
        SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
    }

    for (int i = 0; i < m_grid->get_size(); i++)
    {
        for (int j = 0; j < m_grid->get_size(); j++)
        {
            if (m_grid->GetCell(i, j))
            {
                SDL_Rect rect;
                rect.h = m_cell_size;
                rect.w = m_cell_size;
                std::pair<int, int> pxCoords = GridToPixel(i, j);
                rect.x = pxCoords.first;
                rect.y = pxCoords.second;
                SDL_RenderFillRect(m_renderer, &rect);
            }
        }
    }
}

void Renderer::UpdateGrid()
{
    std::vector<std::pair<int, int>> next_pos;
    std::vector<bool> next_states;

    for (int i = 0; i < m_grid->get_size(); i++)
    {
        for (int j = 0; j < m_grid->get_size(); j++)
        {
            bool alive = m_grid->GetCell(i, j);
            int *neighbors = m_grid->GetNeighbors(i, j);
            bool new_state = m_Update(alive, neighbors);
            if (new_state != m_grid->GetCell(i, j))
            {
                next_pos.push_back(std::pair<int, int>(i, j));
                next_states.push_back(new_state);
            }
        }
    }

    for (int i = 0; i < next_pos.size(); i++)
        m_grid->SetCell(next_pos[i].first, next_pos[i].second, next_states[i]);
}

std::pair<int, int> Renderer::PixelToGrid(int x, int y)
{
    int gridX = 0;
    int gridY = 0;

    gridX = (x - m_grid_x) / m_cell_size;
    gridY = (y - m_grid_y) / m_cell_size;

    if (gridX < 0 || gridX > m_grid->get_size() - 1 || gridY < 0 || gridY > m_grid->get_size() - 1)
        return std::pair<int, int>(-1, -1);

    return std::pair<int, int>(gridX, gridY);
}

std::pair<int, int> Renderer::GridToPixel(int x, int y)
{
    int pX = 0;
    int pY = 0;

    pX = (x * m_cell_size) + m_grid_x;
    pY = (y * m_cell_size) + m_grid_y;

    return std::pair<int, int>(pX, pY);
}
