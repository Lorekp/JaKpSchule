#include "Grid.h"

Grid::Grid(int gridSizeX, int gridSizeY) {
    for (int x = 0; x < gridSizeX; x++)
    {
       grid.push_back(std::vector<GridElement>());
       for (int y = 0; y < gridSizeY; y++) 
       {
           grid.at(x).push_back(GridElement());
       }
    }
}

Grid::Grid()
{
}

void Grid::printGrid()
{
    for (int x = 0; x < grid.size(); x++)
    {
        grid.push_back(std::vector<GridElement>());
        for (int y = 0; y < grid.at(x).size(); y++)
        {
            if (grid.at(x).at(y).getSubGridElements().size() > 0)
                std::cout << grid.at(x).at(y).getSubGridElementAt(0).getType();
            else
                std::cout << "-";
        }
        std::cout << std::endl;
    }
}

GridElement Grid::getGridElementAt(int x, int y) {
	return grid.at(x).at(y);
}

std::vector<std::vector<GridElement>>& Grid::getGrid()
{
    return grid;
}

void Grid::addSubGridElementAt(int x, int y, SubGridElement newSubGridElement) {
    grid.at(x).at(y).addSubGridElement(newSubGridElement);
}