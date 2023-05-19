#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <errno.h>
#if defined(_WIN32)
#include <direct.h>
#endif
#include <regex>
#include <iostream>
#include "Level.h"
#include "AssetManager.h"
#include "MainMenu.h"

bool isDirExist(std::string path);
bool makePath(std::string path);

int main() {

    //initialization
    
    makePath(".\\saves");


    bool fullscreen = true;
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth");
    window.setFramerateLimit(60);
    AssetManager manager;
    MainMenu mainMenu;
    sf::Sprite background(AssetManager::getTexture(".\\resources\\white19201080.png"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
				{
					(fullscreen) ? window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth") : window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Labyrinth", sf::Style::Fullscreen);
					fullscreen = !fullscreen;
				}
                break;
            case sf::Event::Closed:
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        mainMenu.draw(window.getSize().x, window.getSize().y, 0.25, window);
        //draw here
        window.display();
    }

    return 0;

}

bool isDirExist(std::string path)
{
#if defined(_WIN32)
    struct _stat info;
    if (_stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & _S_IFDIR) != 0;
#else 
    path = std::regex_replace(path, std::regex("\\\\"), "/");
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
#endif
}

bool makePath(std::string path)
{
#if defined(_WIN32)
    int ret = _mkdir(path.c_str());
#else
    path = std::regex_replace(path, std::regex("\\\\"), "/");
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
#endif
    if (ret == 0)
        return true;

    switch (errno)
    {
    case ENOENT:
        // parent didn't exist, try to create it
        {
            int pos = path.find_last_of('/');
            if (pos == std::string::npos)
#if defined(_WIN32)
                pos = path.find_last_of('\\');
            if (pos == std::string::npos)
#endif
                return false;
            if (!makePath(path.substr(0, pos) ))
                return false;
        }
        // now, try to create again
#if defined(_WIN32)
        return 0 == _mkdir(path.c_str());
#else 
        return 0 == mkdir(path.c_str(), mode);
#endif

    case EEXIST:
        // done!
        return isDirExist(path);

    default:
        return false;
    }
}