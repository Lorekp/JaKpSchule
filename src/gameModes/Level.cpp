#include "Level.h"
#include "AssetManager.h"
#include "Slope.h"
#include "Straight.h"
#include "Player.h"
#include "Settings.h"

Level::Level(sf::RenderWindow& window, std::string filename) : window(window)
{
	this->scale = Settings::getScale();

	this->view = sf::View();
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(0, 0);
	view = getLetterboxView(view, window.getSize().x, window.getSize().y);

    levelGrid = AssetManager::getGrid(filename);
}

int Level::run()
{
    levelGrid.draw(window, false, true, true);
    Player player = Player(levelGrid);

    float fadePercent = 0;
    bool fullscreen = false;

    sf::Sprite background(AssetManager::getTexture(".\\resources\\white19201080.png"));
    sf::RectangleShape fadeShape = sf::RectangleShape(sf::Vector2f(1920, 1080));
    fadeShape.setFillColor(sf::Color(0, 0, 0, 0)); //make transparent fade

    //time init
    sf::Time elapsedTime;
    sf::Clock clock;

    while (window.isOpen())
    {
        this->scale = Settings::getScale();
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::MouseWheelMoved:
                if (event.mouseWheel.delta >= 1) {
                    if (view.getSize().x > 494 && view.getSize().y > 278) { view.zoom(1.f / 1.1f); }
                }
                else if (event.mouseWheel.delta <= -1) {
                    if (view.getSize().x < 1548 && view.getSize().y < 871) { view.zoom(1.1f); }
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::F11:
                    (fullscreen) ? window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth") : window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
                    fullscreen = !fullscreen;
                    break;
                case sf::Keyboard::Left:
                    player.addNextSide(3);
                    break;
                case sf::Keyboard::Right:
                    player.addNextSide(1);
                    break;
                case sf::Keyboard::Up:
                    player.addNextSide(0);
                    break;
                case sf::Keyboard::Down:
                    player.addNextSide(2);
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

        fadeShape.setPosition(view.getCenter() - sf::Vector2f(1920 / 2, 1080 / 2));
        if (player.getPos().x < -((levelGrid.getGrid().at(0).size() * 256 * scale) / 2))
        {
            float fadeDistance = (view.getSize().x / 2 - ((levelGrid.getGrid().at(0).size() * 256 * scale) / 2));
            float relativePlayerPos = (-1) * (player.getPos().x) - ((levelGrid.getGrid().at(0).size() * 256 * scale) / 2);
            fadePercent = (relativePlayerPos / fadeDistance);
            fadeShape.setFillColor(sf::Color(0, 0, 0, 255 * fadePercent));
            if (player.getPos().x < -(view.getSize().x / 2))
                if (player.getFinished())
                    return 9; //succesfully completed
                else
                    return 8; //went out-of-bounds
        }
        else if (player.getPos().x > ((levelGrid.getGrid().at(0).size() * 256 * scale) / 2))
        {
            float fadeDistance = (view.getSize().x / 2 - ((levelGrid.getGrid().at(0).size() * 256 * scale) / 2));
            float relativePlayerPos = (player.getPos().x) - ((levelGrid.getGrid().at(0).size() * 256 * scale) / 2);
            fadePercent = (relativePlayerPos / fadeDistance);
            fadeShape.setFillColor(sf::Color(0, 0, 0, 255 * fadePercent));
            if (player.getPos().x > (view.getSize().x / 2))
                if (player.getFinished())
                    return 9; //succesfully completed
                else
                    return 8; //went out-of-bounds
        }
        else if (player.getPos().y > ((levelGrid.getGrid().size() * 256 * scale) / 2))
        {

        }
        window.draw(background);
        window.draw(fadeShape);

        levelGrid.draw(window, false, true, true);
        player.move(deltaTime, false);
        player.draw(window);

        view.setCenter(player.getPos());
        window.display();
    }
}

sf::View Level::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

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