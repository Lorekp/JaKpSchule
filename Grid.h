#include <vector>

class Grid {

private:
	std::vector<std::vector<int>> grid;

public:
	void setGridValueAt(int x, int y, int newValue);
	int getGridValueAt(int x, int y);
	Grid(int gridSize);

};
