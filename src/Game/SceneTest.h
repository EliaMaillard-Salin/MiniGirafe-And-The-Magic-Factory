#pragma once

#include "Scene.h"
#include "MachineSelectPipe.h"

struct Map;
class Player;
class Grimoire;
class GCInputSystem;
class Tile;
class Inventory;
class Prop;
class UIText;
class Pipe;
class WoodFarmer;
class PlantFarmer;
class RessourcesSpawner;
class PotionSelector;
class RessourcesProp;
class DecantingMachine;
class ScenePause;

class SceneTest : public Scene
{
	// Just for tests

	Prop* m_pProp = nullptr;

	Pipe* m_pPipe = nullptr;
	DecantingMachine* m_pDecant = nullptr;

	RessourcesSpawner* m_pSpawnerWood = nullptr;
	RessourcesSpawner* m_pSpawnerPlant = nullptr;

	ScenePause* m_pPauseMenu = nullptr;

	//
	Scene* m_pPauseScene = nullptr;

	bool m_onPause = false;

	Map* m_pMap = nullptr;
	MachineSelectPipe* m_machineSelectPipe = nullptr;

	PotionSelector* m_pPotionSelector = nullptr;

	Player* m_pPlayer = nullptr;
	Grimoire* m_pGrimoire = nullptr;

	UIText* m_pFpstext = nullptr;

	int m_mapRows = 4;
	int m_mapCols = 4;
	int m_mapTileCount = 15;
	Inventory* m_pInventory = nullptr;

	std::vector<std::vector<std::vector<RessourcesProp*>>> m_propsOnSpawnerList = {};

public:
	enum GAME_TAG : int
	{
		PIPE,
		MACHINE,
		PLAYER,
		MOVINGITEM,
		PIPEWALL,
		PIPEENDCHECK,
		RESOURCE_SPAWNER,
		DECANTING_MACHINE,
	};


	SceneTest() = default;
	~SceneTest();

	void LoadAssets() override;
	void OnInitialize() override;
	void OnUpdate() override;
	void OnFixedUpdate() override {};

	void PauseGame();
	void UnpauseGame();

	void SwitchScene();

	Tile* GetTileOver();
	int GetTileCount();
	Grimoire* GetGrimoire();
	Inventory* GetInventory();

	void SetSceneMenu(Scene* pScene);

	void OpenSelectPipeMenu(std::vector<std::vector<Tile*>> tiles, Machine* pMachine);

	virtual void OnEvent(std::optional<sf::Event> pEvent);

	RessourcesProp* GetMachinePropPrefab(int type, int biome, int rank);

	Map* GetMap();

	PotionSelector* GetPotionListSelector();
};