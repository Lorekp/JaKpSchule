#pragma once
#include "Grid.h"
#include "Player.h"

class AssetManager;
class Slope;
class Straight;
class Player;

class Level {

private:
	Grid levelGrid;
	float scale;
	sf::RenderWindow& window;
	sf::View view;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
public:
	int run();
	Level(sf::RenderWindow& window, std::string filename);

};