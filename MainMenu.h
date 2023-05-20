#pragma once
#include <vector>
#include "Grid.h"

class AssetManager;
class Slope;
class Straight;

class MainMenu{

private:
	std::vector<sf::Sprite> textures;
	Grid mainGrid;
public:
	MainMenu();
	void draw(float scale, sf::RenderWindow& window);
};
