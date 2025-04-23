#pragma once

#include "Entity.h"

class Prop;
class RessourcesProp;

class RessourcesSpawner : public Entity
{
protected:
	int m_widthInTiles = 0;
	int m_heightInTiles = 0;
	
	int m_ressourceType = -1;
	int m_biome = -1;
	int m_rank = -1;

	RessourcesProp* m_pProp = nullptr;

	Tile* m_pTileOfMachine = nullptr;

public:
	RessourcesSpawner();
	virtual ~RessourcesSpawner() = default;

	void Init(Scene* pScene,int widthInTiles, int heightInTiles, int resType, int biome, int rank);

	void SetPositionInWorld(sf::Vector2i chunkCoord, sf::Vector2i topLeftTileCoord);

	RessourcesProp* GetProp();

	int GetSpawnerType();
};