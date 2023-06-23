#include "Straight.h"
#include "AssetManager.h"

Straight::Straight(int side)
{
	this->type = 1;
	this->side = side;
	this->sprite = sf::Sprite();
	this->sprite.setTexture(AssetManager::getTexture(".\\resources\\straight.png"));
	this->boundingBox = sf::RectangleShape();
	this->boundingBox.setSize(sf::Vector2f(13, 64));
	this->boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
	//debug Outline
	this->boundingBox.setOutlineThickness(8);
	this->boundingBox.setOutlineColor(sf::Color::Red);
}
