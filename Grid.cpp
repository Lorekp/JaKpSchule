#include "Grid.h"

Grid::Grid(int gridSize) {
    for (int x = 0; x < gridSize; x++)
    {
       for (int y = 0; y < gridSize; y++) 
       {
           
       }
    }
}

int Grid::getGridValueAt(int x, int y) {
	return grid.at(x).at(y);
}

void Grid::setGridValueAt(int x, int y, int newValue, int rotationDeg, int offsetx, int offsety) {
    //value 100 = empty, 101 = slope, 102 = straight
    //rotation 000 = none, rotation 090 = 90°, rotation 180 = 190° ...
    //offset in pixels
    grid[x][y] = concatenate(newValue, rotationDeg);
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}