#pragma once

#include "UIEntity.h"
#include "Button.h"

enum CRAFTABLE_OBJECT : int
{
	WOOD_FARMER,
	PLANT_FARMER,
	DECANTER,
	PIPE,
	COUNT,
	NONE
};

struct Materials
{
	int ammount = 0;
	int propID = -1;
};

class CraftingScroll;
class Inventory;

class ButtonCraftingTable : public Button
{

	int m_state = 0;
	CRAFTABLE_OBJECT m_type = NONE;
	CraftingScroll* m_pCraftingScroll = nullptr;
	bool m_craftinScrollIsOpen = false;

public:

	void Init(CraftingScroll* pCraftingScroll, CRAFTABLE_OBJECT type);
	void CanCraft(bool boolean);
	void OnClick() override;
};

class CraftingScroll : public UIEntity
{
	std::list<ButtonCraftingTable*> m_craftableMachines = {};

	std::map<CRAFTABLE_OBJECT, std::list<Materials>> m_craftingRecipe = {};
	std::map<CRAFTABLE_OBJECT, std::list<Materials>> m_unlockingRecipe = {};

	Inventory* m_pInventory = nullptr;

public:
	CraftingScroll();
	virtual ~CraftingScroll() = default;

	void Init();

	void OpenCrafting();
	void CloseCrafting();

	void Craft(CRAFTABLE_OBJECT type);
	bool UnlockMachine(CRAFTABLE_OBJECT type);

	bool CheckIfHasProp(CRAFTABLE_OBJECT type, int unlock);
};

