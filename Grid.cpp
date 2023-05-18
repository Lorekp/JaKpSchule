#include "Grid.h"
#include "AssetManager.h"

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
    grid.push_back(std::vector<GridElement>());
    grid.at(0).push_back(GridElement());
}

GridElement Grid::getGridElementAt(int x, int y) {
	return grid.at(x).at(y);
}

std::vector<std::vector<GridElement>>& Grid::getGrid()
{
    return grid;
}

void Grid::draw(float px, float py, float scale, sf::RenderWindow& window)
{
    int gridSizeX = sprites.size();
    int gridSizeY = sprites.at(0).size();
    sf::Vector2f centerOfGrid = sf::Vector2f((gridSizeX * 256 * scale) / 2, (gridSizeY * 256 * scale) / 2);
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            sprites.at(y).at(x).setScale(sf::Vector2f(scale, scale));
            sprites.at(y).at(x).setPosition((sf::Vector2f(px/2, py/2)) - centerOfGrid + sf::Vector2f((x)*256*scale, (y)*256*scale));
            window.draw(sprites.at(y).at(x));
        }
    }
}

void Grid::calcSprites()
{
    int gridSizeX = grid.size();
    int gridSizeY = grid.at(0).size();
    sprites.resize(gridSizeX);
    for (int x = 0; x < gridSizeX; x++)
    {
        sprites.at(x).resize(gridSizeY);
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++)
            {
                switch (grid.at(x).at(y).getSubGridElements().at(i).getType())
                {
                case -1:
                    sprites.at(x).at(y).setTexture(AssetManager::getTexture(".\\resources\\empty256.png"));
                    break;
                case 0:
                    sprites.at(x).at(y).setTexture(AssetManager::getTexture(".\\resources\\slope.png"));
                    break;
                case 1:
                    sprites.at(x).at(y).setTexture(AssetManager::getTexture(".\\resources\\straight.png"));
                    break;
                default:
                    break;
                }
            }
            
        }
    }
}

void Grid::addSubGridElementAt(int y, int x, SubGridElement newSubGridElement) {
    grid.at(x).at(y).addSubGridElement(newSubGridElement);
    calcSprites();
}