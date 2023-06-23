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
	float currentSpeed;


	void move(sf::Vector2f target, float dTimeAsSeconds);
	void move(float x, float y, float dTimeAsSeconds);
	float Lerp(float x, float y, float z);

	bool checkIfMovementValid(int side);
	bool checkCellPos(sf::Vector2f posToCheck, sf::Vector2i& variable);
	bool finished;

	int getSide(sf::Vector2i cell);
	void setInitialPos(sf::Vector2f constPos);
	void setInitialPos(float cx, float cy);
	bool rotMultipleOf90(int rot);
public:
	sf::Vector2f getPos();
	sf::Vector2f getTargetPos();
	bool getFinished();
	void setPos(sf::Vector2f newPos);
	void setPos(float x, float y);
	void setTargetPos(float x, float y);
	void setTargetPos(sf::Vector2f newPos);
	void draw(sf::RenderWindow& window);
	void move(sf::Time deltaTime, bool bypassMovementValid);
	void addNextSide(int side);
	Player(Grid& grid);
};

