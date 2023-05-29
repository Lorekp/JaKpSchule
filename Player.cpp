#include "Player.h"

Player::Player(Grid& grid, float scale) : grid(grid)
{
    circ = sf::Sprite(AssetManager::getTexture(".\\resources\\blackBall.png"));
    circ.setOrigin(128, 128);

    this->scale = scale;
    this->targetCell = sf::Vector2i(grid.getStart().x, grid.getStart().y);
    this->currentCell = sf::Vector2i(-1, -1);

    int gridSizeX = grid.getGrid().size();
    int gridSizeY = grid.getGrid().at(0).size();
    switch (grid.getStart().z)
    {
    case 2: this->pos = sf::Vector2f((gridSizeY * 256 * scale) / 2 + 1024 * scale, targetCell.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); break;
    case 4: this->pos = sf::Vector2f(-((gridSizeY * 256 * scale) / 2) - 1024 * scale, targetCell.x * 256 * scale - ((gridSizeX * 256 * scale) / 2) + 128 * scale); break;
    case 3: this->pos = sf::Vector2f(targetCell.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, -((gridSizeX * 256 * scale) / 2) - 1024 * scale); break;
    case 6: this->pos = sf::Vector2f(targetCell.y * 256 * scale - ((gridSizeY * 256 * scale) / 2) + 128 * scale, ((gridSizeX * 256 * scale) / 2) + 1024 * scale); break;
    default:
        break;
    }
    circ.setPosition(pos);
}

void Player::move(sf::Vector2f target) { pos += (target - pos) * 0.025f; circ.setPosition(pos); }
void Player::move(float x, float y) { pos += (sf::Vector2f(x, y) - pos) * 0.025f; circ.setPosition(pos); }

bool Player::isMoveValid(int side)
{
    bool valid = true;
    switch (side)
    {
    case 0:
        for (int i = 0; i < grid.getGridElementAt(currentCell.x, currentCell.y).getSubGridElements().size(); i++)
        {
            SubGridElement element = grid.getGridElementAt(currentCell.x, currentCell.y).getSubGridElementAt(i);
            switch (element.getType())
            {
            case 0:
                if ((element.getSprite().getRotation() == 0) && (previousSide == 1))

                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
}

bool Player::calculateTargetCell(int side)
{
    switch (side)
    {
    case 0:
        for ()
        break;
    default:
        break;
    }
}

bool Player::validPair(int side1, int previousSide, int type, int rotationOrSide)
{
    if (type == 0)
    {
        if (rotationOrSide == 0)
        {
            if ((side1 == 2 && previousSide == 3) || (side1 == 3 && previousSide == 2) || (side1 == 0 && previousSide == 1) || (side1 == 1 && previousSide == 0))
                return true;
        }
        else if (rotationOrSide == 90)
        {
            if ((side1 == 2 && previousSide == 1) || (side1 == 1 && previousSide == 2) || (side1 == 0 && previousSide == 3) || (side1 == 3 && previousSide == 0))
                return true;
        }
    }
    else if (type == 1)
    {
        if (previousSide == )
    }
    return false;
}

sf::Vector2f Player::calcCellpos(sf::Vector2i cell) {

}

void Player::move() 
{
    if (pos == targetPos)
        this->currentCell = targetCell;
    if ((targetCell == currentCell) && (nextSide.size() != 0))
    {
        this->previousSide = nextSide.at(0);
        nextSide.erase(nextSide.begin());
        if (!isMoveValid(nextSide.at(0)))
            nextSide.erase(nextSide.begin());
        calculateTargetCell(nextSide.at(0));
    }
    if (pos != targetPos)
        move(targetPos);
}

void Player::draw(sf::RenderWindow& window, float scale)
{
    circ.setScale(scale, scale);
    window.draw(circ);
}

void Player::addNextSide(int side)
{
    nextSide.push_back(side);
}

sf::Vector2f Player::getPos() { return pos; }
void Player::setPos(sf::Vector2f newPos) { pos = newPos; circ.setPosition(pos); }
void Player::setPos(float x, float y) { pos = sf::Vector2f(x, y); circ.setPosition(pos); }