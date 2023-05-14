#ifndef ASSET MANAGER_H
#define ASSET MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "Grid.h"
#include "Slope.h"
#include "Straight.h"

class AssetManager {

	public:

		AssetManager();

		static sf::Texture& getTexture(std::string const& filename);
		static Grid& getGrid(std::string const& filename);
		void serializeGrid(std::string const& filename, std::vector<std::vector<GridElement>>& grid);

	private:

		std::map<std::string, sf::Texture> m_Textures;
		std::map<std::string, Grid> m_Grids;

		//Asset Manager is a singleton, so only one instance can exist at a time 
		//sInstacne holds a static pointer to the single manager instance static AssetManager* sInstance;

		static AssetManager* sInstance;

		Grid deserializeGrid(std::string const& filename);
};
#endif
