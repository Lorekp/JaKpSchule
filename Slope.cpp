#include "Slope.h"

Slope::Slope(int rotation) {
	this->type = 0;
	this->rotation = rotation;
	this->sprite.setTexture(AssetManager::getTexture(".\\resources\\slope.png"));
}

