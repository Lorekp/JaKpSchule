#include "Straight.h"
#include "AssetManager.h"

Straight::Straight(int side)
{
	this->type = 1;
	this->side = side;
	this->sprite.setTexture(AssetManager::getTexture(".\\resources\\straight.png"));
}
