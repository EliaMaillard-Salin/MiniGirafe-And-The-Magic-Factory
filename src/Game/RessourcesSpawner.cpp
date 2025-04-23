#include "pch.h"
#include "RessourcesSpawner.h"
#include "SceneTest.h"
#include "Map.h"
#include "Chunk.h"
#include "Tile.h"

RessourcesSpawner::RessourcesSpawner()
{
	m_tag = SceneTest::GAME_TAG::RESOURCE_SPAWNER;
	m_hasCollision = true;
	m_isDrawable = true;
}

void RessourcesSpawner::Init(Scene* pScene,int widthInTiles, int heightInTiles, int resType, int biome, int rank)
{
	m_pScene = pScene;
	m_widthInTiles = widthInTiles;
	m_heightInTiles = heightInTiles;

	m_width = widthInTiles * 64.0f;
	m_height = heightInTiles * 64.0f;


	std::string texturePath = "Spawners/";
	texturePath += std::to_string(resType);
	texturePath += "_";
	texturePath += std::to_string(biome);
	texturePath += "_";
	texturePath += std::to_string(rank);
	SetSpriteTexture(texturePath.c_str());
	m_ressourceType = resType;
	m_biome = biome;
	m_rank = rank;

	m_pProp = GetScene<SceneTest>()->GetMachinePropPrefab(resType, biome, rank);

	SetLayer(3);
}

void RessourcesSpawner::SetPositionInWorld(sf::Vector2i chunkCoord, sf::Vector2i topLeftTileCoord)
{
	Map* pMap = GetScene<SceneTest>()->GetMap();

	Tile* topLeftTile = pMap->m_chunks[chunkCoord.x][chunkCoord.y]->GetTile(topLeftTileCoord.x, topLeftTileCoord.y);
	m_pTileOfMachine = topLeftTile;
	topLeftTile->SetObjectOnTile(this);
	SetPosition(topLeftTile->GetPosition(0,0).x, topLeftTile->GetPosition(0,0).y,0,0);
}

RessourcesProp* RessourcesSpawner::GetProp()
{
	return m_pProp;
}

int RessourcesSpawner::GetSpawnerType()
{
	return m_ressourceType;
}
