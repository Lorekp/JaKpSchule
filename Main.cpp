#include <SFML/Graphics.hpp>
#include "Level.h"
#include "AssetManager.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    AssetManager manager;

    Level level = Level(8);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //draw here
        window.display();
    }

    return 0;

}