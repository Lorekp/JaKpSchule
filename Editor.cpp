#include "Editor.h"
#include "AssetManager.h"
#include "Slope.h"
#include "Straight.h"

Editor::Editor(std::string const& filename, sf::RenderWindow& window) : window(window)
{
    grid = AssetManager::getGrid(filename);
}

Editor::Editor(sf::RenderWindow& window) : window(window)
{
    scale = 0.25f;

    this->hoveredCell = sf::Vector2i(-1, -1);
    this->hoverPlace = false;

    this->view = sf::View();
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(0, 0);
    view = getLetterboxView(view, window.getSize().x, window.getSize().y);

    this->grid = Grid(4, 4);

    //setup resizeSymbols
    for (int i = 0; i < 4; i++) {
        resizeSymbols[i] = sf::Sprite(AssetManager::getTexture(".\\resources\\plusEmpty.png"));
        resizeSymbols[i].setOrigin(128, 128);
        resizeSymbols[i].setScale(scale, scale);
    }
    for (int i = 4; i < 8; i++)
    {
        resizeSymbols[i] = sf::Sprite(AssetManager::getTexture(".\\resources\\minusEmpty.png"));
        resizeSymbols[i].setOrigin(128, 128);
        resizeSymbols[i].setScale(scale, scale);
    }

    this->drawStart = true;
    this->drawFinish = true;
    this->drawStartPossibilities = false;

    //setupStartPossibilities
    for (int i = 0; i < 4; i++)
    {
        startPossibilites.push_back(std::vector<sf::Sprite>());
        for (int j = 0; j < 4; j++)
        {
            startPossibilites.at(i).push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
        }
    }
}

void Editor::run()
{
    bool fullscreen = false;
    bool upFlag = false, downFlag = false, leftFlag = false, rightFlag = false; //movement flags
    float camSpeed = 500;

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
                case sf::Keyboard::R: 
                {
                    if (checkHoveredCell())
                    {
                        if (hoverElement.getType() == 0)
                            hoverElement.setRotation(hoverElement.getSprite().getRotation() + 90);
                        else if (hoverElement.getType() == 1) {
                            (hoverElement.getSide() + 1 > 3) ? (hoverElement.setSide(0)) : (hoverElement.setSide(hoverElement.getSide() + 1));
                            hoverElement.setRotation((hoverElement.getSide()+ 1)*90);
                        }
                    }
                    break; 
                }
                case sf::Keyboard::F: 
                {
                    if (hoverElement.getType() == 1 && hoverPlace) {
                        hoverElement = Slope(0);
                        hoverElement.setSprite(sf::Sprite(AssetManager::getTexture(".\\resources\\slopeLowOp.png")));
                        hoverElement.getSprite().setOrigin(128, 128);
                    }
                    else if (!hoverPlace) {
                        hoverElement = Slope(0);
                        hoverElement.setSprite(sf::Sprite(AssetManager::getTexture(".\\resources\\slopeLowOp.png")));
                        hoverElement.getSprite().setOrigin(128, 128);
                        hoverPlace = true;
                    }
                    else if (hoverPlace)
                        hoverPlace = false;
                    break; 
                }
                case sf::Keyboard::G: 
                {
                    if (hoverElement.getType() == 0 && hoverPlace) {
                        hoverElement = Straight(0);
                        hoverElement.setSprite(sf::Sprite(AssetManager::getTexture(".\\resources\\straightLowOp.png")));
                        hoverElement.getSprite().setOrigin(128, 128);
                        hoverElement.getSprite().setRotation(90);
                    }
                    else if (!hoverPlace) {
                        hoverElement = Straight(0);
                        hoverElement.setSprite(sf::Sprite(AssetManager::getTexture(".\\resources\\straightLowOp.png")));
                        hoverElement.getSprite().setOrigin(128, 128);
                        hoverElement.getSprite().setRotation(90);
                        hoverPlace = true;
                    }
                    else if (hoverPlace)
                        hoverPlace = false;
                    break;
                }
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
                    //TODO: do something

                }
                case sf::Mouse::Left:
                {
                    if (hoverPlace)
                        if (checkHoveredCell())
                            if (hoverElement.getType() == 0) {
                                if (!grid.checkForSubGridElement(hoveredCell.x, hoveredCell.y, 0))
                                    grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y, Slope(hoverElement.getSprite().getRotation()));
                            }
                            else if (hoverElement.getType() == 1)
                                if (!grid.checkForSubGridElementAndSide(hoveredCell.x, hoveredCell.y, 1, hoverElement.getSide()) && !checkForStraight(hoverElement.getSide()))
                                    grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y, Straight(hoverElement.getSide()));
                    if (checkHoveredSymbol(event.mouseButton.x, event.mouseButton.y))
                        switch (hoveredSymbol)
                        {
                        case 0: grid.addColumnToGrid(); break;
                        case 1: grid.addColumnToGrid(); grid.moveGridRight(); break;
                        case 2: grid.addRowToGrid(); break;
                        case 3: grid.addRowToGrid(); grid.moveGridDown(); break;
                        case 4: grid.removeColumnFromGrid(grid.getGrid().at(0).size()); break;
                        case 5: grid.removeColumnFromGrid(1); break;
                        case 6: grid.removeRowFromGrid(grid.getGrid().size()); break;
                        case 7: grid.removeRowFromGrid(1); break;
                        case 8: drawStart = false; drawStartPossibilities = true; break;
                        default:
                            break;
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
        float etimeAsSeconds = elapsedTime.asSeconds();
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
        if (view.getCenter().x < -(grid.getGrid().size() * 256 * scale) / 2)
            view.setCenter(-(grid.getGrid().size() * 256 * scale) / 2, view.getCenter().y);
        if (view.getCenter().x > (grid.getGrid().size() * 256 * scale) / 2)
            view.setCenter((grid.getGrid().size() * 256 * scale) / 2, view.getCenter().y);
        if (view.getCenter().y < -(grid.getGrid().at(0).size() * 256 * scale) / 2)
            view.setCenter(view.getCenter().x, -(grid.getGrid().at(0).size() * 256 * scale) / 2);
        if (view.getCenter().y > (grid.getGrid().at(0).size() * 256 * scale) / 2)
            view.setCenter(view.getCenter().x, (grid.getGrid().at(0).size() * 256 * scale) / 2);

        window.clear();
        window.setView(view);

        //move the background to camera
        background.setPosition(view.getCenter() - sf::Vector2f(1920 / 2, 1080 / 2));
        window.draw(background);


        //move plusSymbols
        resizeSymbols[0].setPosition((grid.getGrid().at(0).size() * 256 * scale) / 2 + 256 * scale, 0);
        resizeSymbols[1].setPosition(-256 * scale - (grid.getGrid().at(0).size() * 256 * scale) / 2, 0);
        resizeSymbols[2].setPosition(0, (grid.getGrid().size() * 256 * scale) / 2 + 256 * scale);
        resizeSymbols[3].setPosition(0, -256 * scale - (grid.getGrid().size() * 256 * scale) / 2);

        //move minusSymbols
        resizeSymbols[4].setPosition((grid.getGrid().at(0).size() * 256 * scale) / 2 + 512 * scale, 0);
        resizeSymbols[5].setPosition(-512 * scale - (grid.getGrid().at(0).size() * 256 * scale) / 2, 0);
        resizeSymbols[6].setPosition(0, (grid.getGrid().size() * 256 * scale) / 2 + 512 * scale);
        resizeSymbols[7].setPosition(0, -512 * scale - (grid.getGrid().size() * 256 * scale) / 2);

        draw(scale, window);

        window.display();
    }
}

void Editor::draw(float scale, sf::RenderWindow& window)
{
    //draw the grid itself
    grid.draw(scale, window, true, drawStart, drawFinish);

    //draw the not yet placed element
    if (hoverPlace) 
        if (checkHoveredCell()) {
            hoverElement.getSprite().setPosition(128*scale - ((grid.getGrid().at(0).size() * 256 * scale) / 2) + 256 * scale * (hoveredCell.y), 128 * scale - ((grid.getGrid().size() * 256 * scale) / 2) + 256 * scale * (hoveredCell.x));
            if (hoverElement.getType() == 1)
                switch (hoverElement.getSide())
                {
                case 0: hoverElement.getSprite().move(0, -128 * scale); break;
                case 1: hoverElement.getSprite().move(128 * scale, 0); break;
                case 2: hoverElement.getSprite().move(0, 128 * scale); break;
                case 3: hoverElement.getSprite().move(-128 * scale, 0); break;
                default:
                    break;
                }
            hoverElement.getSprite().setScale(scale, scale);
            window.draw(hoverElement.getSprite());
        }

    for (int i = 0; i < 8; i++) {
        if (i < 4)
            resizeSymbols[i].setTexture(AssetManager::getTexture(".\\resources\\plusEmpty.png"));
        else
            resizeSymbols[i].setTexture(AssetManager::getTexture(".\\resources\\minusEmpty.png"));
    }
    //check if resize symbols are hovered
    if (checkHoveredSymbol(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    {
        if (hoveredSymbol < 4)
            resizeSymbols[hoveredSymbol].setTexture(AssetManager::getTexture(".\\resources\\plus.png"));
        else
            resizeSymbols[hoveredSymbol].setTexture(AssetManager::getTexture(".\\resources\\minus.png"));
    }
    for (int i = 0; i < 8; i++) {
        window.draw(resizeSymbols[i]);
    }

    //draw startPossibilities
    if (drawStartPossibilities)
        for (int i = 0; i < startPossibilites.size(); i++)
            for (int j = 0; j < startPossibilites.at(0).size(); i++)
                window.draw(startPossibilites.at(i).at(j));
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

bool Editor::checkHoveredCell() {
    float gridSizeX = grid.getGrid().at(0).size() * 256 * scale;
    float gridSizeY = grid.getGrid().size() * 256 * scale;
    sf::Vector2i mP = sf::Mouse::getPosition();
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
    for (int i = 0; i < grid.getGrid().size(); i++)
    {
        for (int j = 0; j < grid.getGrid().at(0).size(); j++)
        {
            if ((j * 256 * scale - (gridSizeX / 2)) < mousePos.x && mousePos.x < (j * 256 * scale + 256 * scale - (gridSizeX / 2)) &&
                (i * 256 * scale - (gridSizeY / 2)) < mousePos.y && mousePos.y < (i * 256 * scale + 256 * scale - (gridSizeY / 2)))
            {
                hoveredCell = sf::Vector2i(i, j);
                return true;
            }
        }
    }
    return false;
}

bool Editor::checkHoveredSymbol(int mouseX, int mouseY)
{
    sf::Vector2f wMousePos = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    for (int i = 0; i < 8; i++)
        if (resizeSymbols[i].getGlobalBounds().contains(wMousePos))
        {
            hoveredSymbol = i;
            return true;
        }
    if (grid.getFinishSprite().getGlobalBounds().contains(wMousePos))
    {
        hoveredSymbol = 9;
        return true;
    }
    else if (grid.getStartSprite().getGlobalBounds().contains(wMousePos))
    {
        hoveredSymbol = 8;
        return true;
    }
    return false;
}

bool Editor::checkForStraight(int side)
{
    switch (side)
    {
    case 0: return grid.checkForSubGridElementAndSide(hoveredCell.x - 1, hoveredCell.y, 1, 2); break;
    case 1: return grid.checkForSubGridElementAndSide(hoveredCell.x, hoveredCell.y + 1, 1, 3); break;
    case 2: return grid.checkForSubGridElementAndSide(hoveredCell.x + 1, hoveredCell.y, 1, 0); break;
    case 3: return grid.checkForSubGridElementAndSide(hoveredCell.x, hoveredCell.y - 1, 1, 1); break;
    default:
        break;
    }
}
