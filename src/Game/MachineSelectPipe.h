#pragma once

#include "UIEntity.h"
#include <map>

class Tile;
class Machine;
class SceneTest;
class UIText;

class MachineSelectPipe : public UIEntity
{
	struct SelectedTiles
	{
		sf::Vector2i tileCoord;
		int side;
	};

private:
	UIText* m_pTextTitle = nullptr;
	UIText* m_pClick = nullptr;
	UIText* m_pArrow = nullptr;
	UIText* m_pEnter = nullptr;

	bool m_tileIsSelected = false;
	sf::Vector2i m_selectedTile = sf::Vector2i(-1, -1);
	int m_tileSide = 0;
	int m_pipeID = 0;

	Machine* m_pSelectedMachine = nullptr;
	std::vector<std::vector<UIEntity*>> m_tilesOfMachine = {};

	std::list<SelectedTiles> m_selectedTilesAndSide = {};

	void Init(std::vector<std::vector<Tile*>> tiles, Machine* pMachine);

	void EndSelection();

public:
	MachineSelectPipe();
	~MachineSelectPipe() = default;

	void OnUpdate();


	friend SceneTest;
};

