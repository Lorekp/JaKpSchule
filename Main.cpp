#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
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
#include "Editor.h"

bool isDirExist(std::string path);
bool makePath(std::string path);

int main() {

    //initialization
    #if defined(_WIN32)
    makePath(".\\saves");
    #else
    makePath("./saves");
    #endif

    //window init
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    AssetManager manager;
  
    Editor editor(window);
    editor.run();
    
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