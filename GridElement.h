#pragma once

#include <vector>

#include "SubGridElement.h"

class GridElement
{
public:
	GridElement();

	void addSubGridElement(SubGridElement newSubGridElement);
	void removeSubGridElement();
	std::vector<SubGridElement> getSubGridElements();
	SubGridElement getSubGridElementAt(int i);
private:
	std::vector<SubGridElement> subGridElements;
};

