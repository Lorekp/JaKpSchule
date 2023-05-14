#pragma once
#include "SubGridElement.h"
#include <vector>

class GridElement
{
public:
	GridElement();

	void addSubGridElement(SubGridElement newSubGridElement);
	std::vector<SubGridElement> getSubGridElements();
	SubGridElement getSubGridElementAt(int i);
private:
	std::vector<SubGridElement> subGridElements;
};

