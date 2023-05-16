#include "MainMenu.h"
#include "Grid.h"


MainMenu::MainMenu(AssetManager manager) 
{
	mainGrid = manager.getGrid(".\\levels\\mainGrid.labdat");

	
}

void MainMenu::draw(float windowX, float windowY, float scale, sf::RenderWindow& window)
{
	mainGrid.draw(windowX, windowY, scale, window);
}
