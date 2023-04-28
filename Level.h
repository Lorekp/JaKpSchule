#pragma once
#include <vector>

class Level {

private:
	std::vector<std::vector<int>> grid;

public:
	void run();
	Level(int gridSize);
	Level(std::vector<std::vector<int>> grid);

};