#include "Player.h"
#include "AssetManager.h"
#include "Settings.h"

Player::Player(Grid& grid) : grid(grid)
{
	this->pSprite = sf::Sprite(AssetManager::getTexture(".\\resources\\blackBall.png"));
	pSprite.setOrigin(128, 128);

	//set player starting pos
	int gridSizeX = grid.getGrid().size();
	int gridSizeY = grid.getGrid().at(0).size();
	
	float scale = Settings::getScale();

	switch (getSide(sf::Vector2i(grid.getStart().x, grid.getStart().y)))
	{
	case 2: setPos((gridSizeY * 256 * scale) / 2 + 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(3); break;
	case 4: setPos(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(1); break;
	case 3: setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); nextSide.push_back(2); break;
	case 6: setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); nextSide.push_back(0); break;
	case 5: {
		if (grid.getStart().z == 2) {
			setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); nextSide.push_back(2);
		}
		else if (grid.getStart().z == 3) {
			setPos((gridSizeY * 256 * scale) / 2 + 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(3);
		}
		break;
	}
	case 8: {
		if (grid.getStart().z == 3) {
			setPos((gridSizeY * 256 * scale) / 2 + 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(3);
		}
		else if (grid.getStart().z == 0) {
			setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); nextSide.push_back(0);
		}
		break;
	}
	case 10: {
		if (grid.getStart().z == 0) {
			setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); nextSide.push_back(0);
		}
		else if (grid.getStart().z == 1) {
			setPos(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(1);
		}
		break;
	}
	case 7: {
		if (grid.getStart().z == 2) {
			setPos(grid.getStart().y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); nextSide.push_back(2);
		}
		else if (grid.getStart().z == 1) {
			setPos(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, grid.getStart().x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); nextSide.push_back(1);
		}
		break;
	}
	default:
		break;
	}
	
	setTargetPos(pos);
	cellPos = sf::Vector2i(0, grid.getStart().y);
	move(sf::seconds(0.1f), true);
}

bool Player::checkCellPos(sf::Vector2f posToCheck)
{
	float scale = Settings::getScale();
	float gridSizeX = grid.getGrid().at(0).size() * 256 * scale;
	float gridSizeY = grid.getGrid().size() * 256 * scale;

	for (int i = 0; i < grid.getGrid().size(); i++)
	{
		for (int j = 0; j < grid.getGrid().at(0).size(); j++)
		{
			if ((j * 256 * scale - (gridSizeX / 2)) < posToCheck.x && posToCheck.x < (j * 256 * scale + 256 * scale - (gridSizeX / 2)) &&
				(i * 256 * scale - (gridSizeY / 2)) < posToCheck.y && posToCheck.y < (i * 256 * scale + 256 * scale - (gridSizeY / 2)))
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
	pSprite.setPosition(pos);
	pSprite.setScale(scale, scale);
	window.draw(pSprite);
}

void Player::move(sf::Time deltaTime, bool bypassMovementValid)
{
	const float scale = Settings::getScale();
	//only move if target hasn't been reached
	if (pos != targetPos) {
		move(targetPos, deltaTime.asSeconds());
		if (pos == targetPos)
			lastSide = nextSide.at(0);
	}
	else if (nextSide.size() > 0) //if nextSide available
	{
		bool valid = checkIfMovementValid(nextSide.at(0));
		if (bypassMovementValid)
			valid = true;
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
			bool targetFound = false;
			//trace and find next target
			if (nextSide.at(0) == 0) {
				for (int i = 0; targetFound == false; i++)
				{
					int posX = -(grid.getGrid().at(0).size() / static_cast<float>(2)) * 256 * scale + scale * 128  + scale * 256 * cellPos.y;
					int scannedPixel = pos.y - i;
					if (checkCellPos(sf::Vector2f(posX, scannedPixel))) {
						for (int j = 0; j < grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElements().size(); j++)
						{
							if (grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j).getBoundingBox().getGlobalBounds().contains(posX, scannedPixel))
							{
								targetFound = true;
								targetPos = sf::Vector2f(posX, pos.y - i);
								target = grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j);
							}
						}
					}
					if ((scannedPixel) < grid.getGrid().size() * -256 * scale)
					{
						targetFound = true;
						targetPos = sf::Vector2f(posX, -1000);
					}
				}
			}
			else if (nextSide.at(0) == 2) {
				for (int i = 0; targetFound == false; i++)
				{
					int posX = -(grid.getGrid().at(0).size() / static_cast<float>(2)) * 256 * scale + scale * 128 + scale * 256 * cellPos.y;
					int scannedPixel = pos.y + i;
					if (checkCellPos(sf::Vector2f(posX, scannedPixel))) {
						for (int j = 0; j < grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElements().size(); j++)
						{
							if (grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j).getBoundingBox().getGlobalBounds().contains(posX, scannedPixel))
							{
								targetFound = true;
								targetPos = sf::Vector2f(posX, scannedPixel);
								target = grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j);
							}
						}
					}
					if (scannedPixel > grid.getGrid().size() * 256 * scale)
					{ 
						targetFound = true;
						targetPos = sf::Vector2f(posX, 1000);

					}
				}
			}
			else if (nextSide.at(0) == 1) {
				for (int i = 0; targetFound == false; i++)
				{
					int posY = -(grid.getGrid().size() / static_cast<float>(2)) * 256 * scale + scale * 128 + scale * 256 * cellPos.x;
					int scannedPixel = pos.x + i;
					if (checkCellPos(sf::Vector2f(scannedPixel, posY))) {
						for (int j = 0; j < grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElements().size(); j++)
						{
							if (grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j).getBoundingBox().getGlobalBounds().contains(scannedPixel, posY))
							{
								targetFound = true;
								targetPos = sf::Vector2f(pos.x + 1, posY);
								target = grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j);
							}
						}
					}
					if ((scannedPixel) > grid.getGrid().at(0).size() * 256 * scale)
					{
						targetFound = true;
						targetPos = sf::Vector2f(1000, posY);
					}
				}
			}
			else if (nextSide.at(0) == 3) {
				for (int i = 0; targetFound == false; i++)
				{
					int posY = -(grid.getGrid().size() / static_cast<float>(2)) * 256 * scale + scale * 128 + scale * 256 * cellPos.x;
					int scannedPixel = pos.x - i;
					if (checkCellPos(sf::Vector2f(scannedPixel, posY))) {
						for (int j = 0; j < grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElements().size(); j++)
						{
							if (grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j).getBoundingBox().getGlobalBounds().contains(scannedPixel, posY))
							{
								targetFound = true;
								targetPos = sf::Vector2f(pos.x - 1, posY);
								target = grid.getGridElementAt(cellPos.x, cellPos.y).getSubGridElementAt(j);
							}
						}
					}
					if ((scannedPixel) < grid.getGrid().at(0).size() * -256 * scale)
					{
						targetFound = true;
						targetPos = sf::Vector2f(-1000, posY);
					}
				}
			}
		}
	}
}

void Player::addNextSide(int side)
{
	this->nextSide.push_back(side);
}

sf::Vector2f Player::getPos() { return pos; }
int Player::getSide(sf::Vector2i cell) //2 = e, 4 = w, n = 3, s = 6 | ne = 5, se = 8, sw = 10, nw = 7
{
	int result = 0;

	if (cell.x == 0)
		result = 3;
	else if (cell.x == grid.getGrid().size() - 1)
		result = 6;
	if (cell.y == 0)
		result += 4;
	else if (cell.y == grid.getGrid().at(0).size() - 1)
		result += 2;

	return result;
}
void Player::setInitialPos(sf::Vector2f constPos) {initialPos = constPos;}
void Player::setInitialPos(float cx, float cy) {initialPos = sf::Vector2f(cx, cy);}
void Player::setPos(sf::Vector2f newPos) { pos = newPos; pSprite.setPosition(pos); }
void Player::setPos(float x, float y) { pos = sf::Vector2f(x, y); pSprite.setPosition(pos); }
void Player::setTargetPos(float x, float y)
{
	targetPos = sf::Vector2f(x, y);
}
void Player::setTargetPos(sf::Vector2f newPos)
{
	targetPos = newPos;
}
void Player::move(sf::Vector2f target, float dTimeAsSeconds) 
{ 
	sf::Vector2f ppos = initialPos - 0.2f*(target-initialPos);
	pos -= (ppos - pos) * dTimeAsSeconds * 0.2f; pSprite.setPosition(pos); 
}

void Player::move(float x, float y, float dTimeAsSeconds) 
{ 
	sf::Vector2f ppos = initialPos - 0.1f*(sf::Vector2f(x, y)-initialPos);
	pos += (ppos - pos) * dTimeAsSeconds * 0.1f; pSprite.setPosition(pos); 
}
/*
Beschleunigt jetzt statt zu verlangsamen, ist aber noch langsam im Beschleunigen,
hört nicht auf zu beschleunigen und schießt über das Ziel hinaus
Wird noch verbessert
*/

bool Player::checkIfMovementValid(int side)
{
	int targetRot = target.getSprite().getRotation();
	checkCellPos(pos);
	switch (target.getType())
	{
	case 0: //slope
		switch (lastSide)
		{
		case 0:
			if ((targetRot == 0 && side == 1) || (targetRot == 90 && side == 3))
				return true;
			break;
		case 1:
			if ((targetRot == 0 && side == 0) || (targetRot == 90 && side == 2))
				return true;
			break;
		case 2:
			if ((targetRot == 0 && side == 3) || (targetRot == 90 && side == 1))
				return true;
			break;
		case 3:
			if ((targetRot == 0 && side == 2) || (targetRot == 90 && side == 0))
				return true;
			break;
		default:
			break;
		}
		break;
	case 1: //straight
		switch (lastSide)
		{
		case 0:
			if (targetRot == 90 && (side == 1 || side == 3))
				return true;
			break;
		case 1:
			if (targetRot == 0 && (side == 0 || side == 2))
				return true;
			break;
		case 2:
			if (targetRot == 90 && (side == 1 || side == 3))
				return true;
			break;
		case 3:
			if (targetRot == 0 && (side == 0 || side == 2))
				return true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
}

