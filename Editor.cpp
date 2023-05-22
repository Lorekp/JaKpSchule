#include "Editor.h"
#include "AssetManager.h"

Editor::Editor(std::string const& filename)
{
	grid = AssetManager::getGrid(filename);
}

Editor::Editor()
{
	grid = Grid(4, 4);
}

void Editor::draw(float scale, sf::RenderWindow& window)
{
	grid.draw(scale, window, true);
}


