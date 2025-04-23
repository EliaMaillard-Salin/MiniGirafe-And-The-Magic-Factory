#include "pch.h"
#include "CraftingScroll.h"
#include "Placable.h"
#include "Pipe.h"
#include "Machine.h"
#include "DecantingMachine.h"
#include "FarmingMachine.h"
#include "Inventory.h"

void CraftingScroll::Init()
{
}


void CraftingScroll::OpenCrafting()
{
	SetUIVisible();
	for (ButtonCraftingTable* pICon : m_craftableMachines)
	{
		pICon->SetUIVisible();
		pICon->CanCraft(true);
	}
}

void CraftingScroll::CloseCrafting()
{
	SetUIInvisible();
	for (ButtonCraftingTable* pICon : m_craftableMachines)
	{
		pICon->SetUIInvisible();
		pICon->CanCraft(false);
	}
}

void CraftingScroll::Craft(CRAFTABLE_OBJECT type)
{
	switch (type)
	{
	case WOOD_FARMER:
		if (CheckIfHasProp(type, 1))
		{
			WoodFarmer* pWoodFarmer = CreateEntity<WoodFarmer>();
			pWoodFarmer->Init(2, 2);
			CloseCrafting();
		}

		break;
	case PLANT_FARMER:
		if (CheckIfHasProp(type, 1))
		{
			PlantFarmer* pPlantFarmer = CreateEntity<PlantFarmer>();
			pPlantFarmer->Init(2, 2);
			CloseCrafting();
		}
		
		break;
	case DECANTER:
		if (CheckIfHasProp(type, 1))
		{
			DecantingMachine* pDecantingMachine = CreateEntity<DecantingMachine>();
			pDecantingMachine->Init();
			CloseCrafting();
		}
		break;
	case PIPE:
		if (CheckIfHasProp(type,1))
		{
			Pipe* pPipe = CreateEntity<Pipe>();
			pPipe->Init();
			CloseCrafting();
		}
		break;


	default:
		break;
	}
}

bool CraftingScroll::UnlockMachine(CRAFTABLE_OBJECT type)
{
	switch (type)
	{
	case DECANTER:
		return CheckIfHasProp(type, 0);

	default:
		break;
	}
}

bool CraftingScroll::CheckIfHasProp(CRAFTABLE_OBJECT type, int unlock)
{
	return true;
}

CraftingScroll::CraftingScroll()
{
	m_craftingRecipe.insert(std::pair < CRAFTABLE_OBJECT, std::list<Materials>>(WOOD_FARMER, { {10, RESSOURCES_PROPS::CHENE} } ));
	m_craftingRecipe.insert(std::pair < CRAFTABLE_OBJECT, std::list<Materials>>(PLANT_FARMER, { {10, RESSOURCES_PROPS::TREFLE} }));
	m_craftingRecipe.insert(std::pair < CRAFTABLE_OBJECT, std::list<Materials>>(DECANTER, { {20, RESSOURCES_PROPS::CHENE},{20, RESSOURCES_PROPS::TREFLE} })); // TEMP
	m_craftingRecipe.insert(std::pair < CRAFTABLE_OBJECT, std::list<Materials>>(PIPE, { {5, RESSOURCES_PROPS::CHENE} }));
	
	m_unlockingRecipe.insert(std::pair < CRAFTABLE_OBJECT, std::list<Materials>>(DECANTER, { {5, RESSOURCES_PROPS::CHENE},{5, RESSOURCES_PROPS::TREFLE} }));


	for (int i = 0; i < CRAFTABLE_OBJECT::COUNT; i++)
	{
		ButtonCraftingTable* pButton = CreateEntity<ButtonCraftingTable>();
		pButton->Init(this,(CRAFTABLE_OBJECT)i);
		m_craftableMachines.push_back(pButton);
	}

}

void ButtonCraftingTable::Init(CraftingScroll* pCraftingScroll, CRAFTABLE_OBJECT type)
{
	m_pCraftingScroll = pCraftingScroll;
	m_state = 0;
	m_type = type;
	if (type == CRAFTABLE_OBJECT::PIPE || type == CRAFTABLE_OBJECT::PLANT_FARMER || type == CRAFTABLE_OBJECT::WOOD_FARMER)
		m_state = 1;
}

void ButtonCraftingTable::CanCraft(bool boolean)
{
	m_craftinScrollIsOpen = boolean;
}

void ButtonCraftingTable::OnClick()
{
	if (m_craftinScrollIsOpen = false)
		return;

	if (m_state == 0)
	{
		if (m_pCraftingScroll->UnlockMachine(m_type))
		{
			m_state = 1;
			// SetNewSprite
		}
		return;
	}

	m_pCraftingScroll->Craft(m_type);
	m_pCraftingScroll->CloseCrafting();
}
