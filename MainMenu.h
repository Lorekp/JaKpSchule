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
	float scale;
	bool doRun;
	sf::RenderWindow& window;
	sf::View view;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	void draw(float scale, sf::RenderWindow& window);
public:
	MainMenu(float scale, sf::RenderWindow& window);
	void run();

	float getScale();
};
