#include "hashfield.h"

#include "field.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

HashField::HashField(int width, int height)
{
    this->width = width;
    this->height = height;

    cells = new bool[width * height];

    clearField();
}

bool HashField::getCell(int x, int y) const
{
    return this->cells[x+y*width];
}

void HashField::setCell(int x, int y, bool value)
{
    this->cells[x+y*width] = value;
}

void HashField::invertCell(int x, int y)
{
    this->cells[x+y*width] = !this->cells[x+y*width];
}

void HashField::clearField()
{
    std::fill(cells, cells + width * height, false);
}

bool randomGenerator()
{
    return rand() % 2;
}

void HashField::randomizeField()
{
    srand(time(nullptr));

    std::generate_n(cells, width * height, randomGenerator);
}

void HashField::step(int count)
{
    for (int i = 0; i < count; ++i)
    {
        this->stepOnce();
    }
}

int HashField::getNeighboursCount(int cellX, int cellY) const
{
    int neighbours = 0;

    for (int x = cellX - 1; x <= cellX + 1; ++x)
    {
        for (int y = cellY - 1; y <= cellY + 1; ++y)
        {
            if (x == cellX && y == cellY) continue;

            if (x >= 0 && y >= 0 &&
                    x < width && y < height &&
                    getCell(x, y))
            {
                neighbours++;
            }
        }
    }

    return neighbours;
}

void HashField::stepOnce()
{
    bool * newCells = new bool[width * height];

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            int neighbours = getNeighboursCount(x, y);
            if (getCell(x, y))
            {
                if(neighbours < 2 || neighbours > 3)
                    newCells[x+y*width] = false;
                else
                    newCells[x+y*width] = true;
            }
            else
            {
                if(neighbours == 3)
                    newCells[x+y*width] = true;
                else
                    newCells[x+y*width] = false;
            }
        }
    }

    delete this->cells;
    this->cells = newCells;
}
