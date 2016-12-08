#include "field.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

Field::Field(int width, int height)
{
    this->width = width;
    this->height = height;

    cells = new char[width * height];

    clearField();
}

char Field::getCell(int x, int y) const
{
    return this->cells[x+y*width];
}

void Field::setCell(int x, int y, char value)
{
    if(value > 3)
        throw "Invalid cell value";

    this->cells[x+y*width] = value;
}

void Field::invertCell(int x, int y, char direction)
{
    this->cells[x+y*width] += direction;

    if (this->cells[x+y*width] > 3)
        this->cells[x+y*width] = 0;
    else if (this->cells[x+y*width] < 0)
        this->cells[x+y*width] = 3;
}

void Field::clearField()
{
    std::fill(cells, cells + width * height, 0);
}

bool randomGenerator()
{
    return rand() % 4;
}

void Field::randomizeField()
{
    srand(time(nullptr));

    std::generate_n(cells, width * height, randomGenerator);
}

void Field::step(int count)
{
    for (int i = 0; i < count; ++i)
    {
        this->stepOnce();
    }
}

int Field::getElectronHeadsCount(int cellX, int cellY) const
{
    int neighbours = 0;

    for (int x = cellX - 1; x <= cellX + 1; ++x)
    {
        for (int y = cellY - 1; y <= cellY + 1; ++y)
        {
            if (x == cellX && y == cellY) continue;

            if (x >= 0 && y >= 0 &&
                    x < width && y < height &&
                    getCell(x, y) == 1)
            {
                neighbours++;
            }
        }
    }

    return neighbours;
}

void Field::stepOnce()
{
    char * newCells = new char[width * height];

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            if (getCell(x, y) == 0)
            {
                newCells[x+y*width] = 0;
            }
            else if (getCell(x, y) < 3)
            {
                newCells[x+y*width] = getCell(x, y) + 1;
            }
            else
            {
                int neighbours = getElectronHeadsCount(x, y);
                if (neighbours == 1 || neighbours == 2)
                    newCells[x+y*width] = 1;
                else
                    newCells[x+y*width] = 3;
            }
        }
    }

    delete this->cells;
    this->cells = newCells;
}
