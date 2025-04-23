#pragma once

#include <vector>
#include "UIEntity.h"

namespace sf
{
	class Sprite;
}

class Prop;
class SceneTest;

class InventoryTile : public UIEntity
{
	int m_count = 0;
	Prop* m_pProp = nullptr;
	bool m_isEmpty = true;

	UIText* m_pAmmount = nullptr;

public:
	InventoryTile();
	~InventoryTile();

	void Init();

	bool IsEmpty();
	
	void AddElement(Prop* pProp, int count);
	void AddElement(int count);
	void RemoveElement(int count);

	void SetTilePosition(float x, float y);

	void Draw();
	void Hide();

	Prop* GetProp();
};


class Inventory
{
	bool m_isFull;
	
	int m_firstEmptyRow = 0;
	int m_firstEmptyCol = 0;

	std::vector<std::vector<InventoryTile*>> m_inventoryTilesList = {};

private:

	sf::Vector2i CheckIfPropInInventory(Prop* pProp);

	void RemoveElementInInventory(int row, int col);

public:
	Inventory() = default;
	virtual ~Inventory() = default;

	void Init(SceneTest* pScene);

	bool AddElementInInventory(Prop* pProp, int propCount);

	void RemoveElementInInventory(Prop* pProp, int propCount);

	void Draw();
	void Hide();

};

