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
            sprites.at(x).at(y).setPosition(centerOfGrid + sf::Vector2f(px, py) - sf::Vector2f((gridSizeX - x+1)*256*scale, (gridSizeY - y+1)*256*scale));
            window.draw(sprites.at(x).at(y));
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