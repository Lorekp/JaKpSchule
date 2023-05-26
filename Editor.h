#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"



class Editor
{
public:
	Editor(std::string const& filename, sf::RenderWindow& window);
	Editor(sf::RenderWindow& window);
	void run();
	void draw(float scale, sf::RenderWindow& window);

private:
	float scale;
	Grid grid;
	sf::View view;
	sf::RenderWindow& window;
	sf::Vector2i clickedCell;
	bool hoverPlace;
	SubGridElement hoverElement;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	sf::View disableLetterboxView(sf::View view);
	bool checkClickedCell();
};

