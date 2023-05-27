#include "Slope.h"
#include "AssetManager.h"

Slope::Slope(int rotation) {
	this->type = 0;
	this->sprite.setRotation(rotation);
	this->sprite.setTexture(AssetManager::getTexture(".\\resources\\slope.png"));
}

