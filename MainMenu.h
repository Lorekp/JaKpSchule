#include "AssetManager.h"
#include <vector>

class MainMenu{

private:
	std::vector<sf::Texture> textures;

public:
	MainMenu(AssetManager manager);
	std::vector<sf::Texture>& GetTextures();

};
