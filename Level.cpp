#include "Level.h"
#include "Grid.h"

Level::Level(int gridSize) {
	new Grid(gridSize);
}

Level::Level(std::vector<std::vector<int>> grid) {
	this->grid = grid;
}