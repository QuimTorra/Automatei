#include "grid.h"

#include <iostream>

Grid::Grid(int size)
{
    m_size = size;
    m_grid = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
}

Grid::~Grid()
{
}

int Grid::get_size()
{
    return m_size;
}

void Grid::SetCell(int x, int y, bool b)
{
    m_grid[x][y] = b;
}

bool Grid::GetCell(int x, int y)
{
    return m_grid[x][y];
}

int *Grid::GetNeighbors(int x, int y)
{
    int x_idx[8] = {x - 1, x, x + 1, x + 1, x + 1, x, x - 1, x - 1};
    int y_idx[8] = {y - 1, y - 1, y - 1, y, y + 1, y + 1, y + 1, y};

    static int neighbors[8];

    for (int i = 0; i < 8; i++)
    {
        // Out of bounds
        if (x_idx[i] < 0 || x_idx[i] >= m_size || y_idx[i] < 0 || y_idx[i] >= m_size)
        {
            neighbors[i] = -1;
            continue;
        }

        neighbors[i] = m_grid[x_idx[i]][y_idx[i]] ? 1 : 0;
    }

    return neighbors;
}
