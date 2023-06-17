#pragma once
#include "Grid.h"
#include "SubGridElement.h"
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


	void move(sf::Vector2f target, float dTimeAsSeconds);
	void move(float x, float y, float dTimeAsSeconds);

	bool checkIfMovementValid(int side);
	bool checkCellPos(sf::Vector2f posToCheck);

	int getSide(sf::Vector2i cell);
public:
	sf::Vector2f getPos();
	void setPos(sf::Vector2f newPos);
	void setPos(float x, float y);
	void setTargetPos(float x, float y);
	void setTargetPos(sf::Vector2f newPos);
	void draw(sf::RenderWindow& window, float scale);
	void move(sf::Time deltaTime);
	void addNextSide(int side);
	Player(Grid& grid);
};

