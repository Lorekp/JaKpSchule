#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class EditorMenu
{
public:
	EditorMenu(tgui::Gui& gui, sf::RenderWindow& window);
	int run();

private:
	tgui::Gui& gui;
	sf::RenderWindow& window;

	bool doRun;
	int returnType;

	sf::View view;

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
	void addNewLevel();
};

