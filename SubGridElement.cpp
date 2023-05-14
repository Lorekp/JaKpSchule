#include "SubGridElement.h"

int SubGridElement::getRotation()
{
    return rotation;
}

int SubGridElement::getType()
{
    return type;
}

int SubGridElement::getSide()
{
    return side;
}

void SubGridElement::setSide(int newSide)
{
    this->side = newSide;
}

void SubGridElement::setRotation(int newRotation)
{
    this->rotation = newRotation;
}

SubGridElement::SubGridElement()
{
    this->type = -1;
}
