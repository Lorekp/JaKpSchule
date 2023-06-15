#pragma once
#include <SFML/Graphics/Sprite.hpp>

class AssetManager;

class SubGridElement
{
public:
	int getType();
	int getSide();
	sf::Sprite& getSprite();
	void setSide(int newSide);
	void setSprite(sf::Sprite sprite);
	void setRotation(int rotation);
	SubGridElement();
protected:
	int type;
	int side;
	int rotation;
	sf::Sprite sprite;
};

