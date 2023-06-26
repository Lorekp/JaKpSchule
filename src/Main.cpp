#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <sys/stat.h>
#include <errno.h>
#if defined(_WIN32)
#include <direct.h>
#endif
#include <regex>
#include <iostream>
#include "gameModes/Level.h"
#include "utils/AssetManager.h"
#include "gameModes/MainMenu.h"
#include "gameModes/editor/Editor.h"
#include "utils/Settings.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "gameModes/editor/EditorMenu.h"


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
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8.0;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2), "Labyrinth", sf::Style::Default, contextSettings);
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    float scale = 0.25f;
    AssetManager manager;
    Settings settings;
    settings.setScale(scale);
  
    MainMenu mainMenu(window);
    int runReturn = mainMenu.run();
    if (runReturn == 0)
    {
        EditorMenu editorMenu(gui, window);
        editorMenu.run();
    }
    if (runReturn == 2)
    {
        Level level(window, ".\\saves\\level.labdat");
        level.run();
    }
    /*Editor editor(window);
    editor.run();*/
    
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