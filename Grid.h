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
	sf::Vector3i start;
	sf::Vector3i finish;
	sf::Sprite startSprite;
	sf::Sprite finishSprite;

	int getSide(sf::Vector2i cell);

public:
	void addSubGridElementAt(int x, int y, SubGridElement newSubGridElement);

	bool removeRowFromGrid(int row);
	void addRowToGrid();
	bool removeColumnFromGrid(int column);
	void addColumnToGrid();

	void moveGridRight();
	void moveGridDown();

	GridElement& getGridElementAt(int x, int y);
	sf::Vector3i& getStart();
	sf::Vector3i& getFinish();
	sf::Sprite getStartSprite();
	sf::Sprite getFinishSprite();

	void setStart(sf::Vector3i start);
	void setFinish(sf::Vector3i finish);

	bool checkForSubGridElement(int x, int y, int type);
	bool checkForSubGridElementAndSide(int x, int y, int type, int side);

	std::vector<std::vector<GridElement>>& getGrid();

	void draw(float scale, sf::RenderWindow& window, bool drawGrid, bool drawStart, bool drawFinish);

	Grid(int gridSizeX, int gridSizeY);
	Grid();
};
