#include "EditorMenu.h"

EditorMenu::EditorMenu(tgui::Gui& gui, sf::RenderWindow& window) : gui(gui), window(window)
{
	
}

int EditorMenu::run()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		gui.draw();

		window.display();
	}
	return -1;
}

