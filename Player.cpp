#include "Player.h"
#include "AssetManager.h"


Player::Player(Grid& grid) : grid(grid)
{
	this->pSprite = sf::Sprite(AssetManager::getTexture(".\\resources\\blackBall.png"));
	pSprite.setOrigin(128, 128);
	
}

void Player::draw(sf::RenderWindow& window, float scale)
{
	pSprite.setScale(scale, scale);
	window.draw(pSprite);
}

void Player::move()
{
}

