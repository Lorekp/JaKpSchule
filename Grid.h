#include <vector>

class Grid {

private:
	std::vector<std::vector<int>> grid;

	unsigned concatenate(unsigned x, unsigned y);

public:
	void setGridValueAt(int x, int y, int newValue, int rotationDeg, int offsetx, int offsety);
	int getGridValueAt(int x, int y);
	Grid(int gridSize);

};
