#include <iostream>
#include "./src/engine.h"

bool Update(bool alive, int neighbors[8])
{
    if (alive)
    {
        if (neighbors[5] == 0)
            return false;
        return true;
    }
    if (neighbors[1] == 1)
        return true;
    return false;
}

int main()
{
    Engine engine(800, 640, "Granite");

    Color bg = Color(7, 8, 18);
    engine.SetBackground(bg);
    engine.Start(32, Update);

    return 0;
}