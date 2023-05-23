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

void Grid::draw(float scale, sf::RenderWindow& window, bool drawGrid)
{
    int gridSizeX = grid.size();
    int gridSizeY = grid.at(0).size();
    sf::Vector2f centerOfGrid = sf::Vector2f((gridSizeX * 256 * scale) / 2, (gridSizeY * 256 * scale) / 2);
    if (drawGrid)
    {
        float newPosX = floor(window.getView().getSize().x / 2) - (gridSizeX * 256 * scale) / 2;
        float newPosY = floor(window.getView().getSize().y / 2) - (gridSizeY * 256 * scale) / 2;

        sf::Texture& texture(AssetManager::getTexture(".\\resources\\grid.png"));
        texture.setRepeated(true);
        
        sf::Sprite sprite(texture);
        sprite.setScale(scale, scale);
        sprite.setTextureRect(sf::IntRect(0, 0, 256 * gridSizeX, 256 * gridSizeY));
        sprite.setPosition(newPosX, newPosY);
        /*sf::Texture texture(AssetManager::getTexture(".\\resources\\grid.png"));
        texture.setRepeated(true);
        sf::RectangleShape rectShape(sf::Vector2f(256*gridSizeX, 256*gridSizeY));
        rectShape.setTextureRect(sf::IntRect(newPosX, newPosY, 256 * gridSizeX, 256 * gridSizeY));
        rectShape.setTexture(&texture);
        rectShape.setScale(scale, scale);*/
        window.draw(sprite);
    }
    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            
            for (int i = 0; i < grid.at(x).at(y).getSubGridElements().size(); i++) {
                sf::Sprite sprite = grid.at(x).at(y).getSubGridElementAt(i).getSprite();
                sprite.setOrigin(128, 128);
                sprite.setScale(sf::Vector2f(scale, scale));
                float newPosX = floor(window.getView().getSize().x / 2) - (gridSizeX * 256 * scale) / 2 + (y * 256 * scale) + 128*scale;
                float newPosY = floor(window.getView().getSize().y / 2) - (gridSizeY * 256 * scale) / 2 + (x * 256 * scale) + 128*scale;
                switch (grid.at(x).at(y).getSubGridElementAt(i).getType())
                {
                case 0:
                    sprite.setPosition(newPosX, newPosY);
                    sprite.setRotation(grid.at(x).at(y).getSubGridElementAt(i).getRotation());
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

void Grid::addSubGridElementAt(int y, int x, SubGridElement newSubGridElement) {
    grid.at(x).at(y).addSubGridElement(newSubGridElement);
}