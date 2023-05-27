#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"
#include "SubGridElement.h"



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
	sf::Vector2i hoveredCell;
	int hoveredSymbol;
	bool hoverPlace;
	bool drawStart;
	bool drawFinish;
	bool drawStartPossibilities;
	SubGridElement hoverElement;
	sf::Sprite resizeSymbols[8];
	std::vector<std::vector<sf::Sprite>> startPossibilites;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	sf::View disableLetterboxView(sf::View view);
	bool checkHoveredCell();
	bool checkHoveredSymbol(int mouseX, int mouseY);
	bool checkForStraight(int side);
};

