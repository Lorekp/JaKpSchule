#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"


class Player
{
private:
    std::vector<int> nextSide;
    sf::Vector2f pos{ 0, 0 };
    sf::Vector2f targetPos;
    int previousSide;
    sf::Vector2i currentCell;
    sf::Vector2i targetCell;
    sf::Sprite circ;
    Grid& grid;
    float scale;

    void move(sf::Vector2f target);
    void move(float x, float y);
    bool isMoveValid(int side);
    bool calculateTargetCell(int side);
    bool validPair(int side1, int previousSide, int type, int rotationOrSide);
    sf::Vector2f calcCellpos(sf::Vector2i cell);
public:
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void setPos(float x, float y);

    void move();
    void draw(sf::RenderWindow& window, float scale);

    void addNextSide(int side);

    Player(Grid& grid, float scale);
};