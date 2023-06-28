#include "EditorMenu.h"
#include "utils/Settings.h"
#include "grid/Grid.h"
#include "utils/AssetManager.h"
#include "sys/stat.h"
#include <filesystem>

EditorMenu::EditorMenu(tgui::Gui& gui, sf::RenderWindow& window) : gui(gui), window(window)
{
	this->view = sf::View();
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(0, 0);
	gui.setAbsoluteView(tgui::FloatRect(0,0, 1920, 1080));
	view = getLetterboxView(view, window.getSize().x, window.getSize().y);

	doRun = true;
	returnType = 0; //return 0 for mainMenu
	try
	{
		gui.loadWidgetsFromFile(".\\resources\\forms\\EditorMenuForm.txt");
		gui.get<tgui::BitmapButton>("Back")->onPress([&] {doRun = false; returnType = 11; });
		gui.get<tgui::BitmapButton>("NewLevel")->onPress([&] {addNewLevel(); });
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

		int savesAmount = 0;
		for (const auto& entry : std::filesystem::directory_iterator(".\\saves"))
		{
			bool isNewEntry = true;
			for (int i = 0; i < levelList.size(); i++)
			{
				if (levelList.at(i)->getText() == std::u8string(std::filesystem::path(entry.path()).stem().u8string()))
					isNewEntry = false;
			}
			if (isNewEntry)
			{
				try
				{
					auto group = tgui::Group::create({ "430", "40" });
					group->setPosition({ "600", "420" });
					gui.add(group);

					auto label = tgui::Label::create(std::u8string(std::filesystem::path(entry.path()).stem().u8string())); //using filename
					label->setPosition({ "0", "10" });
					label->setTextSize(Settings::getFontSize());
					group->add(label);

					levelList.push_back(label);

					/*auto buttonEdit = tgui::Button::create("E");
					buttonEdit->setSize({"2%", "2%"});
					buttonEdit->setPosition({ "51.125%", "32.8695%" });
					group->add(buttonEdit);*/
				}
				catch (const tgui::Exception& e)
				{
					std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
				}
			}
			savesAmount += 1;
		}
		if (savesAmount < levelList.size())
		{
				for (int i = 0; i < levelList.size(); i++)
				{
					for (const auto& entry : std::filesystem::directory_iterator(".\\saves"))
					{
						if (!(levelList.at(i)->getText() == std::u8string(std::filesystem::path(entry.path()).stem().u8string())))
							levelList.at(i)->getParent()->~Container();
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

	gui.setRelativeViewport(tgui::FloatRect((posX), (posY), sizeX, sizeY));
	view.setViewport(sf::FloatRect((posX), (posY), sizeX, sizeY));

	return view;
}

void EditorMenu::addNewLevel()
{
	std::string filename = ".\\saves\\newLevel.labdat";
	if (isFileExist(filename)) {
		std::string filenameEnd = ").labdat";
		int amount = 0;
		for (int i = 1; isFileExist(std::string(".\\saves\\newLevel(") + std::to_string(i) + filenameEnd); i++)
		{
			amount = i + 1;
		}
		if (amount != 0)
			filename = std::string(".\\saves\\newLevel(") + std::to_string(amount) + filenameEnd;
		else
			filename = std::string(".\\saves\\newLevel(") + '1' + filenameEnd;
	}
	Grid grid(4, 4);
	AssetManager::serializeGrid(filename, grid);
}

bool EditorMenu::isFileExist(std::string path)
{
#if defined(_WIN32)
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
#else 
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
#endif
}