#pragma once

#include "Machine.h"
#include "UIEntity.h"

class PotionSelector;
class Potion;

struct PotionIngredient
{
	int ammount = 0;
	int propID;
};

class PotionRecipe {

	std::map<POTION_TYPES, std::list<PotionIngredient>> m_recipes = {};
	std::map< POTION_TYPES, int> m_timeToDecant = {};

	static PotionRecipe* Get();
	PotionRecipe();
	virtual ~PotionRecipe();

public:
	static std::list<PotionIngredient> GetRecipeOfPotion(POTION_TYPES potion);
	static int GetTimeToDecant(POTION_TYPES potion);
};


class DecantingMachine : public Machine
{

	POTION_TYPES m_potionToCraft = LUCK_I;
	std::list<PotionIngredient> m_necessaryIngredients = {};
	int m_currentTick = 10;
	int m_tickToDecant = 0;

	int m_potionCraftedCount = 0;

	Potion* m_pPotionCrafted = nullptr;

	UIEntity* m_pResultSlot = nullptr;

	UIEntity* m_pSlot1 = nullptr;
	UIEntity* m_pSlot2 = nullptr;
	UIEntity* m_pSlot3 = nullptr;

	UIEntity* m_pUIDecantMachine = nullptr;
	PotionSelector* m_pPotionList = nullptr;

	std::vector<PotionIngredient> m_ingredientsSlot = {};

	PipePosInMachine m_outPipePos = TOP_LEFT;

	int m_pipeInCount = 3;
	int m_pipeOutCount = 1;

	bool m_canDecant = false;

	bool m_isOpen = false;

protected:

	bool CheckIfCanDecant();
	void ConsumIngredients();

	void OnTick() override;
	void ConfirmPotion(POTION_TYPES potion);

	void ReceiveFromInPipes();

public:
	DecantingMachine();
	virtual ~DecantingMachine() = default;
	void Init();

	void OpenCraftingMachine();

	void PlaceObject() override;
	void MachineEffect() override;

	bool CheckPlaceCondition(Tile* pTile) override;

	void AddIngredient(int potionIngredient, int ammout  = 1,int slot = -1);

	void SetPipe(int pipeID, sf::Vector2i pipeTilePos, int pipeSide);

	void DrawUI() override;

	void OpenMachineUI() override;

	friend PotionSelector;
};

