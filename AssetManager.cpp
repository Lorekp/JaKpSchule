#include "AssetManager.h"
#include "Slope.h"
#include "Straight.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

void AssetManager::serializeGrid(std::string const& filename, Grid& gridG)
{
	std::vector<std::vector<GridElement>>& grid = gridG.getGrid();

	std::ofstream wf(filename, std::ios::binary | std::ios::trunc);
	if (!wf)
		std::cout << "Cannot open file!" <<std::endl;
	//write x/y size of grid
	int gridSizeX = grid.size();
	int gridSizeY = grid.at(0).size();
	wf.write((char*)&gridSizeX, sizeof(int));
	wf.write((char*)&gridSizeY, sizeof(int));
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			int sGridsize = grid.at(y).at(x).getSubGridElements().size();
			//write number of SubGridElements
			wf.write((char*)&sGridsize, sizeof(int));
			for (int i = 0; i < sGridsize; i++)
			{
				int type = grid.at(y).at(x).getSubGridElementAt(i).getType();
				//write type of subgridelement & depending on type side/rotation
				wf.write((char*)&type, sizeof(int));
				switch (type)
				{
				case 0:
				{
					int rotation = grid.at(y).at(x).getSubGridElementAt(i).getSprite().getRotation();
					wf.write((char*)&rotation, sizeof(int));
					break;
				}
				case 1:
				{
					int side = grid.at(y).at(x).getSubGridElementAt(i).getSide();
					wf.write((char*)&side, sizeof(int));
					break;
				}
				default:
					break;
				}
			}
		}
	}
	//write start/finish
	sf::Vector3i start = gridG.getStart();
	wf.write((char*)&start.x, sizeof(int));
	wf.write((char*)&start.y, sizeof(int));
	wf.write((char*)&start.z, sizeof(int));

	sf::Vector3i finish = gridG.getFinish();
	wf.write((char*)&finish.x, sizeof(int));
	wf.write((char*)&finish.y, sizeof(int));
	wf.write((char*)&finish.z, sizeof(int));

	wf.close();
	if (!wf.good()) 
		std::cout << "Error occurred at writing time!" << std::endl;
	
}

Grid AssetManager::deserializeGrid(std::string const& filename)
{
	std::ifstream rf(filename, std::ios::binary);
	if (!rf)
		std::cout << "Cannot open file!" << std::endl;
	//reading size of grid
	int gx, gy;
	rf.read((char*)&gx, sizeof(int));
	rf.read((char*)&gy, sizeof(int));
	Grid rGrid(gx, gy);
	for (int x = 0; x < gx; x++) 
	{
		for (int y = 0; y < gy; y++)
		{
			//reading how many subGridElements to read
			int sGridSize;
			rf.read((char*)&sGridSize, sizeof(int));
			for (int i = 0; i < sGridSize; i++) {
				//reading type and rotation
				int type, rotation, side;
				rf.read((char*)&type, sizeof(int));
				switch (type)
				{
				case 0:
				{
					rf.read((char*)&rotation, sizeof(int));
					rGrid.addSubGridElementAt(x, y, Slope(rotation));
					break;
				}
				case 1:
				{
					rf.read((char*)&side, sizeof(int));
					rGrid.addSubGridElementAt(x, y, Straight(side));
					break;
				}
				default:
					break;
				}
			}
		}
	}
	//read start/finish
	sf::Vector3i start;
	rf.read((char*)&start.x, sizeof(int));
	rf.read((char*)&start.y, sizeof(int));
	rf.read((char*)&start.z, sizeof(int));
	rGrid.setStart(start);

	sf::Vector3i finish;
	rf.read((char*)&finish.x, sizeof(int));
	rf.read((char*)&finish.y, sizeof(int));
	rf.read((char*)&finish.z, sizeof(int));
	rGrid.setFinish(finish);

	rf.close();
	if (!rf.good())
		std::cout << "Error occurred at reading time!" << std::endl;
	return rGrid;
}

sf::Texture& AssetManager::getTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;

	auto pairFound = texMap.find(filename);

	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

Grid& AssetManager::getGrid(std::string const& filename)
{
	auto& gridMap = sInstance->m_Grids;

	auto pairFound = gridMap.find(filename);

	if (pairFound != gridMap.end())
		return pairFound->second;
	else
	{
		auto& grid = gridMap[filename];
		grid = sInstance->deserializeGrid(filename);
		return grid;
	}
}