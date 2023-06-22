#pragma once
#include <vector>
#include "Grid.h"
#include "Player.h"

class AssetManager;
class Slope;
class Straight;
class Player;

class MainMenu{

private:
	std::vector<sf::Sprite> textures;
	Grid mainGrid;
	float scale;
	sf::RenderWindow& window;
	sf::View view;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	void draw(sf::RenderWindow& window);
public:
	MainMenu(sf::RenderWindow& window);
	int run();
};
