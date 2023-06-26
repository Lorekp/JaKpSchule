#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class EditorMenu
{
public:
	EditorMenu(tgui::Gui& gui, sf::RenderWindow& window);

private:
	tgui::Gui& gui;
	sf::RenderWindow& window;
};

