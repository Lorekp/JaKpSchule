#pragma once
#include <vector>
#include "GridElement.h"
#include "Grid.h"

class Level {

private:
	Grid grid;

public:
	void run();
	Level(int gridSizeX, int gridSizeY);

};