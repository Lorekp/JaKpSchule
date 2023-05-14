#include "MainMenu.h"
#include "Grid.h"


MainMenu::MainMenu(AssetManager manager) 
{
	textures.push_back(manager.getTexture(".\\resources\\Arrow_Up_Key_Light.png"));
	textures.push_back(manager.getTexture(".\\resources\\Arrow_Left_Key_Light.png"));
	textures.push_back(manager.getTexture(".\\resources\\Arrow_Right_Key_Light.png"));
	textures.push_back(manager.getTexture(".\\resources\\Arrow_Down_Key_Light.png"));
	textures.push_back(manager.getTexture(".\\resources\\slope.png"));
	textures.push_back(manager.getTexture(".\\resources\\straight.png"));

	Grid mainGrid(4, 4);
	mainGrid.addSubGridElementAt(0, 0, Slope(0));
	mainGrid.addSubGridElementAt(1, 0, Straight(2));
	mainGrid.addSubGridElementAt(3, 0, Slope(270));
	mainGrid.addSubGridElementAt(0, 3, Straight(2));
	mainGrid.addSubGridElementAt(3, 3, Slope(90));
	manager.serializeGrid(".\\levels\\mainGrid.labdat", mainGrid.getGrid());
	mainGrid = manager.getGrid(".\\levels\\mainGrid.labdat");
	mainGrid.printGrid();

}

std::vector<sf::Texture>& MainMenu::GetTextures()
{
	return textures;
}