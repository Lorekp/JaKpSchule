#pragma once
#include "AssetManager.h"
#include "GridElement.h"
#include "SubGridElement.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class AssetManager;
class GridElement;
class SubGridElement;

class Grid {

private:
	std::vector<std::vector<GridElement>> grid;

public:
	void addSubGridElementAt(int x, int y, SubGridElement newSubGridElement);
	GridElement getGridElementAt(int x, int y);

	std::vector<std::vector<GridElement>>& getGrid();

	void draw(float scale, sf::RenderWindow& window, bool drawGrid);

	Grid(int gridSizeX, int gridSizeY);
	Grid();
};
