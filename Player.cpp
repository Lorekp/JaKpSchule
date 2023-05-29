#include "Player.h"

Player::Player()
{
    circ = sf::CircleShape(32.0, 100ul); 
    circ.setOrigin(32, 32);
    circ.setPosition(pos);
    circ.setFillColor(sf::Color::Red);
}

Player::~Player(){}

void Player::move(sf::Vector2f target)  {pos += ((target/*1.1f*/)-pos)*0.025f; circ.setPosition(pos);}
void Player::move(float x, float y)     {pos += ((sf::Vector2f(x, y)/*1.1f*/)-pos)*0.025f; circ.setPosition(pos);}

void Player::draw(sf::RenderWindow& window, float scale)
{
    circ.setScale(scale, scale);
    window.draw(circ);
}

sf::Vector2f Player::getPos(){return pos;}
void Player::setPos(sf::Vector2f newPos)    {pos = newPos; circ.setPosition(pos);}
void Player::setPos(float x, float y)    {pos = sf::Vector2f(x, y); circ.setPosition(pos);}
