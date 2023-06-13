#include "Player.h"
#include "AssetManager.h"


Player::Player(Grid& grid) : grid(grid)
{
	this->pSprite = sf::Sprite(AssetManager::getTexture(".\\resources\\blackBall.png"));
	pSprite.setOrigin(128, 128);

	this->grid.getStart();

	sf::Vector2f startPos = grid.getStartSprite().getPosition();

	this->targetPos = startPos;
	this->pos = startPos;
}

bool Player::checkCellPos()
{
	float scale = pSprite.getScale().x;
	float gridSizeX = grid.getGrid().at(0).size() * 256 * scale;
	float gridSizeY = grid.getGrid().size() * 256 * scale;

	for (int i = 0; i < grid.getGrid().size(); i++)
	{
		for (int j = 0; j < grid.getGrid().at(0).size(); j++)
		{
			if ((j * 256 * scale - (gridSizeX / 2)) < pos.x && pos.x < (j * 256 * scale + 256 * scale - (gridSizeX / 2)) &&
				(i * 256 * scale - (gridSizeY / 2)) < pos.y && pos.y < (i * 256 * scale + 256 * scale - (gridSizeY / 2)))
			{
				cellPos = sf::Vector2i(i, j);
				return true;
			}
		}
	}
	return false;
}

void Player::draw(sf::RenderWindow& window, float scale)
{
	pSprite.setScale(scale, scale);
	window.draw(pSprite);
}

void Player::move(sf::Time deltaTime)
{
	//only move if target hasn't been reached
	if (pos != targetPos) {
		move(targetPos, deltaTime.asSeconds());
		if (pos == targetPos)
			lastSide = nextSide.at(0);
	}
	else if (nextSide.size() > 0) //if nextSide available
	{
		bool valid = checkIfMovementValid(nextSide.at(0));
		while (!valid)
		{
			nextSide.erase(nextSide.begin());
			if (nextSide.size() > 0)
			{
				valid = checkIfMovementValid(nextSide.at(0));
			}
			else
				break;
		}
		if (valid)
		{
			//calculate TargetCell

		}
	}
}

void Player::addNextSide(int side)
{
	this->nextSide.push_back(side);
}

sf::Vector2f Player::getPos() { return pos; }
void Player::setPos(sf::Vector2f newPos) { pos = newPos; pSprite.setPosition(pos); }
void Player::setPos(float x, float y) { pos = sf::Vector2f(x, y); pSprite.setPosition(pos); }
void Player::move(sf::Vector2f target, float dTimeAsSeconds) { pos += ((target/*1.1f*/)-pos) * dTimeAsSeconds; pSprite.setPosition(pos); }
void Player::move(float x, float y, float dTimeAsSeconds) { pos += ((sf::Vector2f(x, y)/*1.1f*/) - pos) * dTimeAsSeconds; pSprite.setPosition(pos); }

bool Player::checkIfMovementValid(int side)
{
	
}
