#pragma once
#include "AssetManager.h"
#include "Grid.h"
#include "Slope.h"
#include "Straight.h"
#include <vector>

class MainMenu{

private:
	std::vector<sf::Sprite> textures;
	Grid mainGrid;
public:
	MainMenu();
	void draw(float scale, sf::RenderWindow& window);
};
