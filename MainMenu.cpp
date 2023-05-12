#include "MainMenu.h"


MainMenu::MainMenu(AssetManager manager) 
{
	textures.push_back(manager.GetTexture(".\\resources\\Arrow_Up_Key_Light.png"));
	textures.push_back(manager.GetTexture(".\\resources\\Arrow_Left_Key_Light.png"));
	textures.push_back(manager.GetTexture(".\\resources\\Arrow_Right_Key_Light.png"));
	textures.push_back(manager.GetTexture(".\\resources\\Arrow_Down_Key_Light.png"));
	textures.push_back(manager.GetTexture(".\\resources\\slope.png"));
	textures.push_back(manager.GetTexture(".\\resources\\straight.png"));

	Grid mainGrid(4);
}

std::vector<sf::Texture>& MainMenu::GetTextures()
{
	return textures;
}