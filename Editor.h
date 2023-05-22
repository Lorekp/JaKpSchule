#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.h"



class Editor
{
public:
	Editor(std::string const& filename);
	Editor();
	void draw(float scale, sf::RenderWindow& window);
private:
	Grid grid;
};

