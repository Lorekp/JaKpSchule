#include <SFML/Graphics.hpp>
#include <direct.h>
#include <iostream>
#include "Level.h"
#include "AssetManager.h"

int dirExists(const char* const path);

int main() {

    //initialization
    const char* spath = ".\\saves";
    if (dirExists(spath) > 0)
        std::cout << "folder already exists";
    else if (dirExists(spath) == 0)
        _mkdir(".\\saves");
    

    bool fullscreen = true;
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
    AssetManager manager;

    Level level = Level(8);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
				{
                    if (fullscreen)
                    {
                        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth");
                    }
                    else
                    {
                        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
                    }
					fullscreen != fullscreen;
				}
                break;
            case sf::Event::Closed:
                window.close();
            }
        }

        window.clear();
        //draw here
        window.display();
    }

    return 0;

}

int dirExists(const char* const path)
{
    //returns 0 if no dir/ exists but not a dir
    //returns >0 if dir exists
    //returns <0 if other error
    struct stat info;

    int statRC = stat(path, &info);
    if (statRC != 0)
    {
        if (errno == ENOENT) { return 0; } // something along the path does not exist
        if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
        return -1;
    }

    return (info.st_mode & S_IFDIR) ? 1 : 0;
}