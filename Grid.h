#pragma once
#include "AssetManager.h"
#include "GridElement.h"
#include "SubGridElement.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class AssetManager;

class Grid {

private:
	std::vector<std::vector<GridElement>> grid;
	std::vector<std::vector<sf::Sprite>> sprites;

	void calcSprites();
public:
	void addSubGridElementAt(int x, int y, SubGridElement newSubGridElement);
	GridElement getGridElementAt(int x, int y);

	std::vector<std::vector<GridElement>>& getGrid();

	void draw(float px, float py, float scale, sf::RenderWindow& window);

	Grid(int gridSizeX, int gridSizeY);
	Grid();
};
