#include "MainMenu.h"
#include "Grid.h"


MainMenu::MainMenu() 
{
	//texture init
	AssetManager::getTexture(".\\resources\\slope.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\straight.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Right_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Left_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Up_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Down_Key_Light.png").setSmooth(true);
	mainGrid = AssetManager::getGrid(".\\levels\\mainGrid.labdat");
}

void MainMenu::draw(float windowX, float windowY, float scale, sf::RenderWindow& window)
{
	mainGrid.draw(windowX, windowY, scale, window);
}
