#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class AssetManager;

class SubGridElement
{
public:
	int getType();
	int getSide();
	sf::Sprite getSprite();
	sf::RectangleShape getBoundingBox();
	void setSide(int newSide);
	void setSprite(sf::Sprite sprite);
	void setRotation(int rotation);
	SubGridElement();
protected:
	int type;
	int side;
	int rotation;
	sf::Sprite sprite;
	sf::RectangleShape boundingBox;
};

