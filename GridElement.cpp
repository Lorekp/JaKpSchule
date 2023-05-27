#include "GridElement.h"

GridElement::GridElement() {

}

void GridElement::addSubGridElement(SubGridElement newSubGridElement)
{
	subGridElements.push_back(newSubGridElement);
}

std::vector<SubGridElement> GridElement::getSubGridElements()
{
	return subGridElements;
}

SubGridElement GridElement::getSubGridElementAt(int i)
{
	return subGridElements.at(i);
}

void GridElement::setSubGridElements(std::vector<SubGridElement> newSubgridElements)
{
	this->subGridElements = newSubgridElements;
}


