#include "GridElement.h"

GridElement::GridElement() {

}

void GridElement::addSubGridElement(SubGridElement newSubGridElement)
{
	subGridElements.push_back(newSubGridElement);
}

void GridElement::removeSubGridElement()
{
	subGridElements.pop_back();
}

std::vector<SubGridElement> GridElement::getSubGridElements()
{
	return subGridElements;
}

SubGridElement GridElement::getSubGridElementAt(int i)
{
	return subGridElements.at(i);
}
