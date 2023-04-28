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

void Grid::setGridValueAt(int x, int y, int newValue) {
    grid[x][y] = newValue;
}