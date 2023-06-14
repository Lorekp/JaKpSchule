#pragma once
#include "Grid.h"
#include <SFML/System/Time.hpp>

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
	SubGridElement target;

	sf::Vector2f getPos();
	void setPos(sf::Vector2f newPos);
	void setPos(float x, float y);

	void move(sf::Vector2f target, float dTimeAsSeconds);
	void move(float x, float y, float dTimeAsSeconds);

	bool checkIfMovementValid(int side);
	bool checkCellPos();
public:
	void draw(sf::RenderWindow& window, float scale);
	void move(sf::Time deltaTime);
	void addNextSide(int side);
	Player(Grid& grid);
};

