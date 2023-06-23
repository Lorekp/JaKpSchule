#pragma once

#include <vector>

#include "SubGridElement.h"

class GridElement
{
public:
	GridElement();

	void addSubGridElement(SubGridElement newSubGridElement);
	std::vector<SubGridElement> getSubGridElements();
	SubGridElement& getSubGridElementAt(int i);
	void setSubGridElements(std::vector<SubGridElement> newSubgridElements);
private:
	std::vector<SubGridElement> subGridElements;
};

