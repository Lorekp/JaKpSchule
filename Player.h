#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


class Player
{
    private:
    sf::Vector2f pos{-32, -32};
    sf::CircleShape circ;
    public:
    sf::Vector2f getPos();
    void move(sf::Vector2f target);
    void draw(sf::RenderWindow& window, float scale);
    Player();
    ~Player();
};