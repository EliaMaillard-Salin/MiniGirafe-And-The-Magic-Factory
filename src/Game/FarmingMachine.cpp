#include "pch.h"
#include "FarmingMachine.h"

#include <iostream>
#include "Map.h"
#include "Chunk.h"
#include "Tile.h"
#include "Pipe.h"
#include "MachineSelectPipe.h"
#include "SceneTest.h"
#include "NaturalRessources.h"
#include "MovingItem.h"
#include "RessourcesSpawner.h"


WoodFarmer::WoodFarmer()
{
}

void WoodFarmer::Init(int widht, int height)
{
	Machine::Init(widht, height);
	m_pProp = new WoodLog();
	m_hasTickEvent = true;
}

bool WoodFarmer::CheckPlaceCondition(Tile* pTile)
{
	Entity* pEntity = pTile->GetObjectOnTile();
	if (pEntity != nullptr)
	{
		if (pEntity->GetTag() == SceneTest::GAME_TAG::RESOURCE_SPAWNER)
		{
			RessourcesSpawner* pSpawn = dynamic_cast<RessourcesSpawner*>(pEntity);
			if (pSpawn->GetSpawnerType() == RESSOURCES_TYPES::TREE)
				return true;
		}
	}
	return false;
}

void WoodFarmer::MachineEffect()
{
	if (m_speedInTick <= 0)
	{
		m_speedInTick = 5;
		if (m_itemCount < m_maxitemcount) {
			m_itemCount += 1; // Farm
			std::cout << "CutWood" << std::endl;
			SmoothPlayAnimation("WoodFarmerFarming");
			m_pSprite->setPosition(m_pTileOfMachine->GetObjectOnTile()->GetPosition(0, 0));

		}
		else {
			SmoothStopAnimation();
		}
	}
	
	for (Pipe* pPipe: m_listOutPipes )
	{
		if (pPipe->CheckIfCanReceive(m_pProp) && m_itemCount > 0)
		{
			sf::Vector2f pipepos = pPipe->GetPosition();
			MovingItem* movingitem = CreateEntity<MovingItem>();
			movingitem->Init("woodMovingItem", pipepos.x, pipepos.y, pPipe);
			pPipe->ReceiveProp(m_pProp);
			m_itemCount -= 1;
		}
	}

}

void WoodFarmer::OnTick()
{
	m_speedInTick -= 1;
}

// Set Custom Pos Pipe (top left, top right for now)
void WoodFarmer::PlaceObject()
{
	Chunk* pChunk = m_pTileOfMachine->GetChunk();
	m_machineTiles = std::vector<std::vector<Tile*>>(m_heightInTiles);
	for (int i = 0; i < m_widthInTiles; i++)
	{
		m_machineTiles[i] = std::vector<Tile*>(m_widthInTiles);
		for (int j = 0; j < m_widthInTiles; j++)
		{
			if (m_pTileOfMachine->GetPosInChunk().x + j >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x + 1][pChunk->GetPosInList().y];
			}

			if (m_pTileOfMachine->GetPosInChunk().y + i >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y + 1];
			}

			m_machineTiles[i][j] = pChunk->GetTile(m_pTileOfMachine->GetPosInChunk().x + j, m_pTileOfMachine->GetPosInChunk().y + i);
		
		}
	}

	GetScene<SceneTest>()->OpenSelectPipeMenu(m_machineTiles, this);
	PlayAnimation("WoodFarmerFarming");
	m_pSprite->setPosition(m_pTileOfMachine->GetObjectOnTile()->GetPosition(0,0));
	m_isDrawable = true;
}

void WoodFarmer::SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide)
{
	if (pipeID == 0)
	{
		m_outPipePos = (PipePosInMachine)(pipeTilePos.x + pipeTilePos.y * 2.0f);
		Pipe* pPipeOut = CreateEntity<Pipe>();
		pPipeOut->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeOut->SetPosition(GetPosition().x + (pipeTilePos.x * 64.0f), GetPosition().y + (pipeTilePos.y * 64.0f));
		pPipeOut->GetSprite()->setOrigin({ 0, 0 });
		pPipeOut->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeOut->PlaceObject();
		pPipeOut->SetLayer(2);
		m_listOutPipes.push_back(pPipeOut);
		m_allPipeSelected = true;
	}
}

// PLANT

bool PlantFarmer::CheckPlaceCondition(Tile* pTile)
{
	Entity* pEntity = pTile->GetObjectOnTile();
	if (pEntity != nullptr)
	{
		if (pEntity->GetTag() == SceneTest::GAME_TAG::RESOURCE_SPAWNER)
		{
			RessourcesSpawner* pSpawn = dynamic_cast<RessourcesSpawner*>(pEntity);
			if (pSpawn->GetSpawnerType() == RESSOURCES_TYPES::PLANT)
				return true;
		}
	}
	return false;
}

PlantFarmer::PlantFarmer()
{
}

void PlantFarmer::Init(int widht, int height)
{
	Machine::Init(widht, height);
	m_pProp = new Plant();
	m_hasTickEvent = true;
}


void PlantFarmer::MachineEffect()
{
	if (m_speedInTick <= 0)
	{
		if (m_itemCount < m_maxitemcount) {
			m_speedInTick = 5;
			m_itemCount += 1; // Farm
			std::cout << "Harvest" << std::endl;
			SmoothPlayAnimation("PlantFarmerFarming");
			m_pSprite->setPosition(m_pTileOfMachine->GetObjectOnTile()->GetPosition(0, 0));
		}
		else {
			SmoothStopAnimation();
		}
	}

	for (Pipe* pPipe : m_listOutPipes)
	{
		if (pPipe->CheckIfCanReceive(m_pProp) && m_itemCount > 0)
		{
			sf::Vector2f pipepos = pPipe->GetPosition();
			MovingItem* movingitem = CreateEntity<MovingItem>();
			movingitem->Init("plantMovingItem", pipepos.x, pipepos.y, pPipe);
			pPipe->ReceiveProp(m_pProp);
			m_itemCount -= 1;
		}
	}

}

void PlantFarmer::OnTick()
{
	m_speedInTick -= 1;
}

// Set Custom Pos Pipe (top left, top right for now)
void PlantFarmer::PlaceObject()
{
	Chunk* pChunk = m_pTileOfMachine->GetChunk();
	m_machineTiles = std::vector<std::vector<Tile*>>(m_heightInTiles);
	for (int i = 0; i < m_widthInTiles; i++)
	{
		m_machineTiles[i] = std::vector<Tile*>(m_widthInTiles);
		for (int j = 0; j < m_widthInTiles; j++)
		{
			if (m_pTileOfMachine->GetPosInChunk().x + j >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x + 1][pChunk->GetPosInList().y];
			}

			if (m_pTileOfMachine->GetPosInChunk().y + i >= pChunk->GetTileCount())
			{
				pChunk = pChunk->GetMap()->m_chunks[pChunk->GetPosInList().x][pChunk->GetPosInList().y + 1];
			}

			m_machineTiles[i][j] = pChunk->GetTile(m_pTileOfMachine->GetPosInChunk().x + j, m_pTileOfMachine->GetPosInChunk().y + i);

		}
	}

	GetScene<SceneTest>()->OpenSelectPipeMenu(m_machineTiles, this);
	PlayAnimation("PlantFarmerFarming");
	m_pSprite->setPosition(m_pTileOfMachine->GetObjectOnTile()->GetPosition(0, 0));
	m_isDrawable = true;
}

void PlantFarmer::SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide)
{
	if (pipeID == 0)
	{
		m_outPipePos = (PipePosInMachine)(pipeTilePos.x + pipeTilePos.y * 2.0f);
		Pipe* pPipeOut = CreateEntity<Pipe>();
		pPipeOut->Init(PlaceableObject::NONE, (PlaceableObject::IN_OUT_SIDE)pipeSide);
		pPipeOut->SetPosition(GetPosition().x + (pipeTilePos.x * 64.0f), GetPosition().y + (pipeTilePos.y * 64.0f));
		pPipeOut->GetSprite()->setOrigin({ 0, 0 });
		pPipeOut->SetTileOfMachine(m_machineTiles[pipeTilePos.y][pipeTilePos.x]);
		pPipeOut->PlaceObject();
		pPipeOut->SetLayer(2);
		m_listOutPipes.push_back(pPipeOut);
		m_allPipeSelected = true;
	}
}