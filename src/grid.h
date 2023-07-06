#ifndef GRID_H_
#define GRID_H_

#include <vector>

class Grid
{
public:
    Grid(int size);
    ~Grid();

    int get_size();

    void SetCell(int x, int y, bool b);
    bool GetCell(int x, int y);
    int *GetNeighbors(int x, int y);

private:
    int m_size;
    std::vector<std::vector<bool>> m_grid;
};

#endif