#pragma once
#include "Grid.h"

class Player
{
private:
	Grid& grid;
	sf::Sprite pSprite;

	std::vector<int> nextSide;
	int lastSide;
	sf::Vector2f pos;
	sf::Vector2i cellPos;
	sf::Vector2f targetPos;
	sf::Vector2i cellTarget;
public:
	void draw(sf::RenderWindow& window, float scale);
	void move();
	Player(Grid& grid);
};

