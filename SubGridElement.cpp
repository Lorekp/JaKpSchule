#include "SubGridElement.h"
#include "AssetManager.h"

int SubGridElement::getType()
{
    return type;
}

int SubGridElement::getSide()
{
    return side;
}

int SubGridElement::getRotation()
{
    return rotation;
}

sf::Sprite& SubGridElement::getSprite()
{
    return sprite;
}

void SubGridElement::setSide(int newSide)
{
    this->side = newSide;
}

SubGridElement::SubGridElement()
{
    this->sprite.setTexture(AssetManager::getTexture(".\\resources\\empty256.png"));
    this->type = -1;
    this->side = 0;
    this->rotation = 0;
}
