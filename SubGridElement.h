#pragma once
#include <SFML/Graphics/Sprite.hpp>

class AssetManager;

class SubGridElement
{
public:
	int getType();
	int getSide();
	int getRotation();
	sf::Sprite& getSprite();
	void setSide(int newSide);
	void setSprite(sf::Sprite sprite);
	void setRotation(int rotation);
	SubGridElement();
protected:
	int type;
	int rotation;
	int side;
	sf::Sprite sprite;
};

