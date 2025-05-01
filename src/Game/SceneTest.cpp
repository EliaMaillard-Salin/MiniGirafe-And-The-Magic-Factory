#include "pch.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

#include "SceneTest.h"

#include "ScenePause.h"

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

	AssetManager::LoadSpriteSheet("Machine/PlantFarmer-Sheet", 23, 2944, 128, 1, 23);


	AnimationManager::CreateAnimation("PlantFarmerFarming", "Machine/PlantFarmer-Sheet", 0, 23);

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

	m_pPauseMenu = GameManager::Get()->CreateScene<ScenePause>();
	m_pPauseMenu->SetGameScene(this);
	
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
	m_pPlayer->SetPosition(64.f * 30.f, 64.f * 30.f);

	m_pFpstext = CreateUIText();
	m_pFpstext->SetSize(20);
	m_pFpstext->SetPosOnCanva({ 10,10 });

	m_pGrimoire->CloseGrimoire();

	m_pSpawnerWood = CreateEntity<RessourcesSpawner>();
	m_pSpawnerWood->Init(this,2, 2, RESSOURCES_TYPES::TREE, RESSOURCES_BIOMES::PLAINS, RESSOURCES_RANK::RANK_1);
	m_pSpawnerWood->SetPositionInWorld(sf::Vector2i(2,2), sf::Vector2i(2, 2));

	m_pSpawnerPlant = CreateEntity<RessourcesSpawner>();
	m_pSpawnerPlant->Init(this, 2, 2, RESSOURCES_TYPES::PLANT, RESSOURCES_BIOMES::PLAINS, RESSOURCES_RANK::RANK_1);
	m_pSpawnerPlant->SetPositionInWorld(sf::Vector2i(2, 2), sf::Vector2i(8, 3));
}

void SceneTest::OnUpdate()
{
	m_pFpstext->SetText(std::to_string(m_fps));
	m_pFpstext->Draw();
}

void SceneTest::PauseGame()
{
	if (m_onPause)
	{
		return;
	}

	GameManager::Get()->SetActiveScene(m_pPauseMenu);

	m_onPause = true; 
}

void SceneTest::UnpauseGame()
{
	if (m_onPause == false)
	{
		return;
	}

	GameManager::Get()->SetActiveScene(this);
	GameManager::Get()->UnloadScene(m_pPauseMenu);

	m_onPause = false;
}

void SceneTest::SwitchScene()
{
	GameManager::Get()->SetActiveScene(m_pPauseScene);
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

void SceneTest::SetSceneMenu(Scene* pScene)
{
	m_pPauseScene = pScene;
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

		//if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
		//{
		//	m_pInventory->AddElementInInventory(m_pProp, 1);
		//}
		//if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R)
		//{
		//	m_pInventory->RemoveElementInInventory(m_pProp, 1);
		//}


		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init(Pipe::UP, Pipe::LEFT);
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::T)
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init(Pipe::UP, Pipe::RIGHT);
		}

		if (pEvent->getIf<sf::Event:: KeyPressed>()->code == sf::Keyboard::Key::C)
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init();
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W)
		{
			WoodFarmer* pWoodFarmer = CreateEntity<WoodFarmer>();
			pWoodFarmer->Init(2,2);
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::X)
		{
			PlantFarmer* pPlantFarmer = CreateEntity<PlantFarmer>();
			pPlantFarmer->Init(2, 2);
		}
		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::M)
		{
			m_pDecant = CreateEntity<DecantingMachine>();
			m_pDecant->Init();
		}

		if (pEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
		{
			PauseGame();
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
