#include "Grid.h"

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

void Grid::saveGrid()
{
    
}

GridElement Grid::getGridElementAt(int x, int y) {
	return grid.at(x).at(y);
}

std::vector<std::vector<GridElement>>& Grid::getGrid()
{
    return grid;
}

sf::Vector2i Grid::getFullSize()
{
    return sf::Vector2i(grid.size(), grid.at(0).size());
}

void Grid::draw(float scale, sf::RenderWindow& window, bool drawGrid)
{
    int gridSizeX = grid.size();
    int gridSizeY = grid.at(0).size();

    if (drawGrid)
    {

        sf::Texture& texture(AssetManager::getTexture(".\\resources\\grid.png"));
        texture.setRepeated(true);
        
        sf::Sprite sprite(texture);
        sprite.setScale(scale, scale);
        sprite.setTextureRect(sf::IntRect(0, 0, 256 * gridSizeX, 256 * gridSizeY));
        sprite.setPosition(-(gridSizeX * 256 * scale) / 2, -(gridSizeY * 256 * scale) / 2);

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
              
                float newPosX = std::floor((y * 256 * scale) + (128 * scale) - (gridSizeX * 256 * scale) / 2);
                float newPosY = std::floor((x * 256 * scale) + (128 * scale) - (gridSizeY * 256 * scale) / 2);

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

void Grid::addSubGridElementAt(int y, int x, SubGridElement newSubGridElement) 
{
    if(x<grid.size() && y<grid.at(0).size())    grid.at(x).at(y).addSubGridElement(newSubGridElement);
}
void Grid::addSubGridElementAt(sf::Vector2u coords, SubGridElement newSubGridElement) 
{
    if(coords.y<grid.size() && coords.x<grid.at(0).size())    grid.at(coords.y).at(coords.x).addSubGridElement(newSubGridElement);
}
void Grid::removeSubGridElementAt(int y, int x) 
{
    if(x<grid.size() && y<grid.at(0).size())    grid.at(x).at(y).removeSubGridElement();
}
void Grid::removeSubGridElementAt(sf::Vector2u coords) 
{
    if(coords.y<grid.size() && coords.x<grid.at(0).size())    grid.at(coords.y).at(coords.x).removeSubGridElement();
}