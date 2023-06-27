#include "EditorMenu.h"
#include "utils/Settings.h"
#include "grid/Grid.h"
#include "utils/AssetManager.h"

EditorMenu::EditorMenu(tgui::Gui& gui, sf::RenderWindow& window) : gui(gui), window(window)
{
	this->view = sf::View();
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(0, 0);
	view = getLetterboxView(view, window.getSize().x, window.getSize().y);

	doRun = true;
	returnType = 0; //return 0 for mainMenu
	try
	{
		gui.loadWidgetsFromFile(".\\resources\\forms\\EditorMenuForm.txt");
		gui.get<tgui::Button>("Back")->onPress([&] {doRun = false; returnType = 11; });
		gui.get<tgui::Button>("NewLevel")->onPress([&] {addNewLevel(); });
		
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
	}

}

int EditorMenu::run()
{
	sf::RectangleShape background(sf::Vector2f(1920, 1080));
	background.setFillColor(sf::Color(198, 198, 198, 255));

	while (window.isOpen() && doRun)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (!gui.handleEvent(event)) //if gui didnt handle event
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					view = getLetterboxView(view, event.size.width, event.size.height);
					break;
				default:
					break;
				}
			}
		}

		window.clear();
		window.setView(view);

		background.setPosition(view.getCenter() - sf::Vector2f(1920 / 2, 1080 / 2));

		window.draw(background);
		gui.draw();

		window.display();
	}
	return returnType;
}

sf::View EditorMenu::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.
	// A new view (with a new viewport set) is returned.

	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}


	view.setViewport(sf::FloatRect((posX), (posY), sizeX, sizeY));

	return view;
}

void EditorMenu::addNewLevel()
{
	std::string filename;
	Grid grid(4, 4);
	AssetManager::serializeGrid(filename, grid);
}