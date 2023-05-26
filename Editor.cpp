#include "Editor.h"
#include "AssetManager.h"
#include <iostream>

Editor::Editor(std::string const& filename, sf::RenderWindow& window) : window(window)
{
	grid = AssetManager::getGrid(filename);
}

Editor::Editor(sf::RenderWindow& window) : window(window)
{

    this->view = sf::View();
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(0, 0);
    view = getLetterboxView(view, window.getSize().x, window.getSize().y);

    this->grid = Grid(4, 4);
}

void Editor::run()
{
    bool isInMovement{false};
    bool fullscreen = false;
    bool upFlag = false, downFlag = false, leftFlag = false, rightFlag = false; //movement flags
    float camSpeed = 500;
    float scale = 0.25f;

    sf::Sprite background(AssetManager::getTexture(".\\resources\\white19201080.png"));

    //time init
    sf::Time elapsedTime;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::F11:
                    (fullscreen) ? window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth") : window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
                    fullscreen = !fullscreen;
                    break;
                case sf::Keyboard::W: upFlag = true; break;
                case sf::Keyboard::A: leftFlag = true; break;
                case sf::Keyboard::S: downFlag = true; break;
                case sf::Keyboard::D: rightFlag = true; break;
                case sf::Keyboard::T: isInMovement = true; break;
                case sf::Keyboard::P: playerExists = !playerExists; break;
                case sf::Keyboard::R: player.setPos(-32, -32); break;
                default:
                    break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::W: upFlag = false; break;
                case sf::Keyboard::A: leftFlag = false; break;
                case sf::Keyboard::S: downFlag = false; break;
                case sf::Keyboard::D: rightFlag = false; break;
                case sf::Keyboard::T: isInMovement = false; break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseWheelMoved:
                if (event.mouseWheel.delta >= 1) {
                    if (view.getSize().x > 494 && view.getSize().y > 278) { view.zoom(1.f / 1.1f); }
                }
                else if (event.mouseWheel.delta <= -1) {
                    if (view.getSize().x < 1548 && view.getSize().y < 871) { view.zoom(1.1f); }
                }
                break;
            case sf::Event::MouseButtonReleased:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Right:
                {
                    //checking if mouse clicked in any of the cells
                    float gridSizeX = grid.getGrid().size() * 256 * scale;
                    float gridSizeY = grid.getGrid().at(0).size() * 256 * scale;
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    for (int i = 0; i < grid.getGrid().size(); i++)
                    {
                        for (int j = 0; j < grid.getGrid().at(0).size(); j++)
                        {
                            if ((j * 256 * scale -(gridSizeX / 2)) < mousePos.x && mousePos.x < (j * 256 * scale + 256 * scale - (gridSizeX / 2)) &&
                                (i * 256 * scale -(gridSizeY / 2)) < mousePos.y && mousePos.y < (i * 256 * scale + 256 * scale - (gridSizeY / 2)))
                            {
                                //do something with x = i and y = j
                            }
                        }
                    }
                    
                }
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
            }
        }
        //accumulate time
        elapsedTime += deltaTime;
        float timeAsSeconds = elapsedTime.asSeconds();
        float dTimeAsSeconds = deltaTime.asSeconds();

        //cam movement
        if (upFlag)
            view.move(0, -camSpeed * dTimeAsSeconds);
        if (leftFlag)
            view.move(-camSpeed * dTimeAsSeconds, 0);
        if (downFlag)
            view.move(0, camSpeed * dTimeAsSeconds);
        if (rightFlag)
            view.move(camSpeed * dTimeAsSeconds, 0);

        //checking boundries of cam
        if (view.getCenter().x < -(grid.getGrid().size() * 256 * scale * 1.92f))
            view.setCenter(-(grid.getGrid().size() * 256 * scale * 1.92f), view.getCenter().y);
        if (view.getCenter().x > (grid.getGrid().size() * 256 * scale * 1.92f))
            view.setCenter((grid.getGrid().size() * 256 * scale * 1.92f), view.getCenter().y);
        if (view.getCenter().y < -(grid.getGrid().at(0).size() * 256 * scale * 1.08f))
            view.setCenter(view.getCenter().x, -(grid.getGrid().at(0).size() * 256 * scale * 1.08f));
        if (view.getCenter().y > (grid.getGrid().at(0).size() * 256 * scale * 1.08f))
            view.setCenter(view.getCenter().x, (grid.getGrid().at(0).size() * 256 * scale * 1.08f));

        if(isInMovement)    player.move(256, 256);
        window.clear();
        window.setView(view);

        //move the background to camera
        background.setPosition(view.getCenter() - sf::Vector2f(1920 / 2, 1080 / 2));
        window.draw(background);

        draw(scale, window);

        window.display();
        //std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << '\n';
    }
}

void Editor::draw(float scale, sf::RenderWindow& window)
{
    grid.draw(scale, window, true);
    if(playerExists)    player.draw(window, scale);
}

sf::View Editor::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

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

sf::View Editor::disableLetterboxView(sf::View view) {

    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    return view;
}
