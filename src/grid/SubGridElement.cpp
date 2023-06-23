#include "SubGridElement.h"
#include "utils/AssetManager.h"

int SubGridElement::getType()
{
    return type;
}

int SubGridElement::getSide()
{
    return side;
}

sf::Sprite& SubGridElement::getSprite()
{
    return sprite;
}

sf::RectangleShape& SubGridElement::getBoundingBox()
{
    return boundingBox;
}

void SubGridElement::setSide(int newSide)
{
    this->side = newSide;
}

void SubGridElement::setSprite(sf::Sprite sprite)
{
    this->sprite = sprite;
}

void SubGridElement::setBoundingBox(sf::RectangleShape boundingBox)
{
    this->boundingBox = boundingBox;
}

void SubGridElement::setRotation(int rotation)
{
    this->sprite.setRotation(rotation);
}

SubGridElement::SubGridElement()
{
    this->sprite.setTexture(AssetManager::getTexture(".\\resources\\grid.png"));
    this->type = -1;
    this->side = 0;
    this->rotation = 0;
}

bool SubGridElement::operator!=(const SubGridElement& compare) const
{
    return compare.sprite.getPosition() != this->sprite.getPosition();
}
