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
    this->drawFinishPossibilities = false;

    int gridSizeX = grid.getGrid().size();
    int gridSizeY = grid.getGrid().at(0).size();

    //setupStartPossibilities
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < gridSizeY; j++)
        {
            startPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
            startPossibilities[i].at(j).setOrigin(128, 128);
            switch (i)
            {
            case 0: startPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); startPossibilities[i].at(j).setRotation(90); break;
            case 1: startPossibilities[i].at(j).setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startPossibilities[i].at(j).setRotation(180); break;
            case 2: startPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); startPossibilities[i].at(j).setRotation(270); break;
            case 3: startPossibilities[i].at(j).setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startPossibilities[i].at(j).setRotation(0); break;
            default:
                break;
            }
        }
    }

    //setupFinishPossibilities
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < gridSizeY; j++)
        {
            finishPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
            finishPossibilities[i].at(j).setOrigin(128, 128);
            switch (i)
            {
            case 0: finishPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); finishPossibilities[i].at(j).setRotation(270); break;
            case 1: finishPossibilities[i].at(j).setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishPossibilities[i].at(j).setRotation(0); break;
            case 2: finishPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); finishPossibilities[i].at(j).setRotation(90); break;
            case 3: finishPossibilities[i].at(j).setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishPossibilities[i].at(j).setRotation(180); break;
            default:
                break;
            }
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
                case sf::Keyboard::S: {
                    if (event.key.control)
                        AssetManager::serializeGrid(".\\saves\\level.labdat", this->grid);
                    else
                        downFlag = true; 
                }
                break;
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
                    if (hoverPlace)
                        if (checkHoveredCell())
                        {
                            if (hoverElement.getType() == 0)
                                hoverElement.setRotation(hoverElement.getSprite().getRotation() + 90);
                            else if (hoverElement.getType() == 1) {
                                (hoverElement.getSide() + 1 > 3) ? (hoverElement.setSide(0)) : (hoverElement.setSide(hoverElement.getSide() + 1));
                                hoverElement.setRotation((hoverElement.getSide() + 1) * 90);
                            }
                        }
                }
                break;
                case sf::Mouse::Left:
                {
                    bool consumeClick = false;
                    if (hoverPlace && !consumeClick)
                        if (checkHoveredCell())
                            if (hoverElement.getType() == 0) {
                                if (!grid.checkForSubGridElement(hoveredCell.x, hoveredCell.y, 0))
                                    grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y, Slope(hoverElement.getSprite().getRotation()));
                            }
                            else if (hoverElement.getType() == 1)
                                if (!grid.checkForSubGridElementAndSide(hoveredCell.x, hoveredCell.y, 1, hoverElement.getSide())) {
                                    grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y, Straight(hoverElement.getSide()));
                                    switch (hoverElement.getSide())
                                    {
                                    case 0:
                                        grid.addSubGridElementAt(hoveredCell.x - 1, hoveredCell.y, Straight(2));
                                        break;
                                    case 1:
                                        grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y + 1, Straight(3));
                                        break;
                                    case 2:
                                        grid.addSubGridElementAt(hoveredCell.x + 1, hoveredCell.y, Straight(0));
                                        break;
                                    case 3:
                                        grid.addSubGridElementAt(hoveredCell.x, hoveredCell.y - 1, Straight(1));
                                        break;
                                    default:
                                        break;
                                    }
                                }
                    if (checkHoveredSymbol(event.mouseButton.x, event.mouseButton.y) && !consumeClick) {
                        switch (hoveredSymbol)
                        {
                        case 8:
                            if (!drawFinishPossibilities) {
                                drawStart = false; drawStartPossibilities = true;
                                consumeClick = true;
                            }
                            break;
                        case 9:
                            if (!drawStartPossibilities) {
                                drawFinish = false; drawFinishPossibilities = true;
                                consumeClick = true;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    if (drawStartPossibilities && !consumeClick) {
                        for (int i = 0; i < 4; i++) {
                            if (i == 0 || i == 2) {
                                for (int j = 0; j < startPossibilities[0].size(); j++)
                                {
                                    if (startPossibilities[i].at(j).getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), view)))
                                    {
                                        if (i == 2)
                                            grid.setStart(sf::Vector3i(grid.getGrid().size() - 1, j, 0));
                                        else
                                            grid.setStart(sf::Vector3i(0, j, 2));
                                        drawStartPossibilities = false;
                                        drawStart = true;
                                    }
                                }
                            }
                            if (i == 1 || i == 3) {
                                for (int j = 0; j < startPossibilities[1].size(); j++)
                                {
                                    if (startPossibilities[i].at(j).getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), view)))
                                    {
                                        if (i == 1)
                                            grid.setStart(sf::Vector3i(j, grid.getGrid().at(0).size() - 1, 3));
                                        else
                                            grid.setStart(sf::Vector3i(j, 0, 1));
                                        drawStartPossibilities = false;
                                        drawStart = true;
                                    }
                                }
                            }
                        }
                    }
                    if (drawFinishPossibilities && !consumeClick) {
                        for (int i = 0; i < 4; i++) {
                            if (i == 0 || i == 2) {
                                for (int j = 0; j < finishPossibilities[0].size(); j++)
                                {
                                    if (finishPossibilities[i].at(j).getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), view)))
                                    {
                                        if (i == 2)
                                            grid.setFinish(sf::Vector3i(grid.getGrid().size() - 1, j, 0));
                                        else
                                            grid.setFinish(sf::Vector3i(0, j, 2));
                                        drawFinishPossibilities = false;
                                        drawFinish = true;
                                    }
                                }
                            }
                            if (i == 1 || i == 3) {
                                for (int j = 0; j < finishPossibilities[1].size(); j++)
                                {
                                    if (finishPossibilities[i].at(j).getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), view)))
                                    {
                                        if (i == 1)
                                            grid.setFinish(sf::Vector3i(j, grid.getGrid().at(0).size() - 1, 3));
                                        else
                                            grid.setFinish(sf::Vector3i(j, 0, 1));
                                        drawFinishPossibilities = false;
                                        drawFinish = true;
                                    }
                                }
                            }
                        }
                    }
                    if (checkHoveredSymbol(event.mouseButton.x, event.mouseButton.y) && !consumeClick) {
                        switch (hoveredSymbol)
                        {
                            //add
                        case 0: readjustArrows(1, true); grid.addColumnToGrid(); resizePossibilities(true, false); readjustPossibilities(); break;
                        case 1: readjustArrows(3, true); grid.addColumnToGrid(); grid.moveGridRight(); resizePossibilities(true, false); readjustPossibilities(); break;
                        case 2: readjustArrows(2, true); grid.addRowToGrid(); resizePossibilities(true, true); readjustPossibilities(); break;
                        case 3: readjustArrows(0, true); grid.addRowToGrid(); grid.moveGridDown(); resizePossibilities(true, true); readjustPossibilities(); break;
                            //remove
                        case 4: if (grid.removeColumnFromGrid(grid.getGrid().at(0).size())) { readjustArrows(1, false); resizePossibilities(false, false); readjustPossibilities(); }  break;
                        case 5: if (grid.removeColumnFromGrid(1)) { readjustArrows(3, false); resizePossibilities(false, false); readjustPossibilities(); } break;
                        case 6: if (grid.removeRowFromGrid(grid.getGrid().size())) { readjustArrows(2, false); resizePossibilities(false, true); readjustPossibilities(); } break;
                        case 7: if (grid.removeRowFromGrid(1)) { readjustArrows(0, false); resizePossibilities(false, true); readjustPossibilities(); } break;
                        default:
                            break;
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
    if (drawStartPossibilities) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < startPossibilities[i].size(); j++) {
                startPossibilities[i].at(j).setScale(scale, scale);
                window.draw(startPossibilities[i].at(j));
            }
        }
    }
        
    if (drawFinishPossibilities) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < finishPossibilities[i].size(); j++) {
                finishPossibilities[i].at(j).setScale(scale, scale);
                window.draw(finishPossibilities[i].at(j));
            }
        }
    }
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

void Editor::readjustPossibilities()
{
    int gridSizeX = grid.getGrid().size();
    int gridSizeY = grid.getGrid().at(0).size();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < startPossibilities[i].size(); j++)
        {
            switch (i)
            {
            case 0: startPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); startPossibilities[i].at(j).setRotation(90); break;
            case 1: startPossibilities[i].at(j).setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startPossibilities[i].at(j).setRotation(180); break;
            case 2: startPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); startPossibilities[i].at(j).setRotation(270); break;
            case 3: startPossibilities[i].at(j).setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishPossibilities[i].at(j).setRotation(0); break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < finishPossibilities[i].size(); j++)
        {
            switch (i)
            {
            case 0: finishPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); finishPossibilities[i].at(j).setRotation(270); break;
            case 1: finishPossibilities[i].at(j).setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishPossibilities[i].at(j).setRotation(0); break;
            case 2: finishPossibilities[i].at(j).setPosition(j * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); finishPossibilities[i].at(j).setRotation(90); break;
            case 3: finishPossibilities[i].at(j).setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, j * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishPossibilities[i].at(j).setRotation(180); break;
            default:
                break;
            }
        }
    }
}

void Editor::readjustArrows(int side, bool add)
{
    switch (side)
    {
    case 0: {
        if (add)
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 1 || ogStart.z == 3)
                start.x += 1;
            if (ogFinish.z == 1 || ogFinish.z == 3)
                finish.x += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);

        }
        else
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 1 || ogStart.z == 3)
                start.x -= 1;
            if (ogFinish.z == 1 || ogFinish.z == 3)
                finish.x -= 1;
            if ((ogStart.z == 1 || ogStart.z == 3) && ogStart.x == 0)
                start.x += 1;
            if ((ogFinish.z == 1 || ogFinish.z == 3) && ogStart.x == 0)
                finish.x += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
    }
    break;
    case 1: {
        if (add)
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 3 && ogStart.y == grid.getGrid().at(0).size() - 1)
                start.y += 1;
            if (ogFinish.z == 3 && ogFinish.y == grid.getGrid().at(0).size() - 1)
                finish.y += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
        else
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if ((ogStart.z == 0 || ogStart.z == 2) && ogStart.y == grid.getGrid().at(0).size())
                start.y -= 1;
            if ((ogFinish.z == 0 || ogFinish.z == 2) && ogFinish.y == grid.getGrid().at(0).size())
                finish.y -= 1;
            if (ogStart.z == 3 && ogStart.y == grid.getGrid().at(0).size())
                start.y -= 1;
            if (ogFinish.z == 3 && ogFinish.y == grid.getGrid().at(0).size())
                finish.y -= 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
    }
    break;
    case 2:
    {
        if (add)
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 0 && ogStart.x == grid.getGrid().size() - 1)
                start.x += 1;
            if (ogFinish.z == 0 && ogFinish.x == grid.getGrid().size() - 1)
                finish.x += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
        else
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if ((ogStart.z == 1 || ogStart.z == 3) && ogStart.x == grid.getGrid().size())
                start.x -= 1;
            if ((ogFinish.z == 1 || ogFinish.z == 3) && ogFinish.x == grid.getGrid().size())
                finish.x -= 1;
            if (ogStart.z == 0 && ogStart.x == grid.getGrid().size())
                start.x -= 1;
            if (ogFinish.z == 0 && ogFinish.x == grid.getGrid().size())
                finish.x -= 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
    }
    break;
    case 3:
    {
        if (add)
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 0 || ogStart.z == 2)
                start.y += 1;
            if (ogFinish.z == 0 || ogFinish.z == 2)
                finish.y += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);

        }
        else
        {
            sf::Vector3i ogFinish = grid.getFinish();
            sf::Vector3i ogStart = grid.getStart();
            sf::Vector3i finish = sf::Vector3i(0, 0, 0);
            sf::Vector3i start = sf::Vector3i(0, 0, 0);
            if (ogStart.z == 0 || ogStart.z == 2)
                start.y -= 1;
            if (ogFinish.z == 0 || ogFinish.z == 2)
                finish.y -= 1;
            if ((ogStart.z == 0 || ogStart.z == 2) && ogStart.y == 0)
                start.y += 1;
            if ((ogFinish.z == 0 || ogFinish.z == 2) && ogStart.y == 0)
                finish.y += 1;
            grid.setStart(grid.getStart() + start);
            grid.setFinish(grid.getFinish() + finish);
        }
    }
    break;
    default:
        break;
    }
}

void Editor::resizePossibilities(bool bigger, bool x)
{
    for (int i = 0; i < 4; i++)
    {
        if (x) {
            if (i == 1 || i == 3)
                if (bigger)
                {
                    startPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
                    startPossibilities[i].at(startPossibilities[i].size() - 1).setOrigin(128, 128);
                }
                else
                {
                    startPossibilities[i].pop_back();
                }
        }
        else
            if (i == 0 || i == 2)
                if (bigger)
                {
                    startPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
                    startPossibilities[i].at(startPossibilities[i].size() - 1).setOrigin(128, 128);
                }
                else
                {
                    startPossibilities[i].pop_back();
                }
    }
    for (int i = 0; i < 4; i++)
    {
        if (x) {
            if (i == 1 || i == 3)
                if (bigger)
                {
                    finishPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
                    finishPossibilities[i].at(finishPossibilities[i].size() - 1).setOrigin(128, 128);
                }
                else
                {
                    finishPossibilities[i].pop_back();
                }
        }
        else
            if (i == 0 || i == 2)
                if (bigger)
                {
                    finishPossibilities[i].push_back(sf::Sprite(AssetManager::getTexture(".\\resources\\arrowLowOp.png")));
                    finishPossibilities[i].at(finishPossibilities[i].size() - 1).setOrigin(128, 128);
                }
                else
                {
                    finishPossibilities[i].pop_back();
                }
    }
}