#pragma once
#include <vector>
#include <iostream>
#include "GridElement.h"
#include "SubGridElement.h"

class Grid {

private:
	std::vector<std::vector<GridElement>> grid;

public:
	void addSubGridElementAt(int x, int y, SubGridElement newSubGridElement);
	GridElement getGridElementAt(int x, int y);
	std::vector<std::vector<GridElement>>& getGrid();
	Grid(int gridSizeX, int gridSizeY);
	Grid();
};
