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
}

GridElement Grid::getGridElementAt(int x, int y) {
	return grid.at(x).at(y);
}

sf::Vector3i Grid::getStart()
{
    return start;
}

sf::Vector3i Grid::getFinish()
{
    return finish;
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

void Grid::draw(float scale, sf::RenderWindow& window, bool drawGrid)
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
    //draw gridelements
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            
            for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++) {
                sf::Sprite sprite = grid.at(x).at(y).getSubGridElementAt(i).getSprite();
                sprite.setOrigin(128, 128);
                sprite.setScale(sf::Vector2f(scale, scale));
              
                float newPosX = floor((y * 256 * scale) + (128 * scale) - (gridSizeY * 256 * scale) / 2);
                float newPosY = floor((x * 256 * scale) + (128 * scale) - (gridSizeX * 256 * scale) / 2);

                switch (grid.at(x).at(y).getSubGridElementAt(i).getType())
                {
                case 0:
                    sprite.setPosition(newPosX, newPosY);
                    sprite.setRotation(grid.at(x).at(y).getSubGridElementAt(i).getSprite().getRotation());
                    break;
                case 1:
                    sprite.setPosition(newPosX, newPosY);
                    switch (grid.at(x).at(y).getSubGridElementAt(i).getSide())
                    {
                    case 0: 
                        sprite.move(0, (-scale * 256) / 2);
                        sprite.setRotation(90);
                        break;
                    case 1:
                        sprite.move((scale * 256) / 2, 0);
                        break;
                    case 2:
                        sprite.move(0, (scale * 256) / 2);
                        sprite.setRotation(90);
                        break;
                    case 3:
                        sprite.move((-scale * 256) / 2, 0);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                window.draw(sprite);
            }
        }
    }


}

void Grid::addSubGridElementAt(int x, int y, SubGridElement newSubGridElement) {
    grid.at(x).at(y).addSubGridElement(newSubGridElement);
}

void Grid::removeRowFromGrid(int row)
{
    if (row <= grid.size() && grid.size() > 4)
        grid.erase(grid.begin() + row - 1);
}

void Grid::addRowToGrid()
{
    grid.push_back(std::vector<GridElement>());
    for (int y = 0; y < grid.at(0).size(); y++)
    {
        grid.at(grid.size()-1).push_back(GridElement());
    }
}

void Grid::removeColumnFromGrid(int column)
{
    if (column <= grid.at(0).size() && grid.at(0).size() > 4)
        for (int x = 0; x < grid.size(); x++)
        {
            grid.at(x).erase(grid.at(x).begin() + column - 1);
        }
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


