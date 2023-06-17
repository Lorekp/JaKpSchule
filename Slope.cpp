#include "Slope.h"
#include "AssetManager.h"

Slope::Slope(int rotation) {
	this->type = 0;
	this->sprite.setRotation(rotation);
	this->sprite.setTexture(AssetManager::getTexture(".\\resources\\slope.png"));
	this->boundingBox.setRotation(rotation+45);
	this->boundingBox.setSize(sf::Vector2f(13, 64));
	this->boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
	//debug Outline
	this->boundingBox.setOutlineThickness(8);
	this->boundingBox.setOutlineColor(sf::Color::Red);
}

