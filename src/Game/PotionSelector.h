#pragma once

#include "UIEntity.h"

class DecantingMachine;
class Potion;

class PotionSelector : public UIEntity
{
	std::map<POTION_TYPES,Potion*> m_unlockedPotions = {};

	DecantingMachine* m_pMachine = nullptr;

protected:
	void OnUpdate() override;
	void Draw();
	void Hide();

	void PotionSelected(POTION_TYPES potion);
public:
	void Init();
	void AddAvailablePotion(POTION_TYPES potion);

	void Open(DecantingMachine* pMachine);

};

