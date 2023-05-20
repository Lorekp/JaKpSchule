#pragma once

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

	void draw(float scale, sf::RenderWindow& window);

	Grid(int gridSizeX, int gridSizeY);
	Grid();
};
