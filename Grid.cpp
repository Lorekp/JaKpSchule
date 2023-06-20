#include "Grid.h"
#include "AssetManager.h"
#include "GridElement.h"
#include "SubGridElement.h"

Grid::Grid(int gridSizeX, int gridSizeY) {
    for (int x = 0; x < gridSizeX; x++)
    {
       grid.push_back(std::vector<GridElement>());
       for (int y = 0; y < gridSizeY; y++) 
       {
           grid.at(x).push_back(GridElement());
       }
    }
    startSprite.setTexture(AssetManager::getTexture(".\\resources\\arrow.png"));
    finishSprite.setTexture(AssetManager::getTexture(".\\resources\\arrow.png"));
    startSprite.setOrigin(128, 128);
    finishSprite.setOrigin(128, 128);
    start = sf::Vector3i(0, 2, 2);
    finish = sf::Vector3i(3, 3, 0);

}

Grid::Grid()
{
    for (int x = 0; x < 4; x++)
    {
        grid.push_back(std::vector<GridElement>());
        for (int y = 0; y < 4; y++)
        {
            grid.at(x).push_back(GridElement());
        }
    }
    startSprite.setTexture(AssetManager::getTexture(".\\resources\\arrow.png"));
    finishSprite.setTexture(AssetManager::getTexture(".\\resources\\arrow.png"));
    startSprite.setOrigin(128, 128);
    finishSprite.setOrigin(128, 128);
    start = sf::Vector3i(0, 2, 2);
    finish = sf::Vector3i(3, 3, 0);
}

GridElement& Grid::getGridElementAt(int x, int y) {
	return grid.at(x).at(y);
}

sf::Vector3i& Grid::getStart()
{
    return start;
}

sf::Vector3i& Grid::getFinish()
{
    return finish;
}

sf::Sprite Grid::getStartSprite()
{
    return startSprite;
}

sf::Sprite Grid::getFinishSprite()
{
    return finishSprite;
}

void Grid::setStart(sf::Vector3i start)
{
    this->start = start;
}

void Grid::setFinish(sf::Vector3i finish)
{
    this->finish = finish;
}

bool Grid::checkForSubGridElement(int x, int y, int type)
{
    for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++)
        if (grid.at(x).at(y).getSubGridElementAt(i).getType() == type)
            return true;
    return false;
}

bool Grid::checkForSubGridElementAndSide(int x, int y, int type, int side)
{
    if (x < 0 || y < 0 || x > grid.size() - 1 || y > grid.at(0).size() - 1)
        return false;
    for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++)
        if (grid.at(x).at(y).getSubGridElementAt(i).getType() == type && grid.at(x).at(y).getSubGridElementAt(i).getSide() == side)
            return true;
    return false;
}

std::vector<std::vector<GridElement>>& Grid::getGrid()
{
    return grid;
}

void Grid::draw(float scale, sf::RenderWindow& window, bool drawGrid, bool drawStart, bool drawFinish)
{
    int gridSizeX = grid.size();
    int gridSizeY = grid.at(0).size();

    //if editor draw lines
    if (drawGrid)
    {

        sf::Texture& texture(AssetManager::getTexture(".\\resources\\grid.png"));
        texture.setRepeated(true);
        
        sf::Sprite sprite(texture);
        sprite.setScale(scale, scale);
        sprite.setTextureRect(sf::IntRect(0, 0, 256 * gridSizeY, 256 * gridSizeX));
        sprite.setPosition(-(gridSizeY * 256 * scale) / 2, -(gridSizeX * 256 * scale) / 2);

        window.draw(sprite);
    }
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            //draw SubGridElements
            for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++) {
                sf::Sprite& sprite = grid.at(x).at(y).getSubGridElementAt(i).getSprite();
                sf::RectangleShape& boundingBox = grid.at(x).at(y).getSubGridElementAt(i).getBoundingBox();
                boundingBox.setOrigin(13 / 2, 32);
                boundingBox.setScale(sf::Vector2f(scale, scale));
                sprite.setOrigin(128, 128);
                sprite.setScale(sf::Vector2f(scale, scale));
              
                float newPosX = floor((y * 256 * scale) + (128 * scale) - (gridSizeY * 256 * scale) / 2);
                float newPosY = floor((x * 256 * scale) + (128 * scale) - (gridSizeX * 256 * scale) / 2);

                switch (grid.at(x).at(y).getSubGridElementAt(i).getType())
                {
                case 0:
                    sprite.setPosition(newPosX, newPosY);
                    boundingBox.setPosition(newPosX, newPosY);
                    break;
                case 1:
                    sprite.setPosition(newPosX, newPosY);
                    boundingBox.setPosition(newPosX, newPosY);
                    switch (grid.at(x).at(y).getSubGridElementAt(i).getSide())
                    {
                    case 0: 
                        sprite.move(0, (-scale * 256) / 2);
                        sprite.setRotation(90);
                        boundingBox.move(0, (-scale * 256) / 2);
                        boundingBox.setRotation(90);
                        break;
                    case 1:
                        sprite.move((scale * 256) / 2, 0);
                        boundingBox.move((scale * 256) / 2, 0);
                        break;
                    case 2:
                        sprite.move(0, (scale * 256) / 2);
                        sprite.setRotation(90);
                        boundingBox.move(0, (scale * 256) / 2);
                        boundingBox.setRotation(90);
                        break;
                    case 3:
                        sprite.move((-scale * 256) / 2, 0);
                        boundingBox.move((-scale * 256) / 2, 0);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                window.draw(sprite);
                window.draw(boundingBox);
            }

        }
    }
    //draw start
    if (drawStart) {
        startSprite.setScale(scale, scale);
        switch (getSide(sf::Vector2i(start.x, start.y)))
        {
        case 2: startSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(180); break;
        case 4: startSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(0); break;
        case 3: startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); startSprite.setRotation(90); break;
        case 6: startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); startSprite.setRotation(270); break;
        case 5: {
            if (start.z == 2) {
                startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); startSprite.setRotation(90);
            }
            else if (start.z == 3) {
                startSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(180);
            }
            break;
        }
        case 8: {
            if (start.z == 3) {
                startSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(180);
            }
            else if (start.z == 0) {
                startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); startSprite.setRotation(270);
            }
            break;
        }
        case 10: {
            if (start.z == 0) {
                startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); startSprite.setRotation(270);
            }
            else if (start.z == 1) {
                startSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(0);
            }
            break;
        }
        case 7: {
            if (start.z == 2) {
                startSprite.setPosition(start.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); startSprite.setRotation(90);
            }
            else if (start.z == 1) {
                startSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, start.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); startSprite.setRotation(0);
            }
            break;
        }
        default:
            break;
        }
        window.draw(startSprite);
    }
    if (drawFinish)
    {
        finishSprite.setScale(scale, scale);
        switch (getSide(sf::Vector2i(finish.x, finish.y)))
        {
        case 2: finishSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(0); break;
        case 4: finishSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(180); break;
        case 3: finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); finishSprite.setRotation(270); break;
        case 6: finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); finishSprite.setRotation(90); break;
        case 5: {
            if (finish.z == 2) {
                finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); finishSprite.setRotation(270);
            }
            else if (finish.z == 3) {
                finishSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(0);
            }
            break;
        }
        case 8: {
            if (finish.z == 3) {
                finishSprite.setPosition((gridSizeY * 256 * scale) / 2 + 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(0);
            }
            else if (finish.z == 0) {
                finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); finishSprite.setRotation(90);
            }
            break;
        }
        case 10: {
            if (finish.z == 0) {
                finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); finishSprite.setRotation(90);
            }
            else if (finish.z == 1) {
                finishSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(180);
            }
            break;
        }
        case 7: {
            if (finish.z == 2) {
                finishSprite.setPosition(finish.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); finishSprite.setRotation(270);
            }
            else if (finish.z == 1) {
                finishSprite.setPosition(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, finish.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); finishSprite.setRotation(180);
            }
            break;
        }
        default:
            break;
        }
        window.draw(finishSprite);
    }
}

int Grid::getSide(sf::Vector2i cell) //2 = e, 4 = w, n = 3, s = 6 | ne = 5, se = 8, sw = 10, nw = 7
{
    int result = 0;

    if (cell.x == 0)
        result = 3;
    else if (cell.x == grid.size() - 1)
        result = 6;
    if (cell.y == 0)
        result += 4;
    else if (cell.y == grid.at(0).size() - 1)
        result += 2;

    return result;
}

void Grid::addSubGridElementAt(int x, int y, SubGridElement newSubGridElement) {
    if (x >= 0 && x < grid.size() && y >= 0 && y < grid.at(0).size())
        grid.at(x).at(y).addSubGridElement(newSubGridElement);
}

bool Grid::removeRowFromGrid(int row)
{
    if (row <= grid.size() && grid.size() > 4) {
        grid.erase(grid.begin() + row - 1);
        return true;
    }
    return false;
}

void Grid::addRowToGrid()
{
    grid.push_back(std::vector<GridElement>());
    for (int y = 0; y < grid.at(0).size(); y++)
    {
        grid.at(grid.size()-1).push_back(GridElement());
    }
}

bool Grid::removeColumnFromGrid(int column)
{
    if (column <= grid.at(0).size() && grid.at(0).size() > 4) {
        for (int x = 0; x < grid.size(); x++)
        {
            grid.at(x).erase(grid.at(x).begin() + column - 1);
        }
        return true;
    }
    return false;
}

void Grid::addColumnToGrid()
{
    for (int x = 0; x < grid.size(); x++)
    {
            grid.at(x).push_back(GridElement());
    }
}

void Grid::moveGridRight()
{
    for (int i = grid.size()-1; i > 0; i--)
    {
        for (int j = grid.at(i).size()-1; j > 0; j--)
            grid.at(i).at(j).setSubGridElements(grid.at(i).at(j - 1).getSubGridElements());
        grid.at(i).at(0).setSubGridElements(std::vector<SubGridElement>());
    }
}

void Grid::moveGridDown()
{
    for (int i = grid.size() - 1; i > 0; i--)
    {
        grid.at(i) = grid.at(i - 1);
    }
    grid.at(0) = std::vector<GridElement>();
    for (int i = 0; i < grid.at(1).size(); i++)
    {
        grid.at(0).push_back(GridElement());
    }
}


