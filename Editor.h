#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"
#include "Player.h"



class Editor
{
public:
	Editor(std::string const& filename, sf::RenderWindow& window);
	Editor(sf::RenderWindow& window);
	void run();
	void draw(float scale, sf::RenderWindow& window);
	void addElementToGrid(unsigned int x, unsigned int y);
	void addElementToGrid(sf::Vector2u coords);
	sf::Vector2u getGridCell(float scale, sf::RenderWindow& window);

private:
    bool playerExists{false};
	Grid grid;
	Player player;
	sf::View view;
	sf::RenderWindow& window;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	sf::View disableLetterboxView(sf::View view);
};

