#include "MainMenu.h"
#include "AssetManager.h"
#include "Slope.h"
#include "Straight.h"
#include "Player.h"


MainMenu::MainMenu(float scale, sf::RenderWindow& window) : window(window)
{
	//texture init
	AssetManager::getTexture(".\\resources\\slope.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\straight.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Right_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Left_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Up_Key_Light.png").setSmooth(true);
	AssetManager::getTexture(".\\resources\\Arrow_Down_Key_Light.png").setSmooth(true);
	mainGrid = AssetManager::getGrid(".\\levels\\mainGrid.labdat");

	this->scale = scale;
    this->doRun = true;

	this->view = sf::View();
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(0, 0);
	view = getLetterboxView(view, window.getSize().x, window.getSize().y);

}

void MainMenu::run()
{
    Player player = Player(mainGrid);

    bool fullscreen = false;

    sf::Sprite background(AssetManager::getTexture(".\\resources\\white19201080.png"));

    //time init
    sf::Time elapsedTime;
    sf::Clock clock;

    while (window.isOpen() && doRun)
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::F11:
                    (fullscreen) ? window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth") : window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
                    fullscreen = !fullscreen;
                    break;
                default:
                    break;
                }
                break;
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

        elapsedTime += deltaTime;
        float etimeAsSeconds = elapsedTime.asSeconds();


        window.clear();
        window.setView(view);

        background.setPosition(view.getCenter() - sf::Vector2f(1920 / 2, 1080 / 2));

        window.draw(background);

        draw(scale, window);
        player.move(deltaTime);
        player.draw(window, scale);

        window.display();
    }
}

void MainMenu::draw(float scale, sf::RenderWindow& window)
{
	mainGrid.draw(scale, window, false, false, false);
}

float MainMenu::getScale() {
    return scale;
}

sf::View MainMenu::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

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