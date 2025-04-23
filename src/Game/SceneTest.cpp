#include "pch.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

#include "SceneTest.h"

#include "Player.h"

#include "Grimoire.h"
#include "Inventory.h"

#include "PotionSelector.h"

#include "Placable.h"
#include "Machine.h"
#include "Pipe.h"
#include "DecantingMachine.h"
#include "FarmingMachine.h"

#include "RessourcesSpawner.h"
#include "Prop.h"
#include "MovingItem.h"

#include "GameUtils.h"

SceneTest::~SceneTest()
{
	delete m_pMap;
	m_pGrimoire = nullptr;
	m_pPlayer = nullptr;
}

void SceneTest::LoadAssets()
{

	AssetManager::LoadSpriteSheet("Machine/WoodFarmer-Sheet", 12, 1536, 128, 1, 12);

	AnimationManager::CreateAnimation("WoodFarmerFarming", "Machine/WoodFarmer-Sheet", 0, 12);

	std::string jsonFilepath = "../../res/Prefab_Map/PrefabSpawner.json";
	std::ifstream jsonFile(jsonFilepath);
	json fileData = json::parse(jsonFile);
	
	int resCount = fileData["ResTypeCount"];
	int biomeCount = fileData["BiomesCount"];
	int rankCount = fileData["RankCount"];
	int spawnerCount = fileData["SpawnersCount"];

	EnumConverter converter = EnumConverter();

	m_propsOnSpawnerList = std::vector<std::vector<std::vector<RessourcesProp*>>>(resCount);
	for (int i = 0; i < resCount; i++)
	{
		m_propsOnSpawnerList[i] = std::vector<std::vector<RessourcesProp*>>(biomeCount);
		for (int j = 0; j < biomeCount; j++)
		{
			m_propsOnSpawnerList[i][j] = std::vector<RessourcesProp*>(rankCount);
		}
	}

	for (auto it = fileData["AllSpawners"].begin(); it != fileData["AllSpawners"].end(); it++)
	{
		std::string resType = it.value()["resType"];
		std::string biome = it.value()["Biome"];
		std::string rank = it.value()["rank"];
		std::string prop = it.value()["Prop"];

		RESSOURCES_TYPES typeE = converter.ConvertStringToEnumTypes(resType);
		RESSOURCES_BIOMES biomeE = converter.ConvertStringToEnumBiomes(biome);
		RESSOURCES_RANK rankE = converter.ConvertStringToEnumRank(rank);
		RESSOURCES_PROPS propE = converter.ConvertStringToEnumProps(prop);

		RessourcesProp* pNewProp = CreateEntity<RessourcesProp>();
		pNewProp->Init(propE);
		m_propsOnSpawnerList[typeE][biomeE][rankE] = pNewProp;
	}

}

void SceneTest::OnInitialize()
{
	m_machineSelectPipe = CreateEntity<MachineSelectPipe>();
	SetMaxLayer(6);

	m_pPotionSelector = CreateEntity<PotionSelector>();
	m_pPotionSelector->Init();
	m_pPotionSelector->AddAvailablePotion(POTION_TYPES::LUCK_I);

	m_pMap = new Map();
	Entity* tileover = CreateEntity<Entity>();
	tileover->SetSpriteTexture("TileOver");
	tileover->DisplayEntity();
	tileover->SetLayer(5);
	m_pMap->Init(this, tileover, m_mapRows, m_mapCols, m_mapTileCount);

	m_pGrimoire = CreateEntity<Grimoire>();
	m_pInventory = new Inventory();
	m_pInventory->Init(this);
	m_pGrimoire->Init();

	m_pPlayer = CreateEntity<Player>();
	m_pPlayer->Init();

	m_pFpstext = CreateUIText();
	m_pFpstext->SetSize(20);
	m_pFpstext->SetPosOnCanva({ 10,10 });

	m_pGrimoire->CloseGrimoire();

	m_pPipe = CreateEntity<Pipe>();
	m_pPipe->Init();

	m_pSpawner = CreateEntity<RessourcesSpawner>();
	m_pSpawner->Init(this,2, 2, RESSOURCES_TYPES::TREE, RESSOURCES_BIOMES::PLAINS, RESSOURCES_RANK::RANK_1);
	m_pSpawner->SetPositionInWorld(sf::Vector2i(0, 0), sf::Vector2i(2, 2));
}

void SceneTest::OnUpdate()
{
	m_pFpstext->SetText(std::to_string(m_fps));
	m_pFpstext->Draw();
}

Tile* SceneTest::GetTileOver()
{
	return m_pMap->m_pTileOver;
}

int SceneTest::GetTileCount()
{
	return m_mapTileCount;
}

Grimoire* SceneTest::GetGrimoire()
{
	return m_pGrimoire;
}

Inventory* SceneTest::GetInventory()
{
	return m_pInventory;
}

void SceneTest::OpenSelectPipeMenu(std::vector<std::vector<Tile*>> tiles, Machine* pMachine)
{
	m_machineSelectPipe->Init(tiles, pMachine);
}

void SceneTest::OnEvent(std::optional<sf::Event> pEvent)
{
	m_pPlayer->OnEvent(pEvent);
	if (pEvent->is<sf::Event::KeyPressed>())
	{
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F)
		{
			m_pGrimoire->Opengrimoire();
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::G)
		{
			m_pGrimoire->CloseGrimoire();
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right)
		{
			m_pGrimoire->Nextpage();
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left)
		{
			m_pGrimoire->PreviousPage();
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
		{
			m_pInventory->AddElementInInventory(m_pProp, 1);
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R)
		{
			m_pInventory->RemoveElementInInventory(m_pProp, 1);
		}
		if (pEvent->getIf<sf::Event:: KeyPressed>()->code == sf::Keyboard::Key::P)
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init();
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::O)
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init(Pipe::RIGHT,Pipe::UP);
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::H)
		{
			m_pPipe->ReceiveProp(m_pProp);
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::M)
		{
			WoodFarmer* pWoodFarmer = CreateEntity<WoodFarmer>();
			pWoodFarmer->Init(2,2);
		}

	}
}

RessourcesProp* SceneTest::GetMachinePropPrefab(int type, int biome, int rank)
{
	return m_propsOnSpawnerList[type][biome][rank];
}

Map* SceneTest::GetMap()
{
	return m_pMap;
}

PotionSelector* SceneTest::GetPotionListSelector()
{
	return m_pPotionSelector;
}
