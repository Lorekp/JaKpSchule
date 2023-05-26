#include "Player.h"

Player::Player()
{
    circ = sf::CircleShape(32.0, 100ul); 
    circ.setOrigin(32, 32);
    circ.setPosition(pos);
    circ.setFillColor(sf::Color::Red);
}

Player::~Player(){}

void Player::move(sf::Vector2f target)  {pos += (target-pos)*0.1f; circ.setPosition(pos);}

void Player::draw(sf::RenderWindow& window, float scale)
{
    circ.setScale(scale, scale);
    window.draw(circ);
}

sf::Vector2f Player::getPos(){return pos;}
