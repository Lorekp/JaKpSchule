#include "Editor.h"
#include "AssetManager.h"
#include <iostream>


Editor::Editor(std::string const& filename, sf::RenderWindow& window) : window(window)
{
	grid = AssetManager::getGrid(filename);
    this->player = Player();
}

Editor::Editor(sf::RenderWindow& window) : window(window)
{

    this->view = sf::View();
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(0, 0);
    view = getLetterboxView(view, window.getSize().x, window.getSize().y);

    this->grid = Grid(4, 4);
    this->player = Player();
}

void Editor::run()
{
    bool control{false};
    bool slopeStraightDelete{false}; 
    int slopeOrStraight{0}; //decides whether the settings for putting in the gridElements are active
    sf::Vector2u clickedCellCoords; //the grid coordinates of the latest clicked grid cell
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
                case sf::Keyboard::LControl: control=true; break;
                case sf::Keyboard::W: upFlag = true; break;
                case sf::Keyboard::A: leftFlag = true; break;
                case sf::Keyboard::S: if(control)   grid.saveGrid();
                downFlag = true; break;
                case sf::Keyboard::D: rightFlag = true; break;
                case sf::Keyboard::T: isInMovement = true; break;
                case sf::Keyboard::P: playerExists = !playerExists; break;
                case sf::Keyboard::R: player.setPos(-32, -32); break;
                case sf::Keyboard::Num0: if(slopeStraightDelete)  grid.removeSubGridElementAt(clickedCellCoords);
                                           break;
                case sf::Keyboard::Num1: if(slopeOrStraight== -1)   grid.addSubGridElementAt(clickedCellCoords, Straight(0)); 
                                         else if(slopeOrStraight== 1)   grid.addSubGridElementAt(clickedCellCoords, Slope(0));
                                         slopeStraightDelete=false; slopeOrStraight=false;
                                         break;
                case sf::Keyboard::Num2: if(slopeStraightDelete&&slopeOrStraight==0)  slopeOrStraight=-1; 
                                         else if(slopeOrStraight== -1)   {grid.addSubGridElementAt(clickedCellCoords, Straight(1)); slopeStraightDelete=false; slopeOrStraight=false;}
                                         else if(slopeOrStraight== 1)   {grid.addSubGridElementAt(clickedCellCoords, Slope(1)); slopeStraightDelete=false; slopeOrStraight=false;}
                                         break;
                case sf::Keyboard::Num3: if(slopeStraightDelete&&slopeOrStraight==0)  slopeOrStraight=1; 
                                         else if(slopeOrStraight== -1)   {grid.addSubGridElementAt(clickedCellCoords, Straight(2)); slopeStraightDelete=false; slopeOrStraight=false;}
                                         else if(slopeOrStraight== 1)   {grid.addSubGridElementAt(clickedCellCoords, Slope(2)); slopeStraightDelete=false; slopeOrStraight=false;}
                                         break;
                case sf::Keyboard::Num4: if(slopeOrStraight== -1)   grid.addSubGridElementAt(clickedCellCoords, Straight(3)); 
                                         else if(slopeOrStraight== 1)   grid.addSubGridElementAt(clickedCellCoords, Slope(3)); 
                                         slopeStraightDelete=false; slopeOrStraight=false;
                                         break;
                case sf::Keyboard::Escape: slopeStraightDelete=false; slopeOrStraight=false; break;
                default:
                    break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::LControl: control=false; break;
                case sf::Keyboard::W: upFlag = false; break;
                case sf::Keyboard::A: leftFlag = false; break;
                case sf::Keyboard::S: downFlag = false; break;
                case sf::Keyboard::D: rightFlag = false; break;
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
                    clickedCellCoords = getGridCell(scale, window);
                    slopeStraightDelete = true;
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

        if(isInMovement)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            player.move(mousePos);
        }

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

void Editor::addElementToGrid(unsigned int x, unsigned int y)
{
    
}
void Editor::addElementToGrid(sf::Vector2u coords)
{
    
}

sf::Vector2u Editor::getGridCell(float scale, sf::RenderWindow& window)
{
    //checking if mouse clicked in any of the cells
    sf::Vector2f gridSizeInWindow = static_cast<sf::Vector2f>(grid.getFullSize()) * 256.0f * scale;
    float sizeOfOneCell = 256.0f*scale;
    sf::Vector2f mousePosToGrid = window.mapPixelToCoords(sf::Mouse::getPosition(window)) + gridSizeInWindow*0.5f;

    unsigned int x{static_cast<unsigned int>(mousePosToGrid.x / sizeOfOneCell)};
    unsigned int y{static_cast<unsigned int>(mousePosToGrid.y / sizeOfOneCell)};

    return sf::Vector2u(x, y);
    //grid.addSubGridElementAt(x, y, Slope(0));
}