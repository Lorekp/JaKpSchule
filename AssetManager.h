#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Slope.h"
#include "Straight.h"
#include "GridElement.h"
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <SFML/Graphics.hpp>

class Grid;

class AssetManager {

	public:

		AssetManager();

		static sf::Texture& getTexture(std::string const& filename);
		static Grid& getGrid(std::string const& filename);
		static void serializeGrid(std::string const& filename, std::vector<std::vector<GridElement>>& grid);

	private:

		std::map<std::string, sf::Texture> m_Textures;
		std::map<std::string, Grid> m_Grids;

		//Asset Manager is a singleton, so only one instance can exist at a time 
		//sInstacne holds a static pointer to the single manager instance static AssetManager* sInstance;

		static AssetManager* sInstance;

		static Grid deserializeGrid(std::string const& filename);
};
#endif
