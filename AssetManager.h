#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <fstream>
#include <regex>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <string>
#include "Slope.h"
#include "Straight.h"
#include "GridElement.h"
#include "Grid.h"
#include "SubGridElement.h"

class Slope;
class Straight;
class Grid;

class AssetManager {

	public:

		AssetManager();

		static sf::Texture& getTexture(std::string filename);
		static Grid& getGrid(std::string filename);
		static void serializeGrid(std::string filename, std::vector<std::vector<GridElement>>& grid);

	private:

		std::map<std::string, sf::Texture> m_Textures;
		std::map<std::string, Grid> m_Grids;

		//Asset Manager is a singleton, so only one instance can exist at a time 
		//sInstacne holds a static pointer to the single manager instance static AssetManager* sInstance;

		static AssetManager* sInstance;

		static Grid deserializeGrid(std::string filename);
};
#endif
