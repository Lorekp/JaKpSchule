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

void Grid::draw(float scale, sf::RenderWindow& window)
{
    int gridSizeX = grid.size();
    int gridSizeY = grid.at(0).size();
    sf::Vector2f centerOfGrid = sf::Vector2f((gridSizeX * 256 * scale) / 2, (gridSizeY * 256 * scale) / 2);
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++) {
                sf::Sprite sprite = grid.at(x).at(y).getSubGridElementAt(i).getSprite();
                sprite.setScale(sf::Vector2f(scale, scale));
                switch (grid.at(x).at(y).getSubGridElementAt(i).getType())
                {
                case 0:
                    sprite.setOrigin(128 * scale, 128 * scale);
                    sprite.setRotation(grid.at(x).at(y).getSubGridElementAt(i).getRotation());
                    sprite.setOrigin(0, 0);
                    sprite.setPosition((sf::Vector2f(window.getView().getSize().x / 2, window.getView().getSize().y / 2)) - centerOfGrid + sf::Vector2f((y) * 256 * scale, (x) * 256 * scale));
                    break;
                case 1:
                    sprite.setPosition((sf::Vector2f(window.getView().getSize().x / 2, window.getView().getSize().y / 2)) - centerOfGrid + sf::Vector2f((y) * 256 * scale, (x) * 256 * scale));
                    switch (grid.at(x).at(y).getSubGridElementAt(i).getSide())
                    {
                    case 0: 
                        sprite.setOrigin(128 * scale, 128 * scale);
                        sprite.setRotation(90);
                        sprite.setOrigin(0,0);
                        sprite.move(0, (-scale * 256) / 2);
                        break;
                    case 1:
                        sprite.move((scale * 256) / 2, 0);
                        break;
                    case 2:
                        sprite.setOrigin(128 * scale, 128 * scale);
                        sprite.setRotation(90);
                        sprite.setOrigin(0,0);
                        sprite.move(0, (scale * 256) / 2);
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

void Grid::addSubGridElementAt(int y, int x, SubGridElement newSubGridElement) {
    grid.at(x).at(y).addSubGridElement(newSubGridElement);
}